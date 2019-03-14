

#include <list.h>

typedef void (*EventCallback_t)(
        void *
);

typedef struct {
    list_t *eventList;
    list_t *eventGcList;
    fd_set readSet;
    fd_set writeSet;
    fd_set errorSet;
    int maxfd;
} IoEngine_t;

IoEngine_t *NewIoEngine();

int IoEngineReadEventAddWatch(IoEngine_t *ioEngine, int fd, void *ctx, EventCallback_t callback);

int IoEngineWriteEventAddWatch(IoEngine_t *ioEngine, int fd, void *ctx, EventCallback_t callback);

int IoEngineReadEventDelWatch(IoEngine_t *ioEngine, int fd);

int IoEngineWriteEventDelWatch(IoEngine_t *ioEngine, int fd);

int IoEngineLoop(IoEngine_t *ioEngine, int timeoutMillis);
