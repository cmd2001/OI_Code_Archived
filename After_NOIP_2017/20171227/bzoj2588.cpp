#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxm=1e7+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],son[maxn],treesiz[maxn],top[maxn],dep[maxn],root[maxn];
int in[maxn],srt[maxn];
int lson[maxm],rson[maxm],siz[maxm];
int n,m,cnt,len,ans;

inline void prebuild(int pos,int ll,int rr) {
    if( ll == rr )
        return;
    const int mid = ( ll + rr ) >> 1;
    prebuild(lson[pos]=++cnt,ll,mid);
    prebuild(rson[pos]=++cnt,mid+1,rr);
}
inline void insert(int pos,int prepos,int ll,int rr,int tar) {
    if( ll == rr && ll == tar ) {
        siz[pos] = siz[prepos] + 1;
        return;
    }
    const int mid = ( ll + rr ) >> 1;
    lson[pos] = lson[prepos] , rson[pos] = rson[prepos];
    if( tar <= mid )
        insert(lson[pos]=++cnt,lson[prepos],ll,mid,tar);
    else if( tar > mid )
        insert(rson[pos]=++cnt,rson[prepos],mid+1,rr,tar);
    siz[pos] = siz[lson[pos]] + siz[rson[pos]];
}
inline int sum(int ap1,int ap2,int mp1,int mp2) {
    return siz[lson[ap1]] + siz[lson[ap2]] - siz[lson[mp1]] - siz[lson[mp2]];
}
inline int sss(int ap1,int ap2,int mp1,int mp2) {
    return siz[ap1] + siz[ap2] - siz[mp1] - siz[mp2];
}
inline int query(int ap1,int ap2,int mp1,int mp2,int ll,int rr,int siz) {
    if( ll == rr )
        return ll;
    const int mid = ( ll + rr ) >> 1 , ss = sum(ap1,ap2,mp1,mp2);
    if( siz <= ss )
        return query(lson[ap1],lson[ap2],lson[mp1],lson[mp2],ll,mid,siz);
    else
        return query(rson[ap1],rson[ap2],rson[mp1],rson[mp2],mid+1,rr,siz-ss);
}

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to,
    nxt[cnt] = s[from],
    s[from] = cnt;
}
inline void pre(int pos) {
    treesiz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] ) {
            fa[t[at]] = pos;
            dep[t[at]] = dep[pos] + 1;
            pre(t[at]);
            treesiz[pos] += treesiz[t[at]];
            if( treesiz[t[at]] > treesiz[son[pos]] )
                son[pos] = t[at];
        }
}
inline void dfs(int pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] )
            dfs(t[at]);
}
inline int lca(int xx,int yy) {
    while( top[xx] != top[yy] )
        if( dep[top[xx]] > dep[top[yy]] )
            xx = fa[top[xx]];
        else
            yy = fa[top[yy]];
    return dep[xx] < dep[yy] ? xx : yy;
}
inline void gen(int pos) {
    insert(root[pos]=++cnt,root[fa[pos]],1,len,in[pos]);
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] )
            gen(t[at]);
}
inline void init() {
    for(int i=1;i<=n;i++)
        srt[++len] = in[i];
    sort(srt+1,srt+1+len);
    len = unique(srt+1,srt+1+len) - srt - 1;
    for(int i=1;i<=n;i++)
        in[i] = lower_bound(srt+1,srt+1+len,in[i]) - srt;
    pre(1);
    dfs(1);
    prebuild(root[0]=cnt=1,1,len);
    gen(1);
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    for(int i=1,a,b;i<n;i++) {
        scanf("%d%d",&a,&b);
        addedge(a,b);
        addedge(b,a);
    }
    init();
    for(int i=1,a,b,k,l,f;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&k);
        a ^= ans;
        l = lca( a , b ) , f = fa[l];
        ans = query(root[a],root[b],root[l],root[f],1,len,k);
        ans = srt[ans];
        printf("%d",ans);
        if( i != m )
            putchar('\n');
    }
    return 0;
}
