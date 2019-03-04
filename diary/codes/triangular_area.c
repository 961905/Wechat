#include <stdio.h>
#include <math.h>
int main(){
	double a,b,c,s,sum;
	scanf("%lf" "%lf" "%lf",&a,&b,&c);
	if(a+b>c&&a+c>b&&b+c>a){
		s=(a+b+c)/2;
		sum=s*(s-a)*(s-b)*(s-c);
	    sum=sqrt(sum);
	    printf("%.2lf\n",sum);
	}else{
		printf("False\n");
	}
	return 0;
}