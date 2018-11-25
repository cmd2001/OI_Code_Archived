#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1e3+1e2,maxm=1e5+1e2;
const int inf=0x7fffffff;
const double eps=1e-3;

int s[maxn],t[maxm],nxt[maxm],l[maxm],n,m;
int val[maxn],tme[maxn];
bool inq[maxn];
double dis[maxn],mid,ans;

inline void addedge(int from,int to,int len)
{
	static int cnt=0;
	t[++cnt]=to;
	l[cnt]=len;
	nxt[cnt]=s[from];
	s[from]=cnt;
	//debug<<"from="<<from<<endl;
	//debug<<"in addedge cnt="<<cnt<<endl;
	//debug<<"s from="<<s[from]<<endl;
}

inline double getd(int id)
{
	return (double)-val[t[id]]+mid*(double)l[id];
}

inline bool spfa(int st)
{
	queue<int> q;
	for(int i=1;i<=n;i++) dis[i]=inf,tme[i]=inq[i]=0;
	dis[st]=0;
	inq[st]=1;
	q.push(st);
	
	while(!q.empty())
	{
		const int x=q.front();
		q.pop();
		inq[x]=0;
		
		//debug<<"in spfa x="<<x<<endl;
		
		int at=s[x];
		
		//debug<<"at="<<at<<endl;
		
		while(at)
		{
			if(dis[t[at]]>dis[x]+getd(at))
			{
				dis[t[at]]=dis[x]+getd(at);
				//debug<<"dis="<<dis[t[at]]<<endl;
				if(++tme[t[at]]>n) return 1;
				if(!inq[t[at]])
				{
					q.push(t[at]);
					inq[t[at]]=1;
				}
			}
			at=nxt[at];
		}
	}
	
	return 0;
}

inline double getans()
{
	double l=0.0,r=2000.0;
	while(r-l>eps)
	{
		//debug<<"r="<<r<<"l="<<l<<endl;
		mid=(l+r)/2.0;
		if(spfa(1)) l=mid;
		else r=mid;
	}
	return mid;
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

inline void getin()
{
	n=getint(),m=getint();
	
	
	for(int i=1;i<=n;i++) val[i]=getint();
	
	for(int i=1,a,b,l;i<=m;i++)
	{
		a=getint(),b=getint(),l=getint();
		addedge(a,b,l);
	}
}

int main()
{
	getin();
	
	ans=getans();
	
	printf("%.2f\n",ans);
	
	return 0;
}
	
	
	

