

#include <list.h>

struct Foo {
    int a;
    int b;
};
int main(){
    list_t *list = list_new();
    struct Foo f;
    f.a = 1;
    f.b = 2;
    list_rpush(list,list_node_new(&f));

    //....
    //...
}