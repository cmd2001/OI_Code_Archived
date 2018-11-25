#include<cstdio>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=1.5e5+1e2,maxe=2e7+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
int dep[maxn],siz[maxn],fa[maxn],son[maxn],sat[maxn],top[maxn],dfn[maxn];
int lson[maxe],rson[maxe],cnt;
lli sum[maxe],mrk[maxe],val[maxn];
int nums[maxn],roots[maxn],len;
lli sumdep[maxn],sumsiz[maxn],ans;
int n,A;

struct Node {
    int num,pos;
    friend bool operator < (const Node &a,const Node &b) {
        return a.num < b.num;
    }
}ns[maxn];

inline void build(int pos,int l,int r) {
    if( l == r ) return;
    const int mid = ( l + r ) >> 1;
    build(lson[pos]=++cnt,l,mid) , build(rson[pos]=++cnt,mid+1,r);
}
inline void insert(int pos,int pre,int l,int r,int ll,int rr) {
    lson[pos] = lson[pre] , rson[pos] = rson[pre] , sum[pos] = sum[pre] , mrk[pos] = mrk[pre];
    if( ll <= l && r <= rr ) {
        mrk[pos] = mrk[pre] + 1 ;
        return;
    } const int mid = ( l + r ) >> 1;
    sum[pos] += val[min(r,rr)] - val[max(l,ll)-1];
    if( rr <= mid ) insert(lson[pos]=++cnt,lson[pre],l,mid,ll,rr);
    else if( ll > mid ) insert(rson[pos]=++cnt,rson[pre],mid+1,r,ll,rr);
    else {
        insert(lson[pos]=++cnt,lson[pre],l,mid,ll,rr) ,
        insert(rson[pos]=++cnt,rson[pre],mid+1,r,ll,rr);
    }
}
inline lli query(int pos,int l,int r,int ll,int rr) {
    lli add = mrk[pos] * ( val[min(r,rr)] - val[max(l,ll)-1] );
    if( ll <= l && r <= rr ) return sum[pos] + add;
    const int mid = ( l + r ) >> 1;
    if( rr <= mid ) return query(lson[pos],l,mid,ll,rr) + add;
    else if( ll > mid ) return query(rson[pos],mid+1,r,ll,rr) + add;
    return query(lson[pos],l,mid,ll,rr) + query(rson[pos],mid+1,r,ll,rr) + add;
}
inline lli chain(int x,int rta,int rtm) {
    lli ret = 0;
    while( x ) {
        ret += query(rta,1,n,dfn[top[x]],dfn[x]) - query(rtm,1,n,dfn[top[x]],dfn[x]);
        x = fa[top[x]];
    }
    return ret;
}

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] ) {
            fa[t[at]] = pos , dep[t[at]] = dep[pos] + l[at];
            pre(t[at]) , siz[pos] += siz[t[at]];
            if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at] , sat[pos] = at;
        }
}
inline void dfs(int pos,int frl) {
    static int dd;
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    dfn[pos] = ++dd , val[dd] = frl;
    if( son[pos] ) dfs(son[pos],l[sat[pos]]);
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] && t[at] != son[pos] )
            dfs(t[at],l[at]);
}

inline void chain(int &r,int p) {
    int t = r;
    while( p ) {
        insert(r=++cnt,t,1,n,dfn[top[p]],dfn[p]) , t = r;
        p = fa[top[p]];
    }
}
inline void init() {
    pre(1) , dfs(1,0);
    sort(ns+1,ns+1+n);
    build(roots[0]=++cnt,1,n);
    for(int i=1;i<=n;i++) val[i] += val[i-1];
    for(int l=1,r;l<=n;l=r+1) {
        for(r=l;r<n&&ns[r+1].num==ns[l].num;r++) ;
        nums[++len] = ns[l].num , roots[len] = roots[len-1];
        sumsiz[len] = sumsiz[len-1] + ( r - l + 1 ) , sumdep[len] = sumdep[len-1];
        for(int k=l;k<=r;k++) {
            chain(roots[len],ns[k].pos) ,
            sumdep[len] += dep[ns[k].pos];
        }
    }
}
inline lli calc(int l,int r,int p) {
    l = lower_bound(nums+1,nums+1+len,l) - nums - 1,
    r = upper_bound(nums+1,nums+1+len,r) - nums - 1;
    lli ret = ( sumdep[r] - sumdep[l] ) + ( sumsiz[r] - sumsiz[l] ) * dep[p];
    ret -= ( chain(p,roots[r],roots[l]) << 1 );
    return ret;
}

int main() {
    static int q;
    scanf("%d%d%d",&n,&q,&A);
    for(int i=1;i<=n;i++) scanf("%d",&ns[i].num) , ns[i].pos = i;
    for(int i=1,a,b,l;i<n;i++) {
        scanf("%d%d%d",&a,&b,&l) ,
        addedge(a,b,l) , addedge(b,a,l);
    }
    init();
    for(int i=1,l,r,p;i<=q;i++) {
        scanf("%d%d%d",&p,&l,&r);
        l = ( l + ans ) % A , r = ( r + ans ) % A;
        if( l > r ) swap(l,r);
        ans = calc(l,r,p);
        printf("%lld\n",ans);
    }
    return 0;
}

