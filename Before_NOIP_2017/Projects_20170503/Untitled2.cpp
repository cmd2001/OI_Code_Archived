#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e2+1e1;
bool g[maxn][maxn],vis[maxn],must[maxn];
int fa[maxn],ans,n;
bool none;
inline void debugg(){for(int i=1;i<=n;i++) {for(int j=1;j<=n;j++) printf("%d",g[i][j]);printf("\n");}}
bool dfs(int pos)
{
    for(int i=1;i<=n;i++)
    {
        if(g[pos][i]&&!vis[i])
        {
            vis[i]=1;
            if((!fa[i])||dfs(fa[i])) {fa[i]=pos;return 1;}
        }
    }
    return 0;
}
void getbin()
{
    for(int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));
        dfs(i);
    }
}
void getans()
{
    for(int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));
        const int f=fa[i];
        g[f][i]=0;
        fa[i]=0;
        if(dfs(f)) g[f][i]=1;
        else
        {
            g[f][i]=1;
            must[i]=1;
            fa[i]=f;
        }
    }
}
int main()
{
    memset(g,1,sizeof(g));
    scanf("%d",&n);
    int a,b;
    while(scanf("%d%d",&a,&b)==2&&a&&b) g[b][a]=0;
    getbin();
    getans();
    for(int i=1;i<=n;i++) if(must[i]) printf("%d %d\n",i,fa[i]),none=1;
    if(!none) puts("none");
    //don't forget output "none"!
    return 0;
}
