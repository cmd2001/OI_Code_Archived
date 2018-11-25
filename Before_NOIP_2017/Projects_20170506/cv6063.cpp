#include<bits/stdc++.h>
using namespace std;
const int maxn=55;
bool g[maxn][maxn],vis[maxn];
int ans[maxn],n;

bool dfs(int pos,int cter)
{
    ans[cter]=pos;
    if(cter==n) return 1;
    for(int i=1;i<=n;i++)
    {
        if(g[pos][i]&&!vis[i])
        {
            vis[i]=1;
            if(dfs(i,cter+1)) return 1;
            vis[i]=0;
        }
    }
    return 0;
}
int main()
{
    scanf("%d",&n);
    int a,b;
    while(scanf("%d%d",&a,&b)==2) g[a][b]=g[b][a]=1;
    for(int i=1;i<=n;i++) g[0][i]=1;
    vis[0]=1;
    dfs(0,0);
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}
