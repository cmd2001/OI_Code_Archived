#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e3+1e2,base=1000000;

int prime[maxn],tme[maxn],cnt,n,tot,c;
int in[maxn],ans[maxn],len=1;
bool vis[maxn];

inline void getprime(int lim)
{
	for(int i=2;i<=lim;i++)
	{
		if(!vis[i]) prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=lim;j++)
		{
			vis[i*prime[j]]=1;
			if(!(i%prime[j])) break;
		}
	}
}
inline void divide(int x,int ope)
{
	if(!x) debug<<"!!warning!!	in divide x==0"<<endl,exit(0);
	
	for(int i=1;i<=cnt;i++)
	{
		while(!(x%prime[i])) x/=prime[i],tme[i]+=ope;
	}
}
inline void update(int x,int ope) // update x! into ans
{
	//debug<<"in update x="<<x<<"ope="<<ope<<endl;
	for(int i=1;i<=x;i++) divide(i,ope);
}
inline void mul(int x) // multi x into ans
{
	//debug<<"x="<<x<<endl;
	for(int i=1;i<=len;i++) ans[i]*=x;
	for(int i=1;i<=len;i++) ans[i+1]+=ans[i]/base,ans[i]%=base;
	while(ans[len+1])
	{
		len++;
		ans[len+1]+=ans[len]/base;
		ans[len]%=base;
	}
}
inline void putans()
{
	for(int i=len;i>0;i--)
	{
		if(i==len) printf("%d",ans[i]);
		else printf("%06d",ans[i]);
	}
	putchar('\n');
}

int main()
{
	ans[1]=1;
	scanf("%d",&n);
	getprime(n);
	if(n==1)
	{
		int x;
		scanf("%d",&x);
		if(!x) puts("1");
		else puts("0");
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&in[i]);
		if(!in[i])
		{
			puts("0");
			return 0;
		}
		if(in[i]==-1) ++c;
		else	in[i]--,tot+=in[i];
	}
	//debug<<"input complete"<<endl;
	if(tot>n-2)
	{
		puts("0");
		return 0;
	}
	update(n-2,1);
	update(n-2-tot,-1);
	//debug<<"first two update completed"<<endl;
	for(int i=1;i<=n;i++) if(in[i]) update(in[i],-1);
	//for(int i=1;i<=cnt;i++) debug<<tme[i]<<endl;
	//return 0;
	for(int i=1;i<=cnt;i++)
		while(tme[i]--) 
			mul(prime[i]);
	//debug<<"multed"<<endl;
	for(int i=1;i<=n-2-tot;i++) mul(c);
	putans();
	return 0;
}
	
	
	
