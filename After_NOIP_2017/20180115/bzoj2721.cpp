#include<cstdio>
#define lli long long int
using namespace std;
const int maxn=1e6+1e2;
const int mod=1e9+7;

int mdiv[maxn];
lli cnt[maxn];
unsigned char vis[maxn];
lli ans;

inline void sieve(int n) {
    static int prime[maxn],cnt;
    for(lli i=2;i<=n;i++) {
        if( !vis[i] ) {
            prime[++cnt] = i , mdiv[i] = i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++) {
            vis[i*prime[j]] = 1 , mdiv[i*prime[j]] = prime[j];
            if( ! ( j % prime[j] ) ) break;
        }
    }
}

inline void calc(int n) {
    for(int i=1;i<=n;i++) {
        for(int j=i;j!=1;j/=mdiv[j])
            ++cnt[mdiv[j]];
    }
}

inline void getans(int n) {
    ans = 1;
    for(int i=1;i<=n;i++)
        if( !vis[i] )
            ans = ans * ( ( cnt[i] << 1 | 1 ) % mod ) % mod;
}

int main() {
    static int n;
    scanf("%d",&n);
    sieve(n);calc(n);getans(n);
    printf("%lld\n",ans);
}