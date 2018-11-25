#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<functional>
#include<queue>
#include<vector>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;
// Compilation technology is well developed, we don't need to support it .

int cmp;
struct Point {
    lli d[2];
    friend bool operator < (const Point &a,const Point &b) {
        return a.d[cmp] < b.d[cmp];
    }
}ps[maxn],nv[maxn],tar;
lli mi[maxn][2],mx[maxn][2];
int lson[maxn],rson[maxn],cnt;
priority_queue<lli,vector<lli>,greater<lli> > pq;
unsigned k;

inline lli sq(const lli &x) {
    return x * x;
}
inline lli dis(const Point &a,const Point &b) {
    return sq(a.d[0]-b.d[0]) + sq(a.d[1]-b.d[1]);
}
inline lli dis(const Point &p,const lli &x,const lli &y) {
    return sq(p.d[0]-x) + sq(p.d[1]-y);
}
inline lli dis(const Point &p,int pos) {
    lli ret = 0;
    ret = max( ret , dis(p,mi[pos][0],mi[pos][1]) ) ,
    ret = max( ret , dis(p,mi[pos][0],mx[pos][1]) ) ,
    ret = max( ret , dis(p,mx[pos][0],mi[pos][1]) ) ,
    ret = max( ret , dis(p,mx[pos][0],mx[pos][1]) ) ;
    return ret;
}
inline void fill(int pos,const Point &p) {
    nv[pos] = p;
    for(int i=0;i<2;i++) mx[pos][i] = mi[pos][i] = p.d[i];
}
inline void update(int pos,int son) {
    for(int i=0;i<2;i++) {
        mx[pos][i] = max( mx[pos][i] , mx[son][i] ) ,
        mi[pos][i] = min( mi[pos][i] , mi[son][i] ) ;
    }
}
inline void build(int pos,int dir,int ll,int rr) {
    const int mid = ( ll + rr ) >> 1;
    cmp = dir , nth_element(ps+ll,ps+mid,ps+rr+1);
    fill(pos,ps[mid]);
    if( ll != mid ) build(lson[pos]=++cnt,dir^1,ll,mid-1) , update(pos,lson[pos]);
    if( rr != mid ) build(rson[pos]=++cnt,dir^1,mid+1,rr) , update(pos,rson[pos]);
}

inline void query(int pos,const Point &p) {
    const lli dnow = dis(p,nv[pos]);
    if( pq.size() < k || dnow >= pq.top() ) {
        if( pq.size() == k ) pq.pop();
        pq.push(dnow);
    }
    if( lson[pos] ) {
        const lli disl = dis(p,lson[pos]);
        if( pq.size() < k || disl >= pq.top() ) query(lson[pos],p);
    }
    if( rson[pos] ) {
        const lli disr = dis(p,rson[pos]);
        if( pq.size() < k || disr >= pq.top() ) query(rson[pos],p);
    }
}

int main() {
    static int n;
    scanf("%d%u",&n,&k) , k <<= 1;
    for(int i=1;i<=n;i++) scanf("%lld%lld",ps[i].d,ps[i].d+1);
    build(cnt=1,0,1,n);
    for(int i=1;i<=n;i++) query(1,ps[i]);
    printf("%lld\n",pq.top());
    return 0;
}

