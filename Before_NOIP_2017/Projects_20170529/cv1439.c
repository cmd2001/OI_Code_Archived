#include<stdio.h>
int l,r;
int judge(int x)
{
	int i;
	if(x==1) return 0;
	for(i=2;i*i<=x;i++) if(!(x%i)) return 0;
	return 1;
}
int main()
{
	int i,ans=0;
	scanf("%d%d",&l,&r);
	for(i=l+1;i<r;i++) ans+=judge(i);
	printf("%d\n",ans);
	return 0;
}
