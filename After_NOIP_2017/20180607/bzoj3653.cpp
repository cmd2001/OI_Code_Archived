#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=3e5+1e2,maxe=2e7+1e2;

int roots[maxn];

struct PersistentSegmentTree {
    int lson[maxe],rson[maxe],cnt;
    lli sum[maxe];
    inline void insert(int &pos,int pre,int l,int r,const int &tar,const int &x) {
        sum[pos=++cnt] = sum[pre] + x;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],lson[pre],l,mid,tar,x) , rson[pos] = rson[pre];
        else insert(rson[pos],rson[pre],mid+1,r,tar,x) , lson[pos] = lson[pre];
    }
    inline lli query(int pos,int pre,int l,int r,const int &ll,const int &rr) {
        if( sum[pos] == sum[pre] || rr < l || r < ll ) return 0;
        if( ll <= l && r <= rr ) return sum[pos] - sum[pre];
        const int mid = ( l + r ) >> 1;
        return query(lson[pos],lson[pre],l,mid,ll,rr) + query(rson[pos],rson[pre],mid+1,r,ll,rr);
    }
}pst;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int dfn[maxn],rit[maxn],siz[maxn],dep[maxn],dd;
int n;

inline void coredge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}
inline void pre(int pos,int fa) {
    siz[pos] = 1 , dep[pos] = dep[fa] + 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) pre(t[at],pos) , siz[pos] += siz[t[at]];
}
inline void dfs(int pos,int fa) {
    dfn[pos] = ++dd , pst.insert(roots[dd],roots[dd-1],1,n,dep[pos],siz[pos]-1);
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) dfs(t[at],pos);
    rit[pos] = dd;
}

inline lli query(int pos,int k) {
    lli ret = pst.query(roots[rit[pos]],roots[dfn[pos]],1,n,dep[pos],dep[pos]+k);
    ret += (lli) min(k,dep[pos]-1) * ( siz[pos] - 1 );
    return ret;
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int m;
    n = getint() , m = getint();
    for(int i=1;i<n;i++) addedge(getint(),getint());
    pre(1,0) , dfs(1,-1);
    for(int i=1,p,k;i<=m;i++) p = getint() , k = getint() , printf("%lld\n",query(p,k));
    return 0;
}
