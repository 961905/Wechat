#include "users.h"

typedef struct{
    int GroupId;
    char GroupName[32];
    Users_t *members;
}Group_t;

Group_t *NewGroup(int GroupId,char name[32]);

User_t *GroupFindUser(Group_t*group,int userId );

int GroupAddUser(Group_t*group,User_t *user);

User_t **GroupGetAllUsers();