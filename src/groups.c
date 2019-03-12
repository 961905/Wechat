#include <string.h>
#include "groups.h"

Groups_t *NewGroups() {
    Groups_t *groups = (Groups_t *)malloc(sizeof(Groups_t ));
    memset(groups,0, sizeof(Groups_t ));
    groups->group_list = list_new();
    return groups;
}

Group_t *GroupsCreateGroup(Groups_t *groups, char *groupName) {
    if(GroupsFindGroup(groups,groupName) != NULL){
        return NULL;//groupName repeated
    }
    Group_t *group = NewGroup(++groups->groupId,groupName);
    list_rpush(groups->group_list,list_node_new(group ));
    return group;
}

Group_t *GroupsFindGroup(Groups_t *groups, char *groupName) {
    list_iterator_t *iter = list_iterator_new(groups->group_list,LIST_HEAD);
    while (1){
        list_node_t *node = list_iterator_next(iter);
        if (node == NULL){
            break;
        }else {
            Group_t *group = (Group_t*)node->val;
            if (strcmp(group->GroupName,groupName) == 0){
                return group;
            }
        }
    }
    return NULL;
}
