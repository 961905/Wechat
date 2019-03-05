
#include <stdio.h>
#include <list.h>
#include <user.h>


/*
struct Foo {
    int a;
    int b;
};

int main(){
    list_t *list = list_new();
    struct Foo f;
    f.a = 1;
    f.b = 2;
    f.sum=list_rpush(list,list_node_new(&f));

    //....
    //...
}

*/


struct F {
    int a;
    int b;
    int sum;
};
int main(){
    struct F f;
    f.a=2;
    f.b=4;
    list_node_t *list=list_new(f.b);
    list_rpush(list,list_node_new(&f.a));

     f.sum=f.a+f.b;




    printf("%d",f.sum);


}