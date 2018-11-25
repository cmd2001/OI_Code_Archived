#include<cstdio>
#include<algorithm>
#define lli long long int
#define bool unsigned char
using namespace std;
const int maxn=1e7+1e1;
int lim=1e7;

int p;
lli fac[maxn],rev[maxn],prephi[maxn];
int ns[10010],ms[10010];

inline void sieve() {
    static bool vis[maxn];
    static int prime[664600],cnt;
    
    fac[1] = rev[1] = prephi[1] = 1;
    for(lli i=2;i<=lim;i++) {
        rev[i] = ( p - p / i ) * rev[ p % i ] % p;
        if( !vis[i] ) {
            prime[++cnt] = i ,
            prephi[i] = prephi[i-1] * ( i - 1 ) % p * rev[i] % p;
        } else prephi[i] = prephi[i-1];
        for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
            vis[ i * prime[j] ] = 1;
            if( ! ( i % prime[j] ) ) break;
        }
    }
    for(int i=2;i<=lim;i++)
        fac[i] = fac[i-1] * i % p ,
        rev[i] = rev[i-1] * rev[i] % p;
}

inline lli calcphi(lli m) {
    return fac[m] * prephi[m] % p;
}
inline lli calc(int n,int m) {
    return calcphi(m) * fac[n] % p * rev[m] % p;
}

int main() {
    static int t,tar;
    scanf("%d%d",&t,&p);
    for(int i=1;i<=t;i++)
        scanf("%d%d",ns+i,ms+i) , tar = max( tar , ns[i] );
    lim = min( lim , tar );
    sieve();
    for(int i=1;i<=t;i++)
        printf("%lld\n",calc(ns[i],ms[i]));
    return 0;
}
