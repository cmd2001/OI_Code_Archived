#include<cstdio>
#include<algorithm>
#define lli long long int
#define bool unsigned char
const int maxn=5e4+1e2,lim=5e4;

lli f[maxn],su[maxn];

inline void sieve() {
    static int prime[maxn],cnt;
    static bool vis[maxn];
    su[1] = 1;
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i , su[i] = -1;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
            const int tar = i * prime[j];
            vis[tar] = 1;
            if( i % prime[j] ) su[tar] = -su[i];
            else break;
        }
    }
    for(int i=1;i<=lim;i++) su[i] += su[i-1];
}
inline lli force(int x) {
    lli ret = 0;
    for(int i=1,j;i<=x;i=j+1) {
        j = x / ( x / i );
        ret += (lli)( j - i + 1 ) * ( x / i );
    }
    return ret;
}
inline lli getans(int n,int m) {
    lli ret = 0;
    if( n > m ) std::swap(n,m); // now assert n <= m .
    for(int i=1,j;i<=n;i=j+1) {
        j = std::min( n / ( n / i ) , m / ( m / i ) );
        ret += ( su[j] - su[i-1] ) * f[n/i] * f[m/i];
    }
    return ret;
}

int main() {
    static int T,n,m;
    sieve();
    for(int i=1;i<=lim;i++) f[i] = force(i);
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&m);
        printf("%lld\n",getans(n,m));
    }
    return 0;
}
