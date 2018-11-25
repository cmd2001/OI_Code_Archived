#include<cstdio>
typedef long long int lli;
const int maxn=2e5+1e2;

long double h[maxn],a[maxn],s,l;
int n;

inline bool judge(lli t) {
    long double su = 0;
    for(int i=1;i<=n;i++) if( h[i] + a[i] * t >= l ) su += h[i] + a[i] * t;
    return su >= s;
}
inline lli bin() {
    lli ll = 0 , rr = 1e18 , mid;
    if( judge(ll) ) return ll;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( judge(mid) ) rr = mid;
        else ll = mid;
    }
    return rr;
}

int main() {
    scanf("%d%Lf%Lf",&n,&s,&l);
    for(int i=1;i<=n;i++) scanf("%Lf",h+i);
    for(int i=1;i<=n;i++) scanf("%Lf",a+i);
    printf("%lld\n",bin());
    return 0;
}
