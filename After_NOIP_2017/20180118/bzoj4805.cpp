#include<cstdio>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e6+1e2,lim=5e6;

lli sum[maxn],mp[maxn];
int n;

inline void sieve() {
    static int prime[maxn],cnt;
    sum[1] = 1;
    for(lli i=2;i<=lim;i++) {
        if( !sum[i] )
            prime[++cnt] = i , sum[i] = i - 1;
        for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
            if( ! ( i % prime[j] ) ) {
                sum[i*prime[j]] = sum[i] * prime[j];
                break;
            }
            sum[i*prime[j]] = sum[i] * ( prime[j] - 1 );
        }
    }
    for(int i=1;i<=lim;i++)
        sum[i] += sum[i-1];
}

inline lli calc(lli x) {
    if( x <= lim ) return sum[x];
    int t = n / x;
    if( mp[t] ) return mp[t];
    mp[t] = x * ( x + 1 ) >> 1;
    for(lli i=2,j;i<=x;i=j+1) {
        j = x / ( x / i );
        mp[t] -= ( j - i + 1 ) * calc( x / i );
    }
    return mp[t];
}

int main() {
    scanf("%d",&n);
    sieve();
    printf("%lld\n",calc(n));
    return 0;
}