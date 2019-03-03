#ifndef __USER__H__
#define __USER__H__

#include <stdint.h>
#include <stdbool.h>
#include <list.h>

#define UsernameLen 64
#define PasswordLen 64
typedef struct User {
    char Username [UsernameLen] ;
    char Password [PasswordLen] ;
    int64_t WeNo;
    list_t *friendList;
}User_t;

User_t* NewUser(char *username ,char *Password);
void PrintUser(User_t *user);

bool UserAddFriend(User_t *user, int64_t friend);
bool UserCheckFriend(User_t *user, int64_t friend);
int64_t *GetFriends(User_t *user);

#endif //__USER__H__