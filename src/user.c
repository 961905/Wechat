
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "proto.h"
#include "user.h"

int64_t WeNo;
int64_t genWeNo(){
    return ++WeNo;
}

User_t *NewUser(char *username, char *Password) {
    void *obj = malloc(sizeof(User_t));
    memset(obj,0, sizeof(User_t));

    User_t *user = (User_t*)obj;
    strncpy(user->Username,username,UsernameLen);
    strncpy(user->Password,Password,PasswordLen);
    user->UserId = genWeNo();
    return user;
}

void PrintUser(User_t *user) {
    printf("username :%s password: %s UserId: %d\n",user->Username,user->Password,user->UserId);
}

int UserAddFriend(User_t *user, UserId_t friendId) {
    if (UserCheckFriend(user,friendId) == 1){
        return UserExist;
    }
    UserId_t *userId = (UserId_t*)malloc(sizeof(UserId_t));
    *userId = friendId;
    list_rpush(user->friendList,list_node_new(userId ));
    return 0;
}

int UserCheckFriend(User_t *user, UserId_t friendId) {
    list_iterator_t *iter = list_iterator_new(user->friendList,LIST_HEAD);
    list_node_t * node;
    int find = 0;
    while(1){
        node = list_iterator_next(iter);
        if (node == NULL){
            break;
        }else {
            void *val = node->val;
            int64_t *friend_id = (int64_t*)val;
            if (*friend_id == friendId){
                find = 1;
                break;
            }
        }
    }
    return find;
}


