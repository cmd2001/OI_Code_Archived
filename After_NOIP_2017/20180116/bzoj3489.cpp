#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=2e5+1e2;

int cmp,ans;
struct Point {
    int d[3],val;
    Point() {}
    Point(int d0,int d1,int d2,int vv) {
        d[0] = d0 , d[1] = d1 , d[2] = d2 , val = vv;
    }
    friend bool operator < (const Point &a,const Point &b) {
        return a.d[cmp] < b.d[cmp];
    }
}ps[maxn],dv[maxn];

int lson[maxn],rson[maxn],mi[maxn][3],mx[maxn][3],mxv[maxn],cnt;
int in[maxn],prv[maxn],nxt[maxn],lst[maxn];

inline void fill(int pos,const Point &p) {
    dv[pos] = p;
    for(int i=0;i<3;i++)
        mi[pos][i] = mx[pos][i] = p.d[i];
    mxv[pos] = p.val;
}
inline void cupd(int fa,int son) {
    for(int i=0;i<3;i++)
        mx[fa][i] = max( mx[fa][i] , mx[son][i] ),
        mi[fa][i] = min( mi[fa][i] , mi[son][i] ),
        mxv[fa] = max( mxv[fa] , mxv[son] );
}
inline void update(int pos) {
    if( lson[pos] ) cupd(pos,lson[pos]);
    if( rson[pos] ) cupd(pos,rson[pos]);
}
inline void build(int pos,int ll,int rr,int dir) {
    cmp = dir;
    const int mid = ( ll + rr ) >> 1;
    nth_element(ps+ll,ps+mid,ps+rr+1);
    fill(pos,ps[mid]);
    if( ll < mid ) build(lson[pos]=++cnt,ll,mid-1,(dir+1)%3);
    if( rr > mid ) build(rson[pos]=++cnt,mid+1,rr,(dir+1)%3);
    update(pos);
}
inline bool inside(int pos,int ll,int rr) {
    return ll <= mi[pos][0] && mx[pos][0] <= rr && mx[pos][1] < ll && rr < mi[pos][2];
}
inline bool inside(const Point &p,int ll,int rr) {
    return ll <= p.d[0] && p.d[0] <= rr && p.d[1] < ll && rr < p.d[2];
}
inline bool outside(int pos,int ll,int rr) {
    return mx[pos][0] < ll || rr < mi[pos][0] || ll <= mi[pos][1] || mx[pos][2] <= rr;
}
inline void query(int pos,int ll,int rr) {
    if( inside(pos,ll,rr) ) {
        ans = max( ans , mxv[pos] );
        return;
    }
    if( inside(dv[pos],ll,rr) ) ans = max( ans , dv[pos].val );
    int pl=-1,pr=-1;
    if( lson[pos] && !outside(lson[pos],ll,rr) ) pl = mxv[lson[pos]];
    if( rson[pos] && !outside(rson[pos],ll,rr) ) pr = mxv[rson[pos]];
    if( pl > pr ) {
        if( pl > ans ) query(lson[pos],ll,rr);
        if( pr > ans ) query(rson[pos],ll,rr);
    } else {
        if( pr > ans ) query(rson[pos],ll,rr);
        if( pl > ans ) query(lson[pos],ll,rr);
    }
}

int n,m;

inline void gen() {
    for(int i=1;i<=n;i++) prv[i] = lst[in[i]] , lst[in[i]] = i;
    for(int i=1;i<=n;i++) lst[i] = n + 1;
    for(int i=n;i;i--) nxt[i] = lst[in[i]] , lst[in[i]] = i;
    for(int i=1;i<=n;i++) ps[i] = Point(i,prv[i],nxt[i],in[i]);
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    
    gen();
    build(cnt=1,1,n,0);
    
    for(int i=1,ll,rr;i<=m;i++) {
        scanf("%d%d",&ll,&rr);
        ll = ( ans + ll ) % n + 1 , rr = ( ans + rr ) % n + 1;
        if( ll > rr ) swap( ll , rr );
        ans = 0;
        query(1,ll,rr);
        printf("%d\n",ans);
    }
    
    return 0;
}