#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=3e2+1e1,inf=0x3f3f3f3f;
int v[maxn][maxn],dep[maxn],m,n,f,t,que[maxn],s,e;
bool vis[maxn];

inline void core_bfs(int pos)
{
    for(int i=1;i<=n;i++)
    {
        if(v[pos][i]&&!vis[i]) dep[i]=dep[pos]+1,vis[i]=1,que[++e]=i;
    }
}
inline void bfs()
{
    memset(vis,0,sizeof(vis));
    memset(dep,0,sizeof(dep));
    vis[f]=1;
    que[s=e=1]=f;
    while(s<=e) core_bfs(que[s++]);
}
int dfs(int pos,int flow)
{
    if(pos==t) return flow;
    int ret=0,tmp;
    for(int i=1;i<=n;i++)
    {
        if(v[pos][i]&&(!vis[i])&&dep[i]>dep[pos])
        {
            vis[i]=1;
            tmp=dfs(i,min(flow,v[pos][i]));
            v[pos][i]-=tmp,v[i][pos]+=tmp,ret+=tmp;
        }
    }
    return ret;
}
inline int calc()
{
    int ret=0,tmp;
    while(1)
    {
        bfs();
        if(!vis[t]) return ret;
        memset(vis,0,sizeof(vis));
        while(tmp=dfs(f,inf)) ret+=tmp;
    }
}

inline void init()
{
    memset(v,0,sizeof(v));
    memset(dep,0,sizeof(dep));
    memset(que,0,sizeof(que));
    s=e=0;
    f=1,t=n;
}

int main()
{
    while(scanf("%d%d",&m,&n)==2)
    {
        init();
        for(int i=1,a,b,x;i<=m;i++)
        {
            scanf("%d%d%d",&a,&b,&x);
            v[a][b]+=x;
        }
        printf("%d\n",calc());
    }
    return 0;
}
