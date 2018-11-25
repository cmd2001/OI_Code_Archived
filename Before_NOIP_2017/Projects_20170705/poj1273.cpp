#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
#define int
using namespace std;
const int maxn=2e2+1e1;
const int inf=0x3f3f3f3f;

int in[maxn][maxn],dep[maxn],m,n;
queue<int> q;

inline void core_bfs(int pos)
{
    for(int i=1;i<=m;i++)
    {
        if(in[pos][i]&&dep[i]==-1)
        {
            dep[i]=dep[pos]+1;
            q.push(i);
        }
    }
}
inline void bfs()
{
    memset(dep,-1,sizeof(dep));
    dep[1]=1;
    q.push(1);
    while(!q.empty())
    {
        core_bfs(q.front());
        q.pop();
    }
}

inline int dfs(int pos,int flow)
{
    if(pos==m) return flow;
    int ret=0,now=0;
    for(int i=1;i<=m;i++)
    {
        if(in[pos][i]&&dep[i]>dep[pos])
        {
            now=dfs(i,min(flow,in[pos][i]));
            ret+=now,
            in[pos][i]-=now,
            in[i][pos]+=now;
            //!!!// flow-=now;
            if(!flow) break;
        }
    }
    if(!ret) dep[ret]=-1;
    return ret;
}

inline int dinic()
{
    int ret=0,now=0;
    while(1)
    {
        bfs();
        if(dep[m]==-1) break;
        while(now=dfs(1,inf)) ret+=now;
    }
    return ret;
}

int main()
{
    scanf("%d%d",&n,&m);
    {
        memset(in,0,sizeof(in));
        for(int i=1,a,b,c;i<=n;i++)
        {
            scanf("%d%d%d",&a,&b,&c);
            in[a][b]=c;
        }

        printf("%d\n",dinic());
    }
    return 0;
}



