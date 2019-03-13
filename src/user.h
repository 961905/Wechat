#ifndef __USER__H__
#define __USER__H__

#include <stdint.h>
#include <stdbool.h>
#include <list.h>

#define UsernameLen 64
#define PasswordLen 64

typedef int UserId_t;

typedef struct User {
    char Username [UsernameLen] ;
    char Password [PasswordLen] ;
    UserId_t UserId;
    list_t *friendList;
}User_t;

User_t* NewUser(char *username ,char *Password);
void PrintUser(User_t *user);

int UserAddFriend(User_t *user, UserId_t friendId);
int UserCheckFriend(User_t *user, UserId_t friendId);

int64_t *GetFriends(User_t *user);

#endif //__USER__H__