#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int prev[maxn],next[maxn];
lli in[maxn];
long long int ans;

struct node
{
	int id;
	node(int ii=0){id=ii;}
	friend bool operator < (const node &a,const node &b)
	{
		return in[a.id]==in[b.id]?a.id<b.id:in[a.id]<in[b.id];
	}
};

set<node> s;

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	static int n,k;
	
	n=getint(),k=getint();
	
	for(int i=1;i<=n;i++) in[i]=getint();
	for(int i=1;i<n;i++) in[i]=in[i+1]-in[i];
	in[0]=in[n]=2147483647;
	n--;
	
	for(int i=1;i<=n;i++) s.insert(node(i));
	for(int i=1;i<=n;i++) prev[i]=i-1,next[i]=i+1;
	prev[1]=0,next[n]=0;
	
	for(int i=1;i<=k;i++)
	{
		const int x=(*s.begin()).id;
		//debug<<"x="<<x<<endl;
		//debug<<"in="<<in[x]<<endl;
		ans+=in[x];
		
		if(!prev[x])
		{
			s.erase(node(x));s.erase(node(next[x]));
			prev[next[x]]=0;
			if(next[next[x]]) prev[next[next[x]]]=0;
		}
		else if(!next[x])
		{
			s.erase(node(x));s.erase(node(prev[x]));
			next[prev[x]]=0;
			if(prev[prev[x]]) next[prev[prev[x]]]=0;
		}
		else
		{
			int l=in[prev[x]]+in[next[x]]-in[x];
			s.erase(node(x));s.erase(node(prev[x]));s.erase((next[x]));
			in[x]=l;
			prev[x]=prev[prev[x]],next[x]=next[next[x]];
			if(next[x]) prev[next[x]]=x;
			if(prev[x])next[prev[x]]=x;
			s.insert(node(x));
		}
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
			
		

