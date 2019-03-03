
#ifndef __USER__H__
#define __USER__H__

#include <stdint-gcc.h>

#define UsernameLen 64
#define PasswordLen 64
typedef struct User {
    char Username [UsernameLen] ;
    char Password [PasswordLen] ;
    int64_t WeNo;
}User_t;

User_t* NewUser(char *username ,char *Password);
void PrintUser(User_t *user);


#endif __USER__H__