#include <sys/select.h>
#include <string.h>
#include <errno.h>
#include "io_engine.h"
#include "proto.h"


typedef struct {
    int fd;
    void *RCCtx;
    void *WCCtx;
    EventCallback_t readCallback;
    EventCallback_t writeCallback;
} IOEntry_t;

IoEngine_t *NewIoEngine() {
    IoEngine_t *ioEngine = (IoEngine_t *) malloc(sizeof(IoEngine_t));
    memset(ioEngine, 0, sizeof(IoEngine_t));
    ioEngine->eventList = list_new();
    ioEngine->eventGcList = list_new();
    ioEngine->maxfd = 0;
    return ioEngine;
}

int IoEngineReadEventAddWatch(IoEngine_t *ioEngine, int fd, void *ctx, EventCallback_t callback) {
    if (callback == NULL) {
        return ParamError;
    }
    list_iterator_t *iter = list_iterator_new(ioEngine->eventList, LIST_HEAD);
    while (1) {
        list_node_t *node = list_iterator_next(iter);
        if (node == NULL)
            break;
        IOEntry_t *ioEntry = (IOEntry_t *) node->val;
        if (ioEntry->fd == fd) {
            if (ioEntry->readCallback == NULL) {
                //update callback handle
                ioEntry->readCallback = callback;
            } else {
                FD_SET(fd, &ioEngine->readSet);
                ioEntry->readCallback = callback;
            }
            return 0;
        }
    }
    free(iter);

    if (ioEngine->eventList->len + 1 > FD_SETSIZE) {
        return -1;
    }
    IOEntry_t *ioEntry = (IOEntry_t *) malloc(sizeof(IOEntry_t));
    memset(ioEntry, 0, sizeof(IOEntry_t));
    ioEntry->fd = fd;
    ioEntry->RCCtx = ctx;
    ioEntry->readCallback = callback;
    list_rpush(ioEngine->eventList, list_node_new(ioEntry));

    FD_SET(fd, &ioEngine->readSet);
    if (fd > ioEngine->maxfd)
        ioEngine->maxfd = fd;
    return 0;
}

int IoEngineWriteEventAddWatch(IoEngine_t *ioEngine, int fd, void *ctx, EventCallback_t callback) {
    if (callback == NULL) {
        return ParamError;
    }
    list_iterator_t *iter = list_iterator_new(ioEngine->eventList, LIST_HEAD);
    while (1) {
        list_node_t *node = list_iterator_next(iter);
        if (node == NULL)
            break;
        IOEntry_t *ioEntry = (IOEntry_t *) node->val;
        if (ioEntry->fd == fd) {
            if (ioEntry->writeCallback == NULL) {
                //update callback handle
                ioEntry->writeCallback = callback;
            } else {
                FD_SET(fd, &ioEngine->writeSet);
                ioEntry->writeCallback = callback;
            }
            return 0;
        }
    }
    free(iter);

    if (ioEngine->eventList->len + 1 > FD_SETSIZE) {
        return -1;
    }
    IOEntry_t *ioEntry = (IOEntry_t *) malloc(sizeof(IOEntry_t));
    memset(ioEntry, 0, sizeof(IOEntry_t));
    ioEntry->fd = fd;
    ioEntry->WCCtx = ctx;
    ioEntry->writeCallback = callback;
    list_rpush(ioEngine->eventList, list_node_new(ioEntry));

    FD_SET(fd, &ioEngine->writeSet);
    if (fd > ioEngine->maxfd)
        ioEngine->maxfd = fd;
    return 0;
}

int IoEngineReadEventDelWatch(IoEngine_t *ioEngine, int fd) {
    list_iterator_t *iter = list_iterator_new(ioEngine->eventList, LIST_HEAD);
    while (1) {
        list_node_t *node = list_iterator_next(iter);
        if (node == NULL)
            break;
        IOEntry_t *ioEntry = (IOEntry_t *) node->val;
        if (ioEntry->fd == fd) {
            if (ioEntry->readCallback == NULL) {
                //nothing change
                break;
            }
            ioEntry->readCallback = NULL;
            FD_CLR(fd, &ioEngine->readSet);

            if (ioEntry->writeCallback == NULL) {
                list_remove(ioEngine->eventList, node);
                /*must not free IOEntry ?*/
                list_rpush(ioEngine->eventGcList, list_node_new(ioEntry));
            }
            break;
        }
    }
    free(iter);
    return 0;
}

int IoEngineWriteEventDelWatch(IoEngine_t *ioEngine, int fd) {
    list_iterator_t *iter = list_iterator_new(ioEngine->eventList, LIST_HEAD);
    while (1) {
        list_node_t *node = list_iterator_next(iter);
        if (node == NULL)
            break;
        IOEntry_t *ioEntry = (IOEntry_t *) node->val;
        if (ioEntry->fd == fd) {
            if (ioEntry->writeCallback == NULL) {
                //nothing change
                break;
            }
            ioEntry->writeCallback = NULL;
            FD_CLR(fd, &ioEngine->writeSet);

            if (ioEntry->writeCallback == NULL) {
                list_remove(ioEngine->eventList, node);
                /*must not free IOEntry ?*/
                list_rpush(ioEngine->eventGcList, list_node_new(ioEntry));
            }
            break;
        }
    }
    free(iter);
    return 0;
}

int IoEngineLoop(IoEngine_t *ioEngine, int timeoutMillis) {

    struct timeval val;
    val.tv_sec = timeoutMillis / 1000;
    val.tv_usec = timeoutMillis % 1000 * 1000;

    fd_set readSet = ioEngine->readSet;
    fd_set writeSet = ioEngine->writeSet;
    fd_set errorSet = ioEngine->errorSet;

    int count = select(ioEngine->maxfd, &readSet, &writeSet, &errorSet, &val);
    if (count == 0) {
        //timeout
        return 0;
    } else if (count < 0) {
        if (errno == EINTR || errno == EAGAIN) {
            return 0;
        }
        return count;
    }

    list_iterator_t *iter = list_iterator_new(ioEngine->eventList, LIST_HEAD);
    while (count > 0) {
        list_node_t *node = list_iterator_next(iter);
        if (node == NULL) {
            free(iter);
            break;
        }
        IOEntry_t *entry = (IOEntry_t *) node->val;
        int fd = entry->fd;
        if (FD_ISSET(fd, &readSet)) {
            count--;
            entry->readCallback(entry->RCCtx);
        } else if (FD_ISSET(fd, &writeSet)) {
            count--;
            // write event is canceled
            if (entry->writeCallback == NULL) {
                continue;
            }
            entry->writeCallback(entry->WCCtx);
        } else if (FD_ISSET(fd, &errorSet)) {
            count--;
            // write event is canceled
            if (entry->readCallback == NULL) {
                continue;
            }
            entry->readCallback(entry->RCCtx);
        }
    }

    iter = list_iterator_new(ioEngine->eventGcList, LIST_HEAD);
    list_node_t *pre = NULL;
    int change = 0;
    while (1) {
        list_node_t *node = list_iterator_next(iter);
        if (pre != NULL) {
            list_remove(ioEngine->eventGcList, pre);
        }
        if (node == NULL) {
            free(iter);
            break;
        }
        change = 1;
        IOEntry_t *entry = (IOEntry_t *) node->val;
        free(entry);
        pre = node;
    }

    if (!change) {
        ioEngine->maxfd = 0;
        iter = list_iterator_new(ioEngine->eventList, LIST_HEAD);
        while (1) {
            list_node_t *node = list_iterator_next(iter);
            if (node == NULL) {
                free(iter);
                break;
            }
            IOEntry_t *ioEntry = (IOEntry_t *) node->val;
            if (ioEntry->fd > ioEngine->maxfd) {
                ioEngine->maxfd = ioEntry->fd;
            }
        }
    }
    return 0;
}
