#include<cstdio>
#define lli long long int

int main() {
    static lli n,ans=1;
    scanf("%lld",&n);
    for(lli i=2,t;i*i<=n;i++)
        if( ! ( n % i ) ) {
            t = 0;
            while( ! ( n % i ) ) n /= i , ++t;
            ans *= ( ( t << 1 ) | 1 );
        }
    if( n - 1 ) ans *= 3ll;
    ans = ( ans + 1 ) >> 1;
    printf("%lld\n",ans);
    return 0;
}
