#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=5e2+1e1;
const double eps=1e-5;
const int inf=0x3f3f3f3f;

inline int dcmp(const double &x) {
    return fabs(x) <= eps ? 0 : x < 0 ? -1 : 1;
}

struct Circle {
    double x,r;
    inline bool inside(const double &xx) {
        return x - r <= xx && xx <= x + r;
    }
    inline double hei(const double &xx) {
        const double dx = xx - x;
        return sqrt( r * r - dx * dx );
    }
}cs[maxn];
struct Line {
    double k,b,sx,tx;
    inline bool inside(const double &xx) {
        return sx <= xx && xx <= tx;
    }
    inline double hei(const double &xx) {
        return k * xx + b;
    }
}ls[maxn];

int sizcir,sizlne;

inline bool inside(const Circle &a,const Circle &b) {
    return dcmp( fabs(a.x-b.x) - fabs(a.r-b.r) ) <= 0;
}
inline Line calclne(const Circle &a,const Circle &b) { // assart not inside and a.x < b.x .
    const double sinalp = ( a.r - b.r ) / ( a.x - b.x ) , cosalp = sqrt( 1 - sinalp * sinalp );
    const double ax = a.x - a.r * sinalp , ay = a.r * cosalp;
    const double bx = b.x - b.r * sinalp , by = b.r * cosalp;
    const double kk = ( ay - by ) / ( ax - bx ) , bb = ay - kk * ax;
    return (Line){kk,bb,ax,bx};
}
inline double gethei(const double &x) {
    double ret = 0;
    for(int i=1;i<=sizcir;i++) if( cs[i].inside(x) ) ret = max( ret , 2 * cs[i].hei(x) );
    for(int i=1;i<=sizlne;i++) if( ls[i].inside(x) ) ret = max( ret , 2 * ls[i].hei(x) );
    return ret;
}
inline double f(const double &l,const double &r) {
    const double mid = ( l + r ) / 2;
    return ( r - l ) * ( gethei(l) + 4 * gethei(mid) + gethei(r) ) / 6;
}
inline double simpson(const double &l,const double &r,const double &fnow) {
    const double mid = ( l + r ) / 2.0;
    const double fl = f(l,mid) , fr = f(mid,r);
    if( !dcmp(fl+fr-fnow) ) return fl + fr;
    return simpson(l,mid,fl) + simpson(mid,r,fr);
}

int main() {
    static int n;
    static double alpha,mul,l=inf,r=-inf;
    scanf("%d%lf",&n,&alpha) , sizcir = ++n , mul = 1 / tan(alpha);
    for(int i=1;i<=n;i++) scanf("%lf",&cs[i].x) , cs[i].x *= mul , cs[i].x += cs[i-1].x;
    for(int i=1;i<n;i++) scanf("%lf",&cs[i].r);
    for(int i=1;i<=n;i++) l = min( l , cs[i].x - cs[i].r ) , r = max( r , cs[i].x + cs[i].r );
    for(int i=2;i<=n;i++) {
        if( !inside(cs[i-1],cs[i]) ) ls[++sizlne] = calclne(cs[i-1],cs[i]);
    }
    printf("%0.2lf\n",simpson(l,r,f(l,r)));
    return 0;
}
