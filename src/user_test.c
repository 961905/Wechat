
#include <stdio.h>
#include "user.h"

int main(){
    printf("----------start user test-----------\n");
    User_t *user = NewUser("hello","world");
    PrintUser(user);
}