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
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm],nxt[maxm],l[maxm],cnt;
int st[maxn],ed[maxn];
int w,dv,n,lam;
lli dis[maxn];
bool inq[maxn];
int f[20],g[20];

struct node
{
	int st,ed;
	friend bool operator < (const node &a,const node &b)
	{
		return a.st<b.st;
	}
}ns[maxn];

inline void addedge(int from,int to,int len)
{
	t[++cnt]=to;
	l[cnt]=len;
	nxt[cnt]=s[from];
	s[from]=cnt;
}


inline int ceildiv(int x)
{
	//if(x<0) puts("Fuck you!");
	//debug<<"x = "<<x<<endl;
	return (x+dv-1)/dv;
}

bool judge(int x)
{
	for(int i=0;i<dv;i++)
		if(x-i>=0&&*lower_bound(st+1,st+1+n,x-i)!=x-i) return 0;
	return 1;
}

inline void core_add(int x)
{
	f[0]=0;
	for(int i=1;i<dv;i++) f[i]=1;
	int lst=0,nlst,delta;
	for(int i=1;i<=n;i++)
		if(i!=x&&st[i]>=ed[x])
		{
			memset(g,0x3f,sizeof(g));
			delta=st[i]-ed[x];
			nlst=delta/dv;
			for(int k=0;k<dv;k++)
				for(int j=0;j<dv;j++)
					if(nlst*dv+k>=lst*dv+j)
					{
						g[k]=min(g[k],f[j]+ceildiv(nlst*dv+k-lst*dv-j));
					}
			addedge(x,i,g[delta%dv]);
			g[delta%dv]=inf;
			//if(nlst==lst) for(int k=0;k<dv;k++) if(f[k]>=inf) g[k]=inf;
			for(int k=0;k<dv;k++) f[k]=g[k];
			lst=nlst;
			if(judge(st[i])) return;
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
	memset(t,0,sizeof(t));
	memset(nxt,0,sizeof(nxt));
	memset(l,0,sizeof(l));
	memset(inq,0,sizeof(inq));
	memset(s,0,sizeof(s));
	memset(st,0,sizeof(st));
	memset(ed,0,sizeof(ed));
	cnt=0;
}

int main()
{
	//freopen("wormhole1.in","r",stdin);
	//freopen("debug.txt","w",stdout);
	
	int cse;
	while(w=getint())
	{
		init();
		dv=getint(),n=getint();
		lam=dv-1;
		for(int i=1;i<=n;i++)
			ns[i].st=getint(),ns[i].ed=getint();
			
		sort(ns+1,ns+1+n);
		
		//debug<<"sorted"<<endl;
		
		for(int i=1;i<=n;i++)
			st[i]=ns[i].st,ed[i]=ns[i].ed;
			
		
		st[n+1]=ed[n+1]=0;
		st[n+2]=ed[n+2]=w;
		n+=2;
		
		for(int i=1;i<=n;i++)
		{
			//debug<<"i = "<<i<<endl;
			core_add(i);
		}
		
		spfa(n-1);
		
		//debug<<"dis = "<<dis[n]<<endl;
		
		printf("%lld\n",dis[n]);
		
	}
	
	return 0;
}
		


	
