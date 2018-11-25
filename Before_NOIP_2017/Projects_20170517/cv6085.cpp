#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+1e2;
int fa[maxn],m,n,a,b;
int findfa(int x)
{

    return fa[x]==x?x:fa[x]=findfa(fa[x]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) fa[i]=i;
    while(m--)
    {
        scanf("%d",&a,&b);
        fa[findfa(a)]=fa[findfa(b)];
    }
    if(findfa(1)==findfa(n)) puts("please go home to sleep");
    else puts("confession");
    return 0;
}
