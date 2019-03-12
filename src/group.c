#include <string.h>
#include "group.h"
#include "proto.h"

Group_t *NewGroup(int GroupId, char name[32]) {
    Group_t *group = (Group_t *)malloc(sizeof(Group_t));
    memset(group,0, sizeof(Group_t));
    group->GroupId = GroupId;
    strcpy(group->GroupName,name);
    group->members = NewUsers();
    return group;
}

User_t *GroupFindUser(Group_t *group, int userId) {
    return UsersFind(group->members,userId);
}

int GroupAddUser(Group_t *group, User_t *user) {
    return UsersAdd(group->members,user);
}

User_t **GroupGetAllUsers(Group_t *group) {
    return UsersGetAll(group->members);
}


