#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map>
#define lli long long int
#define debug cout
using namespace std;

int p,b,n; // B^X=n;

int exgcd(int a,int b,int &x,int &y)
{
	if(!b)
	{
		x=1,y=0;
		return a;
	}
	int ret=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return ret;
}
inline void work()
{
	map<int,int> m;
	map<int,bool> vis;
	int now=1,rev,tmp,nn=n,sq=sqrt(p);
	
	m[1]=0,vis[1]=1;
	
	
	for(int i=1;i<sq;i++)
	{
		now=(lli)now*b%p;
		if(!vis[now]) vis[now]=1,m[now]=i;
	}
	
	now=(lli)now*b%p;
	
	exgcd(now,p,rev,tmp);
	
	/*if(rev>0) rev%=p;
	else rev=rev%p+p;*/
	rev%=p;
	rev+=rev<0?p:0;
	//debug<<"rev="<<rev<<endl;
	
	
	for(int i=0;i<=sq;i++)
	{
		//debug<<"i="<<i<<"nn="<<nn<<endl;
		if(vis[nn])
		{
			printf("%d\n",i*sq+m[nn]);
			return;
		}
		nn=(lli)nn*rev%p;
	}
	
	puts("no solution");
}

int main()
{
	//freopen("dat.txt","w",stdout);
	while(scanf("%d%d%d",&p,&b,&n)!=EOF) work();
	return 0;
}
	
		
