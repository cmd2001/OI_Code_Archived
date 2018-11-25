#include<stdio.h>

int n,in,tme,ans;

int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d",&in);
		if(in==ans) ++tme;
		else if(!tme) ans=in,tme=1;
		else --tme;
	}
	printf("%d\n",ans);
	return 0;
}
