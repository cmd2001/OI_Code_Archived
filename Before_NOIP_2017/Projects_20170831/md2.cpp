#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e6+1e2,maxm=1e7+1e2;

int s[maxn],t[maxm<<1],nxt[maxm<<1];
int deg[maxn],fa[maxn],dis[maxn],m,n;
bool vis[maxn];

lli chain,used,single,part;
lli ans,mod;

inline void addedge(int from,int to)
{
	static int cnt=0;
	t[++cnt]=to;
	nxt[cnt]=s[from];
	s[from]=cnt;
}
inline int findfa(int x)
{
	return fa[x]==x?x:fa[x]=findfa(fa[x]);
}
inline void doubledge(int x,int y)
{
	deg[x]++,deg[y]++;
	addedge(x,y);
	addedge(y,x);
	fa[findfa(x)]=findfa(y);
}

lli getc(lli x)
{
	lli ret=1;
	for(int i=1;i<=x;i++) ret=ret*i%mod;
	return ret;
}


inline lli work(int pos)
{
	lli ret=1,siz=0;
	static int id[maxn],from[maxn],to[maxn],tar,mxid;
	queue<int> q,qp;
	
	
	qp.push(pos);
	q.push(pos);
	mxid=dis[pos]=0;
	tar=pos;
	
	while(!q.empty())
	{
		const int pos=q.front();
		q.pop();
		siz++;
		int at=s[pos];
		while(at)
		{
			
			if(dis[t[at]]==-1)
			{
				qp.push(t[at]);
				vis[t[at]]=1;
				dis[t[at]]=dis[pos]+1;
				if(dis[t[at]]>dis[tar]) tar=t[at];
				q.push(t[at]);
			}
			at=nxt[at];
		}
		
	}
	
	if(siz==1)
	{
		++single;
		return 1;
	}
	else if(siz==2) return 2;
	else if(siz==3) return 4;
	
	while(!qp.empty())
	{
		dis[qp.front()]=-1;
		qp.pop();
	}
	
	pos=tar;
	dis[pos]=0;
	q.push(pos);
	
	
	while(!q.empty())
	{
		const int pos=q.front();
		q.pop();
		int at=s[pos];
		while(at)
		{
			if(dis[t[at]]==-1)
			{
				dis[t[at]]=dis[pos]+1;
				if(dis[t[at]]>dis[tar]) tar=t[at];
				q.push(t[at]);
				qp.push(t[at]);
				from[t[at]]=pos;
			}
			at=nxt[at];
		}
	}
	
	for(int i=tar;i;i=from[i])
	{
		int at=s[i];
		while(at)
		{
			if(t[at]!=from[i]&&t[at]!=to[i]&&deg[t[at]]>=2)
				return ans=0;
			at=nxt[at];
		}
		
		if(i==pos) break;
		to[from[i]]=i;
	}
	for(int i=pos;i!=tar;i=to[i])
		id[i]=++mxid;
	
	for(int i=pos;i!=tar;i=to[i])
	{
		lli cnt=0;
		int at=s[i];
		while(at)
		{
			cnt+=(deg[t[at]]==1);
			at=nxt[at];
		}
		if(i==pos) continue;
		ret=ret*getc(cnt)%mod;
	}
	
	while(!qp.empty())
	{
		dis[qp.front()]=-1;
		qp.pop();
	}
	
	if(mxid==2) return ret*2%mod;
	
	return ret*4%mod;
}
	
	
	
	
inline int getint()
{
	int ret=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret;
}
	
int main()
{
	n=getint(),m=getint(),mod=getint();
	
	if(m>=n) return puts("0");
	
	
	for(int i=1;i<=n;i++) fa[i]=i;
	
	for(int i=1,a,b;i<=m;i++)
	{
		a=getint(),b=getint();
		if(findfa(a)==findfa(b)) return puts("0");
		doubledge(a,b);
	}
	ans=1;
	memset(dis,-1,sizeof(dis));
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			vis[i]=1;
			lli t=work(i);
			if(t!=1)
			{
				++part;
			}
			ans=ans*t%mod;
		}
	}
	for(int i=1;i<=part;i++) ans=ans*i%mod;
	
	used=n-single;
	
	
	for(lli i=0;i<single;i++)
	{
		ans=ans*(used+2+i)%mod;
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
			
	
	
	
	
