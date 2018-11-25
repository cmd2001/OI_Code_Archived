#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=6e3+1e2;

int fa[maxn],siz[maxn],n;
long long int ans;

inline int findfa(int x)
{
    return fa[x]==x?x:fa[x]=findfa(fa[x]);
}
inline void mrege(int x,int y)
{
    x=findfa(x),y=findfa(y);
    fa[x]=y,siz[y]+=siz[x];
}
inline void fillfa(int len)
{
    for(int i=1;i<=len;i++) fa[i]=i,siz[i]=1;
}
struct node
{
    int a,b,len;
    friend bool operator < (const node &a,const node &b)
    {
        return a.len<b.len;
    }
}ns[maxn];


int main()
{
    static int t;
    scanf("%d",&t);

    while(t--)
    {
        ans=0;
        scanf("%d",&n);

        fillfa(n);
        for(int i=1;i<n;i++) scanf("%d%d%d",&ns[i].a,&ns[i].b,&ns[i].len);

        sort(ns+1,ns+n);

        for(int i=1;i<n;i++)
        {
            const int &a=ns[i].a,&b=ns[i].b,&l=ns[i].len;
            if(findfa(a)!=findfa(b))
            {
                ans+=(siz[findfa(a)]*siz[findfa(b)]-1)*(l+1);
                mrege(a,b);
            }
        }

        printf("%lld\n",ans);
    }
    return 0;
}



