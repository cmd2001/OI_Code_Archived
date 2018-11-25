#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=1e3+1e2;
const double eps=1e-13;

int dcmp(const double &x) {
    return fabs(x) <= eps ? 0 : ( x < 0 ? -1 : 1 );
}
struct Circle {
    double x,y,r;
    friend bool operator < (const Circle &a,const Circle &b) {
        return a.r < b.r;
    }
}cir[maxn];
struct Segment {
    double l,r;
    friend bool operator < (const Segment &a,const Segment &b) {
        return a.l < b.l;
    }
}ss[maxn];
double x[maxn],y[maxn],r[maxn];
char flag[maxn];
int n;

inline double f(const double now) {
    static double od,rd,ll,rr;
    int cnt = 0;
    for(int i=1;i<=n;i++) {
        if( dcmp( r[i] - fabs( now - x[i] ) ) <= 0 ) continue;
        od = fabs( now - x[i] );
        rd = sqrt( r[i] * r[i] - od * od );
        ss[++cnt] = (Segment){y[i]-rd,y[i]+rd};
    }
    if( !cnt ) return 0.0;
    sort(ss+1,ss+1+cnt);
    double ret = 0.0; ll = ss[1].l , rr = ss[1].r;
    for(int i=2;i<=cnt;i++) {
        if( ss[i].l > rr ) ret += rr - ll , ll = ss[i].l , rr = ss[i].r;
        else rr = max( rr , ss[i].r );
    }
    ret += rr - ll;
    return ret;
}
inline double calc(const double &fl,const double &fmid,const double &fr) {
    return ( fl + fmid * 4.0 + fr ) / 6;
}
inline double simpson(const double &l,const double &r,const double &fnow,const double &cl,const double &cmid,const double &cr) {
    const double mid = ( l + r ) / 2 , clmid = f( ( l + mid) / 2.0 ) , crmid = f( ( mid + r ) / 2.0 );
    const double fl = calc(cl,clmid,cmid) * ( mid - l ) , fr = calc(cmid,crmid,cr) * ( r - mid );
    if( !dcmp( fnow - fl - fr ) ) return fnow;
    return simpson(l,mid,fl,cl,clmid,cmid) + simpson(mid,r,fr,cmid,crmid,cr);
}

inline double dis(const double &x,const double &xx,const double &y,const double &yy) {
    const double dx = x - xx , dy = y - yy;
    return sqrt( dx * dx + dy * dy );
}
inline bool incir(const int &i,const int &j) { // judge i inside j or not.
    return dcmp( ( cir[j].r - cir[i].r ) -  dis(cir[i].x,cir[j].x,cir[i].y,cir[j].y) ) >= 0;
}
inline void unicir() {
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++) {
            if( incir(i,j) ) {
                flag[i] = 1;
                break;
            }
        }
    int t = n; n = 0;
    for(int i=1;i<=t;i++)
        if( !flag[i] ) {
            ++n , x[n] = cir[i].x , y[n] = cir[i].y , r[n] = cir[i].r;
        }
}

int main() {
    static double ml=1e9,mr=-1e9,fnow,cl,cmid,cr,ans,x,y,r;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%lf%lf%lf",&x,&y,&r) , cir[i] = (Circle){x,y,r};
        ml = min( ml , x - r ) , mr = max( mr , x + r );
    }
    sort(cir+1,cir+1+n);
    unicir();
    cl = f(ml) , cmid = f( ( ml + mr ) / 2.0 ) , cr = f(mr);
    fnow = calc(cl,cmid,cr) * ( mr - ml );
    ans = simpson(ml,mr,fnow,cl,cmid,cr);
    printf("%0.3lf\n",ans);
    return 0;
}

