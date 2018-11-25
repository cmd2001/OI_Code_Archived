#include<bits/stdc++.h>
using namespace std;
const int maxn=6e4,inf=0x3fffffff;
int st[maxn],dep[maxn],to[8*maxn],nxt[8*maxn],flow[8*maxn];
int m,n,f,t,tmp;
bool vis[maxn];
inline void addedge(int a,int b,int f)
{
    static cnt=1;
    to[++cnt]=b;
    nxt[cnt]=s[a];
    flow[cnt]=f;
    s[a]=cnt;
    to[++cnt]=a;
    nxt[cnt]=s[b];
    flow[cnt]=f;
    s[b]=cnt;
}

queue<int> q;

void bfs(int pos)
{
    int at=s[pos];
    while(at)
    {
        if(vis[to[at]])
        {
            at=nxt[at];
            continue;
        }
        vis[t[at]]=1;
        dep[t[at]]=dep[pos]+1;
        q.push(t[at]);
    }
}
int dfs(int pos,int maxf)
{
    if(pos==t) return maxf;
    int ret=0,tmp,at=s[pos];
    while(at)
    {
        if(dep[to[at]]>dep[pos]&&flow[at]&&!vis[to[at]])
        {
            vis[to[at]]=1;
            tmp=dfs(to[at],min(maxf,flow[at]));
            ret+=tmp;
            flow[at]-=tmp;
            flow[at^1]+=tmp;
            maxf-=tmp;
        }
        at=nxt[at];
    }
    return ret;
}
inline int calc()
{
    int ret=0,tmp;
    while(1)
    {
        memset(vis,0,sizeof(vis));
        memset(dep,0,sizeof(dep));
        while(!q.empty()) q.pop();
        q.push(s);
        dep[s]=1;
        while(!q.empty())
        {
            bfs(q.front());
            q.pop();
        }
        if(!vis[t]) return ret;
        memset(vis,0,sizeof(vis));
        while(tmp=dfs(s,inf))
        {
            ret+=tmp;
            memset(vis,0,sizeof(vis));
        }
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<m;j++)
        {
            scanf("%d",&tmp);
            addedge(i*m+j,i*m+j+1,tmp);
        }
    }
    for(int i=1;i<n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&tmp);
            addedge(i*m+j,(i+1)*m+j,tmp);
        }
    }

