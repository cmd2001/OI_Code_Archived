#include<bits/stdc++.h>
using namespace std;
const int maxn=15;

int n;
bool vis[maxn];
int out[maxn];

inline void dfs(int dep)
{
    if(!dep)
    {
        for(int i=n;i>0;i--) printf("%d ",out[i]);
        putchar('\n');
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            vis[i]=1;
            out[dep]=i;
            dfs(dep-1);
            vis[i]=0;
        }
    }
}

int main()
{
    scanf("%d",&n);
    dfs(n);
    return 0;
}
