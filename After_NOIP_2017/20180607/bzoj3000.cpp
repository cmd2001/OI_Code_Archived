#include<cstdio>
#include<cmath>
typedef long double ldb;
typedef long long int lli;
const ldb pi = acos(-1.0) , e = exp(1.0) , eps = 1e-10;

inline ldb Log(const ldb &base,const ldb &x) {
    return log(x) / log(base);
}

int main() {
    static lli n,k;
    while( scanf("%lld%lld",&n,&k) == 2 ) {
        if( n <= 10000 ) {
            ldb ans = 0;
            for(int i=1;i<=n;i++) ans += log(i);
            ans = ans / log(k) + eps;
            printf("%lld\n",(lli)ceil(ans));
        } else printf("%lld\n",(lli)(0.5*Log(k,2*pi*n)+n*Log(k,n)-n*Log(k,e))+1);
    }
    return 0;
}

