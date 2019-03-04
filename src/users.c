
#include <stdint.h>
#include <stddef.h>
#include <list.h> //deps/list
#include <string.h>
#include "users.h"


list_t *_UserList;

int matchByWeNo(void *_WeNo, void *_user){
    int64_t WeNo = *(int64_t*)_WeNo;
    User_t *user = (User_t*)_user;
    if (user->WeNo == WeNo){
        return 1;
    }
    return 0;
}

void InitUsers() {
    _UserList = list_new();
    _UserList->match = matchByWeNo;
}

void UsersAdd(User_t *user) {
    list_rpush(_UserList,list_node_new(user));
}

User_t *UsersFind(int64_t WeNo) {
    list_node_t *node = list_find(_UserList,&WeNo);
    if (node == NULL){
        return NULL;
    }
    User_t *user = (User_t*)node->val;
    return user;
}

void UsersDelete(User_t *user) {
    list_node_t *node = list_find(_UserList,&user->WeNo);
    if (node == NULL){
        return ;
    }
    list_remove(_UserList,node);
}

int UsersCount() {
    return  (int)_UserList->len;
}

User_t **UserGetAll() {
    int count = UsersCount();
    int index = 0;
    list_iterator_t *it ;
    list_node_t * node;

    if (count == 0){
        return NULL;
    }
    User_t **users = (User_t **)malloc((count+1)* sizeof(User_t*));
    memset(users,0,(count+1)* sizeof(User_t*));

    it = list_iterator_new(_UserList,LIST_HEAD);
    while((node = list_iterator_next(it))){
        users[index++] = (User_t*)node->val;
    }
    return users;
}
