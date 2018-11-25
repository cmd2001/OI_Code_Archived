#include<iostream>
#include<cstdio>
#include<cstring>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
int fa[maxn],dat[maxn],in[maxn],sta[maxn],ans[maxn],tme[maxn],cnt,anst,m,n;
char q[10];
int findfa(int x)
{
    return x==fa[x]?x:fa[x]=findfa(fa[x]);
}
inline int calc(int x)
{
    while(!findfa(x)) x=fa[x]=dat[x];
    return findfa(x);
}
int main()
{
    tme[1]=0x3fffffff,fa[1]=1;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=n;i++)
    {
        scanf("%d%d",&a,&b);
        dat[b]=a;
    }
    for(int i=1,x;i<=m;i++)
    {
        scanf("%s%d",q,&x);
        if(q[0]=='Q') in[i]=x;
        else in[i]=x,sta[i]=1,tme[x]++,fa[x]=x;
    }
    for(int i=m;i>0;i--)
    {
        if(!sta[i]) ans[++anst]=calc(in[i]);
        else
        {
            tme[in[i]]--;
            if(!tme[in[i]]) fa[in[i]]=dat[in[i]];
        }
    }
    for(int i=anst;i>0;i--) printf("%d\n",ans[i]);
    return 0;
}
