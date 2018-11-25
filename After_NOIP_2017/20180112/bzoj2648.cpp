#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int maxn=1.5e6+1e2;
const int inf=0x3f3f3f3f;

int cmp,ans;
struct Point {
    int d[2];
    friend bool operator < (const Point &a,const Point &b) {
        return a.d[cmp] < b.d[cmp];
    }
    int dis(const Point &o) const {
        int ret = 0;
        for(int i=0;i<2;i++)
            ret += abs( d[i] - o.d[i] );
        return ret;
    }
}ps[maxn];

int lson[maxn],rson[maxn],mi[maxn][2],mx[maxn][2];
Point dv[maxn];
int cnt;

inline void update(int pos) {
    if( lson[pos] ) {
        for(int i=0;i<2;i++)
            mi[pos][i] = min( mi[pos][i] , mi[lson[pos]][i] ),
            mx[pos][i] = max( mx[pos][i] , mx[lson[pos]][i] );
    }
    if( rson[pos] ) {
        for(int i=0;i<2;i++)
            mi[pos][i] = min( mi[pos][i] , mi[rson[pos]][i] ),
            mx[pos][i] = max( mx[pos][i] , mx[rson[pos]][i] );
    }
}
inline void fill(int pos,const Point &p) {
    dv[pos] = p;
    for(int i=0;i<2;i++)
        mx[pos][i] = mi[pos][i] = p.d[i];
}
inline void build(int pos,int pl,int pr,int dir) {
    const int pmid = ( pl + pr ) >> 1;
    cmp = dir;
    nth_element(ps+pl,ps+pmid,ps+pr+1);
    fill(pos,ps[pmid]);
    if( pl < pmid ) build(lson[pos]=++cnt,pl,pmid-1,dir^1);
    if( pr > pmid ) build(rson[pos]=++cnt,pmid+1,pr,dir^1);
    update(pos);
}
inline void insert(int pos,Point np,int dir) {
    cmp = dir;
    if( np < dv[pos] ) {
        if( lson[pos] ) insert(lson[pos],np,dir^1);
        else {
            lson[pos] = ++cnt;
            fill(lson[pos],np);
        }
    } else {
        if( rson[pos] ) insert(rson[pos],np,dir^1);
        else {
            rson[pos] = ++cnt;
            fill(rson[pos],np);
        }
    }
    update(pos);
}
inline int dis(int pos,const Point &p) {
    int ret = 0;
    for(int i=0;i<2;i++)
        ret += max( p.d[i] - mx[pos][i] , 0 ) + max( mi[pos][i] - p.d[i] , 0 );
    return ret;
}
inline void query(int pos,const Point &p) {
    ans = min( ans , p.dis(dv[pos]) );
    int dl = lson[pos] ? dis(lson[pos],p) : inf;
    int dr = rson[pos] ? dis(rson[pos],p) : inf;
    if( dl < dr ) {
        if( dl < ans ) query(lson[pos],p);
        if( dr < ans ) query(rson[pos],p);
    } else {
        if( dr < ans ) query(rson[pos],p);
        if( dl < ans ) query(lson[pos],p);
    }
}

int main() {
    static int n,m;
    static Point p;
    
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d",ps[i].d,ps[i].d+1);
    
    build(cnt=1,1,n,0);
    
    for(int i=1,t;i<=m;i++) {
        scanf("%d%d%d",&t,p.d,p.d+1);
        if(t == 1) {
            insert(1,p,0);
        } else {
            ans = inf;
            query(1,p);
            printf("%d\n",ans);
        }
    }
    return 0;
}
