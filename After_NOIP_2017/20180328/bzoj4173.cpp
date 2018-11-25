#include<cstdio>
typedef long long int lli;
const int mod = 998244353;

inline lli phi(lli n) {
    lli ret = n;
    for(lli i=2;i*i<=n;i++)
        if( ! ( n % i ) ) {
            ( ret /= i ) *= i - 1;
            while( ! ( n % i ) ) n /= i;
        }
    if( n != 1 ) ( ret /= n ) *= n - 1;
    return ret % mod;
}

inline lli calc(lli n,lli m) {
    return phi(n) * phi(m) % mod * ( n % mod ) % mod * ( m % mod ) % mod;
}

int main() {
    static lli n,m;
    scanf("%lld%lld",&n,&m) , printf("%lld\n",calc(n,m));
    return 0;
}