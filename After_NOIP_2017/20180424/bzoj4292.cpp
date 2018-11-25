#include<cstdio>
typedef long long int lli;

inline int f(lli t) {
    int ret = 0;
    while(t) ret += ( t % 10 ) * ( t % 10 ) , t /= 10;
    return ret;
}
int main() {
    static lli k,a,b,n,ans;
    scanf("%lld%lld%lld",&k,&a,&b);
    for(int i=1;i<=1458&&i<=b/k;i++) {
        n = i * k;
        if( n >= a && (lli) f(n) == i ) ++ans;
    }
    printf("%lld\n",ans);
    return 0;
}
