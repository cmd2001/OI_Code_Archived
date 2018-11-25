#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=9e4,maxe=72e4,inf=0x7fffffff;
int s[maxn],t[maxe],f[maxe],nxt[maxe];
int from,to,m,n;
int dep[maxn];
bool vis[maxn];
queue<int> q;

inline void addedge(int from,int to,int flow)
{
    static int cnt=1;
    t[++cnt]=to;
    f[cnt]=flow;
    nxt[cnt]=s[from];
    s[from]=cnt;
}

inline void core_bfs(int pos)
{
    int at=s[pos];
    while(at)
    {
        if(f[at]&&!vis[t[at]])
        {
            vis[t[at]]=1;
            q.push(t[at]);
            dep[t[at]]=dep[pos]+1;
        }
        at=nxt[at];
    }
}
inline void get_level()
{
    while(!q.empty()) q.pop();
    memset(vis,0,sizeof(vis));
    memset(dep,0,sizeof(dep));
    dep[from]=1;
    vis[from]=1;
    q.push(from);
    while(!q.empty())
    {
        core_bfs(q.front());
        q.pop();
    }
}
int dfs(int pos,int flow)
{
    if(pos==to) return flow;
    int ret=0,tmp,at=s[pos];
    while(at)
    {
        if(dep[t[at]]>dep[pos]&&f[at]&&!vis[t[at]])
        {
            vis[t[at]]=1;
            tmp=dfs(t[at],min(flow,f[at]));
            ret+=tmp;
            flow-=tmp;
            f[at]-=tmp;
            f[at^1]+=tmp;
        }
        at=nxt[at];
    }
    return ret;
}
inline int get_flow()
{
    int deb=1;
    int ret=0,tmp;
    while(1)
    {
        get_level();
        if(!vis[to]) return ret;
        while(1)
        {
            memset(vis,0,sizeof(vis));
            vis[from]=1;
            tmp=dfs(from,inf);
            if(!tmp) break;
            ret+=tmp;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    from=1*m+1,to=n*m+m;
    for(int i=1,tmp;i<=n;i++)
    {
        for(int j=1;j<m;j++)
        {
            scanf("%d",&tmp);
            addedge(i*m+j,i*m+j+1,tmp);
            addedge(i*m+j+1,i*m+j,tmp);
        }
    }
    for(int j=1,tmp;j<=m;j++)
    {
        for(int i=1;i<n;i++)
        {
            scanf("%d",&tmp);
            addedge(i*m+j,(i+1)*m+j,tmp);
            addedge((i+1)*m+j,i*m+j,tmp);
        }
    }
    printf("%d\n",get_flow()>>1);
    return 0;
}

