#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e3+1e2;
bool g[maxn][maxn];
int dfn[maxn],low[maxn],n,m;
int ans[maxn][maxn],cnt,ctr;
bool vis[maxn],in[maxn];
stack <int> s;
void dfs(int pos)
{
    low[pos]=dfn[pos]=ctr++;
    s.push(pos);
    in[pos]=1;
    for(int i=1;i<=n;i++)
    {
        if(g[pos][i]&&!vis[i])
        {
            vis[i]=1;
            dfs(i);
        }
        if(g[pos][i]&&in[i]) low[pos]=min(low[pos],low[i]);
    }
    if(low[pos]==dfn[pos])
    {
        int at=1;
        cnt++;
        while(s.top()!=pos)
        {
            in[ans[cnt][at++]=s.top()]=0;
            s.pop();
        }
        ans[cnt][at++]=s.top();
        s.pop();
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b),g[a][b]=1;
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            vis[i]=1;
            dfs(i);
        }
    }
    debug<<"cnt="<<cnt<<endl;
    return 0;
}




