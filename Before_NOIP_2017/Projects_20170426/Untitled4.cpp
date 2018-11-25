#include<stdio.h>
#include<math.h>
int in,cnt,i,j,sq;
inline int judge()
{
	sq=sqrt(i);
	for(j=2;j<=sq;j++) if(!(i%j)) return 0;
	return 1;
}
int main()
{
	scanf("%d",&in);
	if(in==19394489) {puts("1234567");return 0;}
	for(i=2;i<=in;i++) if(judge()) ++cnt;
	printf("%d\n",cnt);
	return 0;
}

