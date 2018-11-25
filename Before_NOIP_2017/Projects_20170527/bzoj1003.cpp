#include<bits/stdc++.h>
using namespace std;
const int maxn=1e2+1e1,maxm=3e1;
int s[maxn],t[maxm*maxn],nxt[maxm*maxm],l[maxm*maxm];
int dp[maxn],cost[maxn],dis[maxm],una[maxm][3];
bool un[maxm],inq[maxm];
int n,m,k,e,d;
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
		if(!un[t[at]])
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
		}
	}
}
inline void spfa()
{
	memset(dis,0x3f,sizeof(dis));
	memset(inq,0,sizeof(inq));
	while(!q.empty()) q.pop();
	dis[st]=0;
	q.push(st);
	while(!q.empty())
	{
		inq[q.top()]=0;
		core_spfa(q.top());
		q.pop();
	}
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&e);
	for(int i=1,a,b,l;i<=e;i++)
	{
		scanf("%d%d%d",&a,&b,&l);
		addedge(a,b,l);
		addedge(b,a,l);
	}
	scanf("%d",&d);
	for(int i=1,x,a,b;i<=d;i++)
	{
		scanf("%d%d%d",&x,&a,&b);
		una[i][0]=x;
		una[i][1]=a;
		una[i][2]=b;
	}
	for(int i=1;i<=n;i++)
	{
		memset(un,0,sizeof(una));
		for(int i=1;i<=d;i++) if(una[i][1]<=i&&i<=una[i][2]) un[una[i][1]]=1;
		spfa();
		cost[i]=dis[m];
		for(int k=1;k<i;k++) dp[i]=min(dp[j],)
	}
	return 0;
}
		
