#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int maxn=5e5+1e2;
const int inf=0x3f3f3f3f;

int cmp;
struct Point {
    int d[2],id;
    friend bool operator < (const Point &a,const Point &b) {
        return a.d[cmp] < b.d[cmp];
    }
}ps[maxn],nv[maxn];
int mi[maxn][2],mx[maxn][2],lson[maxn],rson[maxn],cnt;
int ansmi,ansmx,ans;

inline void fill(int pos,const Point &p) {
    nv[pos] = p;
    for(int i=0;i<2;i++) mi[pos][i] = mx[pos][i] = p.d[i];
}
inline void update(int pos,int son) {
    for(int i=0;i<2;i++) {
        mi[pos][i] = min( mi[pos][i] , mi[son][i] ) ,
        mx[pos][i] = max( mx[pos][i] , mx[son][i] ) ;
    }
}
inline void build(int pos,int dir,int ll,int rr) {
    const int mid = ( ll + rr ) >> 1;
    cmp = dir , nth_element(ps+ll,ps+mid,ps+rr+1);
    fill(pos,ps[mid]);
    if( ll < mid ) build(lson[pos]=++cnt,dir^1,ll,mid-1) , update(pos,lson[pos]);
    if( mid < rr ) build(rson[pos]=++cnt,dir^1,mid+1,rr) , update(pos,rson[pos]);
}

inline int hmin(int pos,const Point &p) {
    int ret = 0;
    for(int i=0;i<2;i++) {
        if( p.d[i] < mi[pos][i] ) ret += mi[pos][i] - p.d[i];
        else if( p.d[i] > mx[pos][i] ) ret += p.d[i] - mx[pos][i];
    }
    return ret;
}
inline int hmax(int pos,const Point &p) {
    return max(abs(mi[pos][0]-p.d[0]),abs(mx[pos][0]-p.d[0])) + max(abs(mi[pos][1]-p.d[1]),abs(mx[pos][1]-p.d[1]));
}
inline int dis(const Point &a,const Point &b,const int &tpe) {
    if( a.id == b.id ) return tpe * inf;
    return abs(a.d[0]-b.d[0]) + abs(a.d[1]-b.d[1]);
}
inline void querymx(int pos,const Point &p) {
    ansmx = max( ansmx , dis(nv[pos],p,-1) );
    if( lson[pos] && hmax(lson[pos],p) > ansmx ) querymx(lson[pos],p);
    if( rson[pos] && hmax(rson[pos],p) > ansmx ) querymx(rson[pos],p);
}
inline void querymi(int pos,const Point &p) {
    ansmi = min( ansmi , dis(nv[pos],p,1) );
    if( lson[pos] && hmin(lson[pos],p) < ansmi ) querymi(lson[pos],p);
    if( rson[pos] && hmin(rson[pos],p) < ansmi ) querymi(rson[pos],p);
}

int main() {
    static int n;
    scanf("%d",&n) , ans = inf;
    for(int i=1;i<=n;i++) scanf("%d%d",ps[i].d,ps[i].d+1) , ps[i].id = i;
    build(cnt=1,0,1,n);
    for(int i=1;i<=n;i++) {
        ansmx = -inf , ansmi = inf;
        querymx(1,ps[i]) , querymi(1,ps[i]);
        ans = min( ans , ansmx - ansmi );
    }
    printf("%d\n",ans);
    return 0;
}

