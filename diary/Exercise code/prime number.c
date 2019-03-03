#include <stdio.h>

int prime(int n);

int main(){
	int n,sum;

    printf("输入一个整数：");
    scanf("%d",&n);
	
	sum=prime(n);

    if(sum==0){
        printf("%d是素数。\n", n);
    }else{
        printf("%d不是素数。\n", n);
    }
}

int prime(int n){
	int a=0;
	for(int i=2;i<n;i++){
        if(n%i==0){
            a++;  
        }
    }
	
   return a;
}
