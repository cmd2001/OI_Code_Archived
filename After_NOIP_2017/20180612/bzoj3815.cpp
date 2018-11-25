#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=65539;
const double inf = 1e3, eps = 1e-5;

inline double jez(const double &t) {
    return fabs(t) <= eps;
}
double a,b,lastans=0.1;
namespace Decode {
    inline double f(double x) {
        return a * x - b * sin(x);
    }
    inline double dec(double tar,double l=-1e2,double r=1e2) {
        static const double eps = 1e-6;
        double mid;
        while( r - l > eps ) {
            mid = ( l + r ) / 2.0;
            if( f(mid*lastans+1.0) > tar ) r = mid;
            else l = mid;
        }
        return l;
    }
    inline double getreal(double l=-1e2,double r=1e2) {
        double t; scanf("%lf",&t);
        return dec(t,l,r);
    }
}
using Decode::getreal;

int cmp;
struct Point {
    double d[3]; int id; bool used;
    friend bool operator < (const Point &a,const Point &b) {
        return a.d[cmp] < b.d[cmp];
    }
}ps[maxn],rp;
struct Circle {
    double d[3],r;
}cir;

int rec[maxn]; // Node of point i .

const int nxt[]={1,2,0};
struct KDTree {
    int lson[maxn<<1],rson[maxn<<1],fa[maxn<<1],root,cnt;
    double mx[maxn<<1][3],mi[maxn<<1][3];
    Point nv[maxn<<1];
    KDTree() { root = cnt = 1; }
    inline void maintain(int pos) {
        if( nv[pos].used ) for(int i=0;i<3;i++) mi[pos][i] = mx[pos][i] = nv[pos].d[i];
        else for(int i=0;i<3;i++) mi[pos][i] = inf , mx[pos][i] = -inf;
        if( lson[pos] ) for(int i=0;i<3;i++) mi[pos][i] = min( mi[pos][i] , mi[lson[pos]][i] ) , mx[pos][i] = max( mx[pos][i] , mx[lson[pos]][i] );
        if( rson[pos] ) for(int i=0;i<3;i++) mi[pos][i] = min( mi[pos][i] , mi[rson[pos]][i] ) , mx[pos][i] = max( mx[pos][i] , mx[rson[pos]][i] );
    }
    inline void maintain_chain(int pos) {
        while(pos) maintain(pos) , pos = fa[pos];
    }
    inline int build(int pos,int dir,int ll,int rr) {
        const int mid = ( ll + rr ) >> 1; cmp = dir , nth_element(ps+ll,ps+mid,ps+rr+1);
        nv[pos] = ps[mid] , rec[nv[pos].id] = pos;
        if( ll < mid ) fa[build(lson[pos]=++cnt,nxt[dir],ll,mid-1)] = pos;
        if( mid < rr ) fa[build(rson[pos]=++cnt,nxt[dir],mid+1,rr)] = pos;
        return maintain(pos) , pos;
    }
    inline int insert(int &pos,int dir,const Point &p) {
        if( !pos ) return nv[pos=++cnt] = p , maintain(rec[p.id] = pos) , pos;
        return cmp = dir , maintain(fa[insert(p<nv[pos]?lson[pos]:rson[pos],nxt[dir],p)] = pos) , pos;
    }
    inline double sq(const double &x) { return x * x; }
    inline double near(int pos,const Circle &c) {
        double su = 0;
        for(int i=0;i<3;i++) {
            if( c.d[i] < mi[pos][i] ) su += sq( mi[pos][i]-c.d[i] );
            else if( mx[pos][i] < c.d[i] ) su += sq( c.d[i] - mx[pos][i] );
        }
        return sqrt(su);
    }
    inline double far(int pos,const Circle &c) {
        double su = 0;
        for(int i=0;i<3;i++) su += sq( max( fabs(c.d[i]-mi[pos][i]) , fabs(c.d[i]-mx[pos][i] ) ) );
        return su;
    }
    inline double dis(const Point &p,const Circle &c) {
        double su = 0;
        for(int i=0;i<3;i++) su += sq(p.d[i]-c.d[i]);
        return sqrt(su);
    }
    inline int query(int pos,const Circle &c) {
        if( !pos || near(pos,c) > c.r + eps || far(pos,c) < c.r-eps ) return 0;
        if( nv[pos].used && jez(dis(nv[pos],c) - c.r) ) return nv[pos].id;
        int ret = query(lson[pos],c);
        return ret ? ret : query(rson[pos],c);
    }
}kdt;

int n,m;

inline void init() {
    for(int i=1;i<=n;i++) {
        for(int j=0;j<3;j++) scanf("%lf",ps[i].d+j);
        ps[i].id = i , ps[i].used = 1;
    }
    kdt.build(1,0,1,n);
}
inline void replace(const Point &p) {
    kdt.nv[rec[p.id]].used = 0 , kdt.maintain_chain(rec[p.id]);
    kdt.insert(kdt.root,0,p);
}

int main() {
    scanf("%d%d%lf%lf",&n,&m,&a,&b) , init();
    for(int i=1,o;i<=m;i++) {
        scanf("%d",&o);
        if( !o ) {
            rp.id = (int)( getreal(1,n) + 0.5 ) , rp.used = 1;
            for(int i=0;i<3;i++) rp.d[i] = getreal();
            replace(rp);
        } else {
            for(int i=0;i<3;i++) cir.d[i] = getreal();
            cir.r = getreal(0,4e2) , printf("%0.lf\n",lastans=kdt.query(1,cir));
        }
    }
    return 0;
}
