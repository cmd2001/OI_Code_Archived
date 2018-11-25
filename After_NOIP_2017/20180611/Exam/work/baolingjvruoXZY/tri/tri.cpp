#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=3e6+1e2,lim=3e6;
const int mod=1e9+7,inv[]={0,1,500000004,333333336};

inline lli C3(lli x) {
    lli ret = 1; x %= mod;
    for(int i=0;i<3;i++) ret = ret * ( x - i + mod ) % mod , ret = ret * inv[i+1] % mod;
    return ret;
}
inline lli LSU(lli x) {
    return x * ( x + 1 ) % mod * inv[2] % mod;
}

lli phi[maxn],phix[maxn],phixx[maxn];
int n,m;

inline void sieve() {
    static int prime[maxn],cnt;
    static bool vis[maxn];
    phi[1] = 1;
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i , phi[i] = i - 1;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
            const int tar = i * prime[j];
            vis[tar] = 1;
            if( i % prime[j] ) phi[tar] = phi[i] * ( prime[j] - 1 );
            else { phi[tar] = phi[i] * prime[j]; break; }
        }
    }
    for(int i=1;i<=lim;i++) {
        phix[i] = phi[i] * i % mod , phixx[i] = phix[i] * i % mod;
        phi[i] = ( phi[i] + phi[i-1] ) % mod , phix[i] = ( phix[i] + phix[i-1] ) % mod , phixx[i] = ( phixx[i] + phixx[i-1] ) % mod;
    };
}

inline lli initans() {
    lli ret = ( ( C3((lli)n*m) - n * C3(m) - m * C3(n) ) % mod + mod ) % mod;
    ret = ( ret + LSU(n-1) * LSU(m-1) % mod * 2 % mod ) % mod;
    return ret;
}
inline lli getsub() { // assert n <= m .
    lli ret = 0;
    if( n > m ) swap(n,m);
    for(int i=1,j;i<n;i=j+1) {
        j = min( ( n - 1 ) / ( ( n - 1 ) / i ) , ( m - 1 ) / ( ( m - 1 ) / i ) );
        const lli apn = ( n - 1 ) / i , apm = ( m - 1 ) / i;
        ret += ( phi[j] - phi[i-1] + mod ) % mod * apn % mod * apm % mod * n % mod * m % mod , ret %= mod;
        ret += ( phixx[j] - phixx[i-1] + mod ) % mod * LSU(apn) % mod * LSU(apm) % mod , ret %= mod;
        ret -= ( phix[j] - phix[i-1] + mod ) % mod * LSU(apn) % mod * apm % mod * m % mod , ret = ( ret + mod ) % mod;
        ret -= ( phix[j] - phix[i-1] + mod ) % mod * LSU(apm) % mod * apn % mod * n % mod , ret = ( ret + mod ) % mod;
    }
    ret = ret * 2 % mod;
    return ret;
}

int main() {
    freopen("tri.in","r",stdin);
    freopen("tri.out","w",stdout);
    sieve();
    while( scanf("%d%d",&n,&m) == 2 && ( n || m ) ) n++ , m++ , printf("%lld\n",(initans()-getsub()+mod)%mod);
    return fclose(stdout);
}
