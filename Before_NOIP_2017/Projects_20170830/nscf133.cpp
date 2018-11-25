#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=4e1+1e1,maxm=1.6e3+5e2;

int s[maxn],t[maxm],nxt[maxm],l[maxm],cnt;
int st[maxn],ed[maxn];
int w,dv,n,lam;
lli dis[maxn];
bool inq[maxn];

inline void addedge(int from,int to,int len)
{
	t[++cnt]=to;
	l[cnt]=len;
	nxt[cnt]=s[from];
	s[from]=cnt;
}

inline void core_add(int x)
{
	for(int i=1;i<=n;i++)
		if(i!=x&&st[i]>=ed[x])
		{
			addedge(x,i,(st[i]-ed[x]+lam)/dv);
			//if(!((st[i]-ed[x])%dv)) break;
		}
}

inline void spfa(int st)
{
	memset(inq,0,sizeof(inq));
	memset(dis,0x3f,sizeof(dis));
	queue<int> q;
	dis[st]=0;
	inq[st]=1;
	q.push(st);
	
	while(!q.empty())
	{
		const int pos=q.front();
		q.pop();
		inq[pos]=0;
		
		int at=s[pos];
		while(at)
		{
			if(dis[t[at]]>dis[pos]+l[at])
			{
				dis[t[at]]=dis[pos]+l[at];
				if(!inq[t[at]])
				{
					q.push(t[at]);
					inq[t[at]]=1;
				}
			}
			at=nxt[at];
		}
	}
}

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

inline void init()
{
	memset(s,0,sizeof(s));
	cnt=0;
}

int main()
{
	freopen("wormhole1.in","r",stdin);
	
	while(w=getint())
	{
		init();
		dv=getint(),n=getint();
		lam=dv-1;
		for(int i=1;i<=n;i++)
			st[i]=getint(),ed[i]=getint();
		
		st[n+1]=ed[n+1]=0;
		st[n+2]=ed[n+2]=w;
		n+=2;
		
		for(int i=1;i<=n;i++)
			core_add(i);
		
		spfa(n-1);
		
		//debug<<"dis = "<<dis[n]<<endl;
		
		printf("%lld\n",dis[n]);
		
	}
	
	return 0;
}
		


	
