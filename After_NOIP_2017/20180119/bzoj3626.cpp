#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define debug cout
#define lli long long int
using namespace std;
const int maxn=5e4+1e2;
const int mod = 201314;

struct QNode {
    int pos,id,lam;
    QNode() {}
    QNode(int pp,int ii,int ll) {
        pos = pp , id = ii , lam = ll;
    }
};
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],dep[maxn],siz[maxn],son[maxn],top[maxn],cov[maxn],num[maxn];
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],sum[maxn<<3],lazy[maxn<<3],cnt;
int ans[maxn];
vector<QNode> qs[maxn];
int n,m,root;

inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) return;
    const int mid = ( ll + rr ) >> 1;
    build(lson[pos]=++cnt,ll,mid);
    build(rson[pos]=++cnt,mid+1,rr);
}
inline void add(int pos,int x) {
    lazy[pos] += x , sum[pos] += ( (lli) r[pos] - l[pos] + 1 ) * x % mod;
    lazy[pos] %= mod , sum[pos] %= mod;
}
inline void push(int pos) {
    if( lazy[pos] ) {
        if( lson[pos] ) add(lson[pos],lazy[pos]);
        if( rson[pos] ) add(rson[pos],lazy[pos]);
        lazy[pos] = 0;
    }
}
inline void update(int pos,int ll,int rr,int x) {
    if( rr < l[pos] || r[pos] < ll ) return;
    if( ll <= l[pos] && r[pos] <= rr ) {
        add(pos,x);
        return;
    }
    push(pos);
    update(lson[pos],ll,rr,x);
    update(rson[pos],ll,rr,x);
    sum[pos] = ( sum[lson[pos]] + sum[rson[pos]] ) % mod;
}
inline int query(int pos,int ll,int rr) {
    if( rr < l[pos] || r[pos] < ll ) return 0;
    if( ll <= l[pos] && r[pos] <= rr ) return sum[pos] % mod;
    push(pos);
    return ( query(lson[pos],ll,rr) + query(rson[pos],ll,rr) ) % mod;
}

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] ) {
            fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1;
            pre(t[at]);
            siz[pos] += siz[t[at]];
            son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
        }
}
inline void dfs(int pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    num[pos] = pos == son[fa[pos]] ? num[fa[pos]] + 1 : 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] )
            dfs(t[at]);
    if( !son[pos] )
        build(cov[top[pos]]=++cnt,num[top[pos]],num[pos]);
}
inline void chainupdate(int x) {
    while( x ) {
        update(cov[top[x]],num[top[x]],num[x],1);
        x = fa[top[x]];
    }
}
inline int chainsum(int x) {
    int ret = 0;
    while( x ) {
        ret += query(cov[top[x]],num[top[x]],num[x]) , ret %= mod;
        x = fa[top[x]];
    }
    return ret;
}

inline void solve() {
    for(int i=1;i<=n;i++) {
        chainupdate(i);
        for(unsigned j=0;j<qs[i].size();j++) {
            ans[qs[i][j].id] = ( ans[qs[i][j].id] + qs[i][j].lam * chainsum(qs[i][j].pos) % mod ) % mod;
        }
    }
}

inline void addquery(int pos,int a,int b,int id) { // a should -- before being argument
    if( a ) qs[a].push_back(QNode(pos,id,-1));
    qs[b].push_back(QNode(pos,id,1));
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=2,a;i<=n;i++) {
        scanf("%d",&a) , ++a;
        addedge(a,i) , addedge(i,a);
    }
    for(int i=1,a,b,p;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&p);
        ++a,++b,++p;
        addquery(p,a-1,b,i);
    }
    
    
    pre(1) , dfs(1);
    solve();
    
    for(int i=1;i<=m;i++)
        printf("%d\n",(ans[i]+mod)%mod);
    
    return 0;
}