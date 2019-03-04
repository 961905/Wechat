#include <stdio.h>
#include <math.h>
int main(){
	double a,b,c,s,sum;
	scanf("%f" "%f" "%f",a,b,c);
	if(a+b>c&&a+c>b&&b+c>a){
		s=(a+b+c)/2;
		sum=s*(s-a)*(s-b)*(s-c);
	    sum=sqrt(sum);
	    printf("%.2f",sum);
	}else{
		printf("False");
	}
	return 0;
}