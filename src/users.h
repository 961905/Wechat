#ifndef USERS_H_
#define USERS_H_

#include "user.h"


typedef struct users {
    list_t *user_list;
}Users_t;

Users_t *NewUsers();

int UsersAdd(Users_t *users,User_t *user);

User_t *UsersFind(Users_t *users,int64_t UserId);

void UsersDelete(Users_t *users,User_t *user);

int UsersCount(Users_t *users);

User_t **UsersGetAll(Users_t *users);

#endif