#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e6+1e2;

int srt[maxn<<1];
int a[maxn],b[maxn],ope[maxn],fa[maxn],n,len,Fail;

inline void fillfa(int l)
{
    for(int i=1;i<=l;i++) fa[i]=i;
}
inline void conv()
{
    for(int i=1;i<=n;i++) a[i]=lower_bound(srt+1,srt+1+len,a[i])-srt;
    for(int i=1;i<=n;i++) b[i]=lower_bound(srt+1,srt+1+len,b[i])-srt;
}
inline int findfa(int x)
{
    return fa[x]==x?x:fa[x]=findfa(fa[x]);
}
inline void init()
{
    memset(srt,0,sizeof(srt));memset(ope,0,sizeof(ope));
    memset(a,0,sizeof(a));memset(b,0,sizeof(b));
    n=Fail=len=0;
}

int main()
{
    static int t;
    scanf("%d",&t);
    while(t--)
    {
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d",a+i,b+i,ope+i);
            srt[++len]=a[i];
            srt[++len]=b[i];
        }

        sort(srt+1,srt+1+len);
        len=unique(srt+1,srt+1+len)-srt-1;

        fillfa(len);
        conv();

        for(int i=1;i<=n;i++)
            if(ope[i]==1&&findfa(a[i])!=findfa(b[i])) fa[findfa(a[i])]=findfa(b[i]);
        for(int i=1;i<=n&&!Fail;i++)
            if(ope[i]==0&&findfa(a[i])==findfa(b[i])) Fail=1;

        if(Fail) puts("NO");
        else puts("YES");

    }

    return 0;
}

