#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e3+1e2,maxm=maxn*maxn;
const int mod=(long long int)(1LL<<31)-1;

int s[maxn],t[maxm<<1],nxt[maxm<<1],l[maxm<<1];
int dis[maxn],qu[maxn],n,m;
bool inq[maxn];
lli ans=1;

inline void addedge(int from,int to,int len)
{
	static int cnt=0;
	t[++cnt]=to;
	l[cnt]=len;
	nxt[cnt]=s[from];
	s[from]=cnt;
}

inline void spfa()
{
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0,inq[1]=1;
	queue<int> q;
	q.push(1);
	
	while(!q.empty())
	{
		const int x=q.front();
		q.pop();
		inq[x]=0;
		
		int at=s[x];
		while(at)
		{
			const int to=t[at];
			if(dis[t[at]]>dis[x]+l[at])
			{
				dis[t[at]]=dis[x]+l[at];
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

bool cmp(const int &x,const int &y)
{
	return dis[x]<dis[y];
}

inline void getans()
{
	for(int i=1;i<=n;i++) qu[i]=i;
	
	sort(qu+1,qu+1+n,cmp);
	
	for(int i=2,tmp;i<=n;i++)
	{
		tmp=0;
		const int x=qu[i];
		int at=s[x];
		while(at)
		{
			if(l[at]+dis[t[at]]==dis[x]) tmp++;
			at=nxt[at];
		}
		ans=ans*tmp%mod;
	}
}

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	
	n=getint(),m=getint();
	
	for(int i=1,a,b,l;i<=m;i++)
	{
		a=getint(),b=getint(),l=getint();
		addedge(a,b,l);
		addedge(b,a,l);
	}
	
	spfa();
	getans();
	
	printf("%lld\n",ans);
	
	return 0;
}
	
