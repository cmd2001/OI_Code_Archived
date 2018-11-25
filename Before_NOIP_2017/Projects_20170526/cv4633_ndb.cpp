//Cv4366_By_Cmd2001
#include<bits/stdc++.h>
#define lli long long int
#define mid ((ll+rr)>>1)
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
int s[2*maxn],t[2*maxn],nxt[2*maxn],n,m;
int fa[maxn],top[maxn],son[maxn],siz[maxn],dep[maxn],num[maxn],seg[maxn];
bool vis[maxn];
int lson[8*maxn],rson[8*maxn],l[8*maxn],r[8*maxn],cnt;
lli dat[8*maxn],add[8*maxn];

inline void addedge(int from,int to)
{
    static int cnt=0;
    t[++cnt]=to;
    nxt[cnt]=s[from];
    s[from]=cnt;
}

inline void dfs1(int pos)
{
    siz[pos]=1;
    int at=s[pos];
    while(at)
    {
        if(vis[t[at]])
        {
            at=nxt[at];
            continue;
        }
        vis[t[at]]=1;
        fa[t[at]]=pos;
        dep[t[at]]=dep[pos]+1;
        dfs1(t[at]);
        siz[pos]+=siz[t[at]];
        if(siz[t[at]]>siz[son[pos]]) son[pos]=t[at];
        at=nxt[at];
    }
}
inline void dfs2(int pos)
{
    if(pos==son[fa[pos]])
    {
        top[pos]=top[fa[pos]];
        num[pos]=num[fa[pos]]+1;
    }
    else
    {
        top[pos]=pos;
        num[pos]=1;
    }
    int at=s[pos];
    while(at)
    {
        if(vis[t[at]])
        {
            at=nxt[at];
            continue;
        }
        vis[t[at]]=1;
        dfs2(t[at]);
        at=nxt[at];
    }
}

inline void build(int pos,int ll,int rr)
{
    l[pos]=ll,r[pos]=rr;
    if(ll==rr) return;
    build(lson[pos]=++cnt,ll,mid);
    build(rson[pos]=++cnt,mid+1,rr);
}

inline void dfs3(int pos)
{
    bool isend=1;
    int at=s[pos];
    while(at)
    {
        isend&=vis[t[at]];
        if(!vis[t[at]])
        {
            vis[t[at]]=1;
            dfs3(t[at]);
        }
        at=nxt[at];
    }
    if(isend)
    {
        seg[top[pos]]=++cnt;
        build(cnt,num[top[pos]],num[pos]);
    }
}

inline void push(int pos)
{
    if(add[pos])
    {
        if(lson[pos]) add[lson[pos]]+=add[pos],dat[lson[pos]]+=(r[lson[pos]]-l[lson[pos]]+1)*add[pos];
        if(rson[pos]) add[rson[pos]]+=add[pos],dat[rson[pos]]+=(r[rson[pos]]-l[rson[pos]]+1)*add[pos];
        add[pos]=0;
    }
}
inline void update(int pos,int ll,int rr)
{
    if(rr<l[pos]||r[pos]<ll) return;
    if(ll<=l[pos]&&r[pos]<=rr)
    {
        add[pos]++;
        dat[pos]+=(r[pos]-l[pos]+1);
        return;
    }
    push(pos);
    update(lson[pos],ll,rr);
    update(rson[pos],ll,rr);
    dat[pos]=dat[lson[pos]]+dat[rson[pos]];
}
inline lli query(int pos,int ll,int rr)
{
    if(rr<l[pos]||r[pos]<ll) return 0;
    if(ll<=l[pos]&&r[pos]<=rr) return dat[pos];
    push(pos);
    return query(lson[pos],ll,rr)+query(rson[pos],ll,rr);
}
inline void change(int a,int b)
{
    while(top[a]!=top[b])
    {
        if(dep[top[a]]>dep[top[b]])
        {
            update(seg[top[a]],num[top[a]],num[a]);
            a=fa[top[a]];
        }
        else
        {
            update(seg[top[b]],num[top[b]],num[b]);
            b=fa[top[b]];
        }
    }
    update(seg[top[a]],min(num[a],num[b]),max(num[a],num[b]));
}
inline lli getans(int a,int b)
{
    lli ret=0;
    while(top[a]!=top[b])
    {
        if(dep[top[a]]>dep[top[b]])
        {
            ret+=query(seg[top[a]],num[top[a]],num[a]);
            a=fa[top[a]];
        }
        else
        {
            ret+=query(seg[top[b]],num[top[b]],num[b]);
            b=fa[top[b]];
        }
    }
    ret+=query(seg[top[a]],min(num[a],num[b]),max(num[a],num[b]));
    return ret;
}
inline void init()
{
    vis[1]=1;
    dfs1(1);
    memset(vis,0,sizeof(vis));
    vis[1]=1;
    dfs2(1);
    memset(vis,0,sizeof(vis));
    vis[1]=1;
    dfs3(1);
}
int main()
{
    scanf("%d",&n);
    for(int i=1,x,y;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        addedge(x,y);
        addedge(y,x);
    }
    init();
    scanf("%d",&m);
    for(int i=1,c,a,b;i<=m;i++)
    {
        scanf("%d%d%d",&c,&a,&b);
        if(c==1) change(a,b);
        else if(c==2) printf("%lld\n",getans(a,b));
    }
    return 0;
}
