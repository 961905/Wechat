
#include <stdint.h>
#include <stddef.h>
#include <list.h>
#include <string.h>
#include "proto.h"
#include "users.h"


int matchByWeNo(void *_WeNo, void *_user){
    int64_t WeNo = *(int64_t*)_WeNo;
    User_t *user = (User_t*)_user;
    if (user->UserId == WeNo){
        return 1;
    }
    return 0;
}

Users_t *NewUsers() {
    Users_t *users = (Users_t*)malloc(sizeof(Users_t));
    memset(users ,0, sizeof(Users_t));
    users->user_list = list_new();
    users->user_list->match = matchByWeNo;
    return users;
}

int UsersAdd(Users_t *users,User_t *user) {
    if (UsersFind(users,user->UserId) != NULL){
        return UserExist;
    }
    list_rpush(users->user_list,list_node_new(user));
    return Ok;
}

User_t *UsersFind(Users_t *users,int64_t UserId) {
    list_node_t *node = list_find(users->user_list,&UserId);
    if (node == NULL){
        return NULL;
    }
    User_t *user = (User_t*)node->val;
    return user;
}

void UsersDelete(Users_t *users,User_t *user) {
    list_node_t *node = list_find(users->user_list,&user->UserId);
    if (node == NULL){
        return ;
    }
    list_remove(users->user_list,node);
}

int UsersCount(Users_t *users) {
    return  (int)users->user_list->len;
}

User_t **UsersGetAll(Users_t *users) {
    int count = UsersCount(users);
    int index = 0;
    list_iterator_t *it ;
    list_node_t * node;

    if (count == 0){
        return NULL;
    }
    User_t **pUser = (User_t **)malloc((count+1)* sizeof(User_t*));
    memset(pUser,0,(count+1)* sizeof(User_t*));

    it = list_iterator_new(users->user_list,LIST_HEAD);
    while((node = list_iterator_next(it))){
        pUser[index++] = (User_t*)node->val;
    }
    return pUser;
}
