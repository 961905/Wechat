#include <stdio.h>
struct City{
 char city[20];
 double spring;
 double summer;
 double autumn;
 double winter;
 double sum;
}


main()
{
 int a=0,i=0;
 double max=0,mix=0;
 struct City c[10];
 for(i=0;i<10;i++){
	printf("请输入城市名:\n");
	scanf("%s",&(c[i].city));
	printf("请输入春季温度:\n");
	scanf("%d",&(c[i].spring));
	printf("请输入夏季温度:\n");
	scanf("%d",&(c[i].summer));
	printf("请输入秋季温度:\n");
	scanf("%d",&(c[i].autumn));
	printf("请输入冬季温度:\n");
	scanf("%d",&(c[i].winter));
	c[i].sum=(c[i].spring+c[i].summer+c[i].autumn+c[i].winter)/4;
	}


  max=c[0].sum;

 for(i=0;i<10;i++){
	//if(max<c[i].sum){
	printf("城市名:%s\n",c[i].city);
	printf("春季温度:%d\n",c[i].spring);
	printf("夏季温度:%d\n",c[i].summer);
	printf("秋季温度:%d\n",c[i].autumn);
	printf("冬季温度:%d\n",c[i].winter);
	printf("全年平均温度:%d\n",c[i].sum);
	/*}else{
	printf("城市名:%s\n",c[i].city);
	printf("春季温度:%d\n",c[i].spring);
	printf("夏季温度:%d\n",c[i].summer);
	printf("秋季温度:%d\n",c[i].autumn);
	printf("冬季温度:%d\n",c[i].winter);
	printf("全年平均温度:%d\n",c[i].sum);}
 */
}
}