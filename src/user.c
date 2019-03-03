
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
    user->WeNo = genWeNo();
    return user;
}

void PrintUser(User_t *user) {
    printf("username :%s password: %s WeNo: %lld",user->Username,user->Password,user->WeNo);
}


