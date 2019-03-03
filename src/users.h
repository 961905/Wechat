#ifndef USERS_H_
#define USERS_H_

#include "user.h"

void InitUsers();

void UsersAdd(User_t *user);

User_t *UsersFind(int64_t WeNo);

void UsersDelete(User_t *user);

int UsersCount();

User_t **UserGetAll();

#endif