#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=2e3+1e2;
char g[maxn][maxn];
int t,n,vis[maxn];
bool ring;
void dfs(int pos)
{
    //debug<<"pos="<<pos<<endl;
    if(vis[pos]) return;
    vis[pos]=-1;
    for(int i=1;i<=n&&!ring;i++)
    {
        //debug<<"i="<<i<<endl;
        if(g[pos][i]&&vis[i]!=1)
        {
            //debug<<"i="<<i<<endl;
            if(vis[i]==-1) {ring=1;return;}
            dfs(i);
        }
    }
    vis[pos]=1;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        memset(vis,0,sizeof(vis));
        memset(g,0,sizeof(g));
        ring=0;
        scanf("%d",&n);
        //debug<<"n="<<n<<endl;
        for(int i=1;i<=n;i++)
        {
            scanf("%s",g[i]+1);
            for(int j=1;j<=n;j++) g[i][j]-='0';
        }
        //debug<<"dfsing"<<endl;
        for(int i=1;i<=n;i++) dfs(i);
        if(ring) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
