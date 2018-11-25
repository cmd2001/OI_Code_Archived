#include<cstdio>
#include<cstring>
#define bool unsigned char
typedef long long int lli;
const int maxn=2e6+1e2;

int phi[maxn],mu[maxn],siz[maxn],su[maxn],prime[maxn],cnt;
bool vis[maxn];
int n;

inline void sieve() {
    mu[1] = phi[1] = 1;
    for(int i=2;i<=n;i++) {
        if( !vis[i] ) prime[++cnt] = i , mu[i] = -1 , phi[i] = i - 1;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=n;j++) {
            const int tar = i * prime[j];
            vis[tar] = 1;
            if( i % prime[j] ) phi[tar] = phi[i] * ( prime[j] - 1 ) , mu[tar] = -mu[i];
            else {
                phi[tar] = phi[i] * prime[j];
                break;
            }
        }
    }
    for(int i=1;i<=n;i++) ++siz[phi[i]];
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j+=i) su[i] += siz[j];
}
inline lli calc() {
    lli ret = 0;
    for(int i=1;i<=n;i++) if( mu[i] ) {
        for(int j=i,mul=1;j<=n;j+=i,++mul) ret += (lli) mu[i] * phi[mul] * su[j] * su[j]; 
    }
    return ret;
}

inline void reset() {
    memset(phi+1,0,n<<2) , memset(mu+1,0,n<<2) , memset(siz+1,0,n<<2) , memset(su+1,0,n<<2) , memset(vis+1,0,n) , cnt = 0;
}

int main() {
    static int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n) , reset();
        sieve() , printf("%lld\n",calc());
    }
    return 0;
}
