#include <stdio.h>
#include "users.h"

int main(){
    InitUsers();

    for (int i = 0; i < 10; ++i) {
        User_t *temp = NewUser("temp","world");
        UsersAdd(temp);
    }

    User_t *u = NewUser("hello","world");

    User_t **users = UserGetAll();

    for(int i = 0;users[i] != NULL;i++){
        PrintUser(users[i]);
    }

    printf("------------------------\n");

    UsersAdd(u);

    User_t *u2 = UsersFind(u->WeNo);
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

    UsersDelete(u2);
    if (UsersFind(u2->WeNo) != NULL){
        printf("UsersDelete error");
        exit(2);
    }

    printf("--------------------\n");

    users = UserGetAll();

    for(int i = 0;users[i] != NULL;i++){
        PrintUser(users[i]);
    }
}