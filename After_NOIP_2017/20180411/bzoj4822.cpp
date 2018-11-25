#include<cstdio>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

int cmp;
struct Point {
    int d[2],val;
    friend bool operator < (const Point &a,const Point &b) {
        return a.d[cmp] < b.d[cmp];
    }
}ps[maxn],nv[maxn];
struct QNode {
    int mi[2],mx[2];
}q;
int lson[maxn],rson[maxn],mi[maxn][2],mx[maxn][2],cnt;
lli su[maxn],ans; // remember to reset ans before query !

inline void fill(const int &pos,const Point &p) {
    nv[pos] = p , su[pos] = p.val;
    for(register int i=0;i<2;i++) mx[pos][i] = mi[pos][i] = p.d[i];
}
inline void up(const int &pos,const int &son) {
    su[pos] += su[son];
    for(register int i=0;i<2;i++)
        mi[pos][i] = min( mi[pos][i] , mi[son][i] ) ,
        mx[pos][i] = max( mx[pos][i] , mx[son][i] ) ;
}
inline void build(int pos,const int &dir,const int &ll,const int &rr) {
    const int mid = ( ll + rr ) >> 1;
    cmp = dir , nth_element(ps+ll,ps+mid,ps+rr+1);
    fill(pos,ps[mid]);
    if( ll < mid ) build(lson[pos]=++cnt,dir^1,ll,mid-1) , up(pos,lson[pos]);
    if( mid < rr ) build(rson[pos]=++cnt,dir^1,mid+1,rr) , up(pos,rson[pos]);
}
inline bool fullout(const int &pos) {
    for(register int i=0;i<2;i++) if( q.mx[i] < mi[pos][i] || mx[pos][i] < q.mi[i] ) return 1;
    return 0;
}
inline bool fullin(const int &pos) {
    for(register int i=0;i<2;i++) if( ! ( q.mi[i] <= mi[pos][i] && mx[pos][i] <= q.mx[i] ) ) return 0;
    return 1;
}
inline bool pointin(const Point &p) {
    for(register int i=0;i<2;i++) if( ! ( q.mi[i] <= p.d[i] && p.d[i] <= q.mx[i] ) ) return 0;
    return 1;
}
inline void query(const int &pos) {
    if( fullout(pos) ) return;
    if( fullin(pos) ) return void(ans+=su[pos]);
    if( pointin(nv[pos]) ) ans += nv[pos].val;
    query(lson[pos]) , query(rson[pos]);
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=n;i++) scanf("%d%d%d",ps[i].d,ps[i].d+1,&ps[i].val);
    build(cnt=1,0,1,n);
    for(register int i=1;i<=m;i++) {
        for(register int i=0;i<2;i++) scanf("%d",q.mi+i);
        for(register int i=0;i<2;i++) scanf("%d",q.mx+i);
        ans = 0 , query(1);
        printf("%lld\n",ans);
    }
    return 0;
}
