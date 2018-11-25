#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e2+1e1,maxm=3e1;
int s[maxm],t[maxm*maxm],nxt[maxm*maxm],l[maxm*maxm];
int dis[maxm],ban[maxm][maxn];
int dp[maxn],cost[maxn][maxn],m,n,k,e,d,st,ed;
bool una[maxm],inq[maxm];

inline void addedge(int from,int to,int len)
{
	static int cnt=0;
	t[++cnt]=to;
	nxt[cnt]=s[from];
	s[from]=cnt;
	l[cnt]=len;
}

queue<int> q;
inline void core_spfa(int pos)
{
	int at=s[pos];
	while(at)
	{
		if((!una[t[at]])&&dis[t[at]]>dis[pos]+l[at])
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
inline int spfa()
{
	memset(dis,0x3f,sizeof(dis));
	memset(inq,0,sizeof(inq));
	while(!q.empty()) q.pop();
	q.push(st);
	inq[st]=1;
	dis[st]=0;
	while(!q.empty())
	{
		core_spfa(q.front());
		inq[q.front()]=0;
		q.pop();
	}
	return dis[ed];
}
inline void pre()
{
	for(int i=1;i<=n;i++) // i is the last day
		for(int j=1;j<=i;j++) // j is the first day
		{
			memset(una,0,sizeof(una));
			for(int k=1;k<=m;k++) // k is the road , d is the date
				for(int d=j;d<=i;d++) una[k]|=ban[k][d];
			cost[j][i]=spfa();
			if(cost[j][i]!=0x3f3f3f3f) cost[j][i]*=(i-j+1);
		}
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&e);
	for(int i=1,a,b,len;i<=e;i++)
	{
		scanf("%d%d%d",&a,&b,&len);
		addedge(a,b,len);
		addedge(b,a,len);
	}
	scanf("%d",&d);
	for(int i=1,x,a,b;i<=d;i++)
	{
		scanf("%d%d%d",&x,&a,&b);
		for(int k=a;k<=b;k++) ban[x][k]=1;
	}
	st=1,ed=m;
	pre();
	//debug<<"prepared"<<endl;
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<i;j++) dp[i]=min(dp[i],dp[j]+cost[j+1][i]+k);
	}
	debug<<dp[n]-k<<endl;
	return 0;
}
	
	
	
	
	
