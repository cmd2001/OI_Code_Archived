#include<iostream>
#include<cstdio>
#include<cmath>
#define debug cout
using namespace std;
const double eps=1e-8;

double a,b,l,r,ans;

inline double corf(double x) {
    double r = 1 - ( x * x ) / ( a * a );
    return sqrt(r) * b;
}
inline double f(double x) {
    return corf(x) * 2;
}
inline double calc(double l,double r) {
    double mid = ( l + r ) / 2.0;
    return ( r - l ) * ( f(l) + 4 * f(mid) + f(r) ) / 6;
}
inline double simpson(double l,double r) {
    const double mid = ( l + r ) / 2;
    const double ret = calc(l,r);
    if( fabs( ret - calc(l,mid) - calc(mid,r) ) <= eps )
        return ret;
    return simpson(l,mid) + simpson(mid,r);
}

int main() {
    static int n;
    scanf("%d",&n);
    while( n-- ) {
        scanf("%lf%lf%lf%lf",&a,&b,&l,&r);
        ans = simpson(l,r);
        printf("%0.3lf\n",ans);
    }
    return 0;
}
