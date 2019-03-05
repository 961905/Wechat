
#include <stdio.h>
#include <list.h>
#include <stdio.h>

typedef struct Foo {
    int a;
    int b;
}Foo ;

void printFoo(Foo *foo){
    printf("a=%d b=%d\n",foo->a,foo->b);
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

void testListRemove(){
    list_t *list = list_new();

    Foo foo;
    foo.b = 1;
    foo.a = 1;

    //插入
    list_node_t*node = list_rpush(list ,list_node_new(&foo));
    if (node->val != &foo){
        printf("error");
        exit(2);
    }

    //删除
    list_remove(list,node);
    printf("list len %d\n",list->len);
}

void testListIterator(){
    list_t *list = list_new();
    for (int i = 0; i <10; ++i) {
        //申请内存
        int *num = (int*)malloc(sizeof(int));
        //给指针赋值
        *num = i;
        //插入到list 里面
        list_rpush(list,list_node_new(num));
    }

    list_iterator_t *iter = list_iterator_new(list,LIST_HEAD);
    list_node_t *node = NULL;
    while(1){
        node = list_iterator_next(iter);
        if (node == NULL){
            //到了list尾了，遍历结束
            break;
        }
        void *val = node->val;
        //指针强制性转换
        int *num = (int*)val;
        printf("num %d\n",*num);
    }
}

int main(){
    printf("-----------testListFind--------------\n");
    testListFind();
    printf("----------testListRemove-------------\n");
    testListRemove();
    printf("---------testListIterator------------\n");
    testListIterator();
    printf("---------------------");
}
