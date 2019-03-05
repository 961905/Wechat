

#include <list.h>
#include <stdio.h>

typedef struct Foo {
    int a;
    int b;
}Foo ;

void printFoo(Foo *foo){
    printf("a= %d b= %d",foo->a,foo->b);
}

int matchByPtr(void *a, void *b){
    if(a == b){
        return 1;
    }
    return 0;
}

void testListFind(){
    list_t *list = list_new();
    //指定match 函数
    list->match = matchByPtr;
    struct Foo f;
    f.a = 1;
    f.b = 2;
    //加入一个节点

    void *ptr = &f;
    list_node_t *node  = list_node_new(ptr);
    list_rpush(list,node);

    list_node_t *result = list_find(list,&f);

    //这个val 就是ptr
    void *val = result->val;

    if (val != ptr){
        printf("error");
        exit(2);
    }

    Foo *fTemp = (Foo*)val;
    if (fTemp != ptr){
        printf("error");
        exit(2);
    }
    printFoo(fTemp);
}
int main(){
    testListFind();
}