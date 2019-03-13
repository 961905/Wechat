#include <stdio.h>
#include "users.h"

int main(){
    Users_t *users = NewUsers();
    for (int i = 0; i < 10; ++i) {
        User_t *temp = NewUser("temp","world");
        UsersAdd(users,temp);
    }

    User_t *u = NewUser("hello","world");

    User_t **userList = UsersGetAll(users);

    for(int i = 0;userList[i] != NULL;i++){
        PrintUser(userList[i]);
    }
    free(userList);

    printf("------------------------\n");

    UsersAdd(users,u);

    User_t *u2 = UsersFind(users,u->UserId);
    if (u2 == NULL){
        printf("UsersFind error");
        exit(2);
    }
    if (u != u2){
        printf("UsersFind error");
        exit(2);
    }

    PrintUser(u);
    PrintUser(u2);

    UsersDelete(users,u2);
    if (UsersFind(users,u2->UserId) != NULL){
        printf("UsersDelete error");
        exit(2);
    }

    printf("--------------------\n");

    userList = UsersGetAll(users);

    for(int i = 0;userList[i] != NULL;i++){
        PrintUser(userList[i]);
    }
}