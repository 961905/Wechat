#include <stdio.h>

int add(int a,int b){
    return a+b;
}

int main(){

    int b = add(1,add(1,1));


    int num = 1000;
    void *pVoid = &num;
    int *temp = (int*)pVoid;
    int num2 = *temp;
    printf("%d",b);
}