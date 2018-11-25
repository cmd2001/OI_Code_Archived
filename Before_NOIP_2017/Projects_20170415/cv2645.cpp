#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+1e2,maxm=2e4+1e2;
long long ans[maxn];
int s[maxn],tme[maxn],n,m,cnt;
bool vis[maxn],bug;
queue<int> q;
struct edge
{
    int to,nxt;
    long long int len;
}g[maxm];
void addedge(int from,int to,int len)
{
    g[++cnt].nxt=s[from],s[from]=cnt;
    g[cnt].len=len,g[cnt].to=to;
}
inline void init()
{
    memset(ans,0x3f,sizeof(ans));
    memset(s,0,sizeof(s));
    memset(vis,0,sizeof(vis));
    memset(g,0,sizeof(g));
    memset(tme,0,sizeof(tme));
    cnt=0,bug=0;
}
void update(int x)
{
    if(tme[x]>n) {bug=1;return;}
    int at=s[x],t,l;
    while(at)
    {
        t=g[at].to,l=g[at].len;
        if(ans[t]>ans[x]+l)
        {
            ans[t]=ans[x]+l;
            if(!vis[t]) {q.push(t);++tme[t];}
        }
        at=g[at].nxt;
    }
}
int main()
{
    while(scanf("%d%d",&n,&m)==2&&n&&m)
    {
        init();
        long long int c,d;
        for(int i=1,a,b;i<=m;i++)
        {
            scanf("%d%d%lld%lld",&a,&b,&c,&d);
            addedge(a,b,c);addedge(b,a,d);
        }
        q.push(1);
        vis[1]=tme[1]=1;
        ans[1]=0;
        while(!q.empty()&&!bug)
        {
            update(q.front());
            vis[q.front()]=0;
            q.pop();
        }
        if(ans[n]!=ans[0]&&!bug)printf("%lld\n",ans[n]);
        else puts("No such path");
    }
    return 0;
}
