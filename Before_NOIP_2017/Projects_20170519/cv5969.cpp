#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=2e2+1e1;
int fa[maxn],n,ans;
bool vis[maxn];
int findfa(int x)
{
    return fa[x]==x?x:fa[x]=findfa(fa[x]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1,t;i<=n;i++) while(scanf("%d",&t)&&t) if(findfa(t)==t) fa[t]=findfa(i);
    for(int i=1;i<=n;i++) if(findfa(i)==i) ++ans;
    printf("%d\n",ans);
    return 0;
}
