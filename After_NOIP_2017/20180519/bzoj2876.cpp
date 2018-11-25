#include<cstdio>
const int maxn=1e4+1e2;
const double inf = 1e9 , eps = 1e-12;

double s[maxn],k[maxn],vp[maxn],v[maxn],E,ans;
int n;

inline double spd(double lam,double k,double vp) {
    double l = vp , r = inf , mid;
    while( r - l > eps ) {
        mid = ( l + r ) / 2.0;
        if( 2 * lam * k * mid * mid * ( mid - vp ) > 1.0 ) r = mid;
        else l = mid;
    }
    return l;
}
inline double calc(double lam) { // returing E .
    double ret = 0;
    for(int i=1;i<=n;i++) v[i] = spd(lam,k[i],vp[i]) , ret += ( v[i] - vp[i] ) * ( v[i] - vp[i] ) * k[i] * s[i];
    return ret;
}
inline void bin() {
    double l = 0 , r = inf , mid;
    while( r - l > eps ) {
        mid = ( l + r ) / 2.0;
        if( calc(mid) >= E ) l = mid;
        else r = mid;
    }
}
inline double getans() {
    double ret = 0;
    for(int i=1;i<=n;i++) ret += s[i] / v[i];
    return ret;
}

int main() {
    scanf("%d%lf",&n,&E);
    for(int i=1;i<=n;i++) scanf("%lf%lf%lf",s+i,k+i,vp+i);
    bin() , printf("%0.8lf\n",getans());
    return 0;
}
