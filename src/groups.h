
#include "group.h"

typedef struct{
    list_t *group_list;
    int groupId;
}Groups_t;

Groups_t *NewGroups();

Group_t* GroupsCreateGroup(Groups_t *groups, char groupName[32]);

Group_t *GroupsFindGroup(Groups_t*groups,char groupName[32]);