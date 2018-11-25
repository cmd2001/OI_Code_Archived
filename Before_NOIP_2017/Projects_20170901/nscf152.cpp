#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e4+1e2,maxl=1e2+1e1;

int d[maxn],c[maxn];
int n,s,t;
lli f[maxl],ans;

struct node
{
	int st,lst;
	int tar;
	friend bool operator < (const node &a,const node &b)
	{
		return a.st+a.lst==b.st+b.lst?a.st<b.st:a.st+a.lst<b.st+b.lst;
	}
}cls[maxl];

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	t=getint(),s=getint(),n=getint();
	for(int i=1;i<=s;i++)
		cls[i].st=getint(),cls[i].lst=getint(),cls[i].tar=getint();
	for(int i=1;i<=n;i++)
		c[i]=getint(),d[i]=getint();
	
	sort(cls+1,cls+1+s);
	
	for(int i=1;i<=s;i++)
	{
		for(int j=1;j<=s;j++)
		{
			const int days=cls[i].st-(cls[j].st+cls[j].lst);
			const int lim=cls[j].tar;
			for(int k=1;k<=s;k++)
				if(c[k]<=lim)
					f[i]=max(f[i],f[j]+(days/d[k]));
		}
		const int days=cls[i].st;
		//debug<<"days = "<<days<<endl;
		for(int k=1;k<=n;k++)
			if(c[k]<=1)
			{
				//debug<<"k = "<<k<<endl;
				//debug<<"d = "<<d[k]<<endl;
				f[i]=max(f[i],(lli)(days/d[k]));
			}
		//debug<<"f[i] = "<<f[i]<<endl;
	}
	
	for(int i=1;i<=s;i++)
	{
		const int &lim=cls[i].tar;
		const int &days=t-(cls[i].st+cls[i].lst);
		for(int k=1;k<=n;k++)
			if(c[k]<=lim)
				ans=max(ans,f[i]+(days/d[k]));
	}
	
	for(int k=1;k<=n;k++)
			if(c[k]<=1)
				ans=max(ans,(lli)(t/d[k]));
	
	//debug<<"ans = "<<ans<<endl;
	
	printf("%lld\n",ans);
	
	return 0;
}

