//
// Created by fu on 19-3-7.
//



#include <stdio.h>
#include <list.h>


typedef struct Foo {
    int a;
    int b;
}f;

int matchByPtr1(void *a, void *b){
    if(a == b){
        return 1;
    }
    return 0;
}

void printF(f *f) {
    printf("a=%d b=%d\n", f->a, f->b);
}

void find(){
    list_t *list = list_new();
    //指定match 函数
    list->match = matchByPtr1;
    struct Foo f;
    f.a = 11;
    f.b = 12;
    //加入一个节点

    void *ptr = &f;
    list_node_t *node  = list_node_new(ptr);
    list_rpush(list,node);

    list_node_t *result = list_find(list,&f);

    //这个val 就是ptr
    void *val = result->val;

    printF(val);
}


void Remove(){
    list_t *list = list_new();

    f foo;
    foo.b = 1;
    foo.a = 1;

    //插入
    list_node_t*node = list_rpush(list ,list_node_new(&foo));
    if (node->val != &foo){
        printf("error");
        exit(2);
    }


    list_remove(list,node);
    printf("list len %d\n",list->len);
}
