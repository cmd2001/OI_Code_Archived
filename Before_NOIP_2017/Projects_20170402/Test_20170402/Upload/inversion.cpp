#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
//#include"orz.h"
//using namespace orz;
//brute force solution by Cmd2001
int gcd(int a,int b)
{
	while(a%b)
	{
		a%=b;
		a^=b^=a^=b;
	}
	return b;
}
inline bool judge(int x)
{
	if(x==1) return 1;
	for(int i=2,sq=sqrt(x);i<=sq;i++)
	{
		if(!(x%i)) return 1;
	}
	return 0;
}
int t,m,n;
unsigned long long int ans;
int main()
{
	freopen("inversion.in","r",stdin);
	freopen("inversion.out","w",stdout);
	scanf("%d",&t);
	while(t--)
	{
		ans=0;
		scanf("%d%d",&m,&n);
		if(m>10000||n>10000) {printf("Orz\n");exit(0);}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(!judge(gcd(i,j))) ++ans;
		printf("%llu\n",ans);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
//orzlh,orzlh,orzlh	
//orzlh,orzlh,orzlh	
//orzlh,orzlh,orzlh	
//orzzrtorzzrtorzzrt
//orzzrtorzzrtorzzrt
//orzzrtorzzrtorzzrt
