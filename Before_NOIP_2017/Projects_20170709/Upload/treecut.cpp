#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e4+1e2,maxe=maxn<<1;

int s[maxn],t[maxe],nxt[maxe],n;
int siz[maxn],dat[maxn];
bool vis[maxn];

inline void addedge(int from,int to)
{
    static int cnt=0;
    t[++cnt]=to;
    nxt[cnt]=s[from];
    s[from]=cnt;
}
inline void doubledge(int x,int y)
{
    addedge(x,y);
    addedge(y,x);
}

inline void pre(int pos)
{
    int at=s[pos];
    siz[pos]=1;

    while(at)
    {
        if(!vis[t[at]])
        {
            vis[t[at]]=1;
            pre(t[at]);
            siz[pos]+=siz[t[at]];
        }
        at=nxt[at];
    }
}
inline void dfs(int pos)
{
    int at=s[pos];
    dat[pos]=n-siz[pos];

    while(at)
    {
        if(!vis[t[at]])
        {
            vis[t[at]]=1;
            dfs(t[at]);
            dat[pos]=max(dat[pos],siz[t[at]]);
        }
        at=nxt[at];
    }
}
inline void output()
{
    const int tar=n>>1;
    bool able=0;
    for(int i=1;i<=n;i++)
    {
        if(dat[i]<=tar)
        {
            printf("%d\n",i);
            able=1;
        }
    }
    if(!able) puts("NONE");
}

int main()
{
    freopen("treecut.in","r",stdin);
    freopen("treecut.out","w",stdout);

    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        doubledge(a,b);
    }

    //debug<<"edge added"<<endl;
    vis[1]=1;
    pre(1);
    memset(vis,0,sizeof(vis));
    vis[1]=1;
    dfs(1);

    output();

    fclose(stdin);
    fclose(stdout);

    return 0;
}

