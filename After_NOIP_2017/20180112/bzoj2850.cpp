#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

int cmp;
struct Point {
    lli d[2],h;
    friend bool operator < (const Point &a,const Point &b) {
        return a.d[cmp] < b.d[cmp];
    }
    inline lli f(int a,int b) const {
        return a * d[0] + b * d[1];
    }
}ps[maxn],dv[maxn];

int lson[maxn],rson[maxn],cnt;
lli mx[maxn][2],mi[maxn][2],sum[maxn];
lli c;

inline lli f(lli x,lli y,int a,int b) {
    return a * x + b * y;
}

inline void update(int pos) {
    if( lson[pos] ) {
        for(int i=0;i<2;i++)
            mi[pos][i] = min( mi[pos][i] , mi[lson[pos]][i] ),
            mx[pos][i] = max( mx[pos][i] , mx[lson[pos]][i] );
        sum[pos] += sum[lson[pos]];
    }
    if( rson[pos] ) {
        for(int i=0;i<2;i++)
            mi[pos][i] = min( mi[pos][i] , mi[rson[pos]][i] ),
            mx[pos][i] = max( mx[pos][i] , mx[rson[pos]][i] );
        sum[pos] += sum[rson[pos]];
    }
}
inline void fill(int pos,const Point &p) {
    dv[pos] = p;
    for(int i=0;i<2;i++)
        mx[pos][i] = mi[pos][i] = p.d[i];
    sum[pos] = p.h;
}
inline void build(int pos,int ll,int rr,int dir) {
    cmp = dir;
    const int mid = ( ll + rr ) >> 1;
    nth_element(ps+ll,ps+mid,ps+rr+1);
    fill(pos,ps[mid]);
    if( ll < mid ) build(lson[pos]=++cnt,ll,mid-1,dir^1);
    if( rr > mid ) build(rson[pos]=++cnt,mid+1,rr,dir^1);
    update(pos);
}
inline int judge(int pos,int a,int b) {
    return ( f(mx[pos][0],mx[pos][1],a,b) < c ) + ( f(mx[pos][0],mi[pos][1],a,b) < c ) + 
           ( f(mi[pos][0],mx[pos][1],a,b) < c ) + ( f(mi[pos][0],mi[pos][1],a,b) < c ) ;
}
inline lli query(int pos,int a,int b) {
    lli ret = 0;
    if( dv[pos].f(a,b) < c )
        ret += dv[pos].h;
    if( lson[pos] ) {
        int jl = judge(lson[pos],a,b);
        if( jl == 4 ) ret += sum[lson[pos]];
        else if( jl ) ret += query(lson[pos],a,b);
    }
    if( rson[pos] ) {
        int jr = judge(rson[pos],a,b);
        if( jr == 4 ) ret += sum[rson[pos]];
        else if( jr ) ret += query(rson[pos],a,b);
    }
    return ret;
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lld%lld%lld",ps[i].d,ps[i].d+1,&ps[i].h);
    
    build(cnt=1,1,n,0);
    
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d%lld",&a,&b,&c);
        printf("%lld\n",query(1,a,b));
    }
    return 0;
}
