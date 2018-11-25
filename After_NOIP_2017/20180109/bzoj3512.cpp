#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=4e6+1e2,lim=4e6;
const int mod=1e9+7;

int phi[maxn],divs[maxn];
lli sum[maxn],mem[maxn];
lli n,m;

inline void init() {
    static int prime[maxn],cnt;
    
    divs[1] = phi[1] = 1;
    for(lli i=2;i<=lim;i++) {
        if( !phi[i] ) {
            prime[++cnt] = i ,
            phi[i] = i - 1 ,
            divs[i] = 1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
            const int tar = i * prime[j];
            if( ! ( i % prime[j] ) ) {
                phi[tar] = phi[i] * prime[j] , 
                divs[tar] = divs[i] * prime[j];
                break;
            }
            phi[tar] = phi[i] * ( prime[j] - 1 ) ,
            divs[tar] = divs[i];
        }
    }
    for(int i=1;i<=lim;i++)
        sum[i] = ( sum[i-1] + phi[i] ) % mod;
    memset(mem,-1,sizeof(mem));
}
inline lli getsum(lli x) {
    if( x <= lim )
        return sum[x];
    const int p = m / x;
    if( ~mem[p] )
        return mem[p];
    mem[p] = ( x * ( x + 1 ) >> 1 ) % mod;
    for(lli i=2,j;i<=x;i=j+1) {
        j = x / ( x / i );
        mem[p] -= ( j - i + 1 ) * getsum( x / i ) % mod;
        mem[p] %= mod;
    }
    mem[p] = ( mem[p] + mod ) % mod;
    return mem[p];
}
inline lli hsh(lli nn,lli mm) {
    return nn * ( m + 1 ) + mm;
}
inline lli s(lli n,lli m) {
    static map<lli,lli> mp;
    if( !m )
        return 0;
    lli h = hsh(n,m);
    if( mp.count(h) )
        return mp[h];
    if( n == 1 )
        return mp[h] = getsum(m);
    lli ret = 0;
    for(lli i=1;i*i<=n;i++)
        if( ! ( n % i ) ) {
            lli d = i;
            ret = ( ret + phi[n/d] * s( d , m / d ) % mod ) % mod;
            if( i * i == n )
                break;
            d = n / i;
            ret = ( ret + phi[n/d] * s( d , m / d ) % mod ) % mod;
        }
    return mp[h] = ret;
}
inline lli getans() {
    lli ret = 0;
    for(lli i=1;i<=n;i++)
        ret += divs[i] * s(i/divs[i],m) % mod ,
        ret %= mod;
    return ret;
}

int main() {
    init();
    scanf("%lld%lld",&n,&m);
    printf("%lld\n",getans());
    return 0;
}
