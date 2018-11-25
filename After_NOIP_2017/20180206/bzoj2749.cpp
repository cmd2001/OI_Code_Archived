#include<cstdio>
#define lli long long int
#define bool unsigned char
const int maxn=1e5+1e2,lim=1e5;

lli f[maxn];

inline void sieve() {
    static int prime[maxn],cnt;
    static bool vis[maxn];
    f[1] = 1;
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) {
            prime[++cnt] = i , f[i] = f[i-1];
        }
        for(int j=1;i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            f[i*prime[j]] = f[i] + f[prime[j]];
            if( ! ( i % prime[j] ) ) break;
        }
    }
}

inline lli getans() {
    static int m,p,q;
    lli ret = 1;
    scanf("%d",&m);
    while( m-- ) {
        scanf("%d%d",&p,&q);
        if( p == 2 ) --ret;
        ret += f[p] * q;
    }
    return ret;
}

int main() {
    static int T;
    sieve();
    scanf("%d",&T);
    while( T-- )
        printf("%lld\n",getans());
    return 0;
}
