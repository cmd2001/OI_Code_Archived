#include<iostream>
#include<cstdio>

int n,m,ans;

int main()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	scanf("%d%d",&n,&m);
	if(m==1)ans=n;
	else if(m==2)while(n>0){ans++;n-=ans;}
	printf("%d\n",ans);
	return 0;
}
 
