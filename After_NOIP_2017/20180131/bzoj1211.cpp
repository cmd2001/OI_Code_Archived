#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define bool unsigned char
#define debug cout
using namespace std;
const int maxn=2e2+1e1,lim=2e2;

int prime[maxn],len;
int cnt[maxn];
lli ans;

inline void sieve() {
    static bool vis[maxn];
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++len] = i;
        for(int j=1;j<=len&&i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            if( ! ( i % prime[j] ) ) break;
        }
    }
}
inline lli fastpow(lli base,int tme) {
    lli ret = 1;
    while( tme ) {
        if( tme & 1 ) ret = ret * base;
        base = base * base;
        tme >>= 1;
    }
    return ret;
}
inline void cut(int t,int delta) {
    for(int p=1,x;p<=t;p++) {
        x = p;
        for(int i=1;i<=len;i++)
            while( ! ( x % prime[i]) )
                cnt[i] += delta , x /= prime[i];
    }
}
inline void getans() {
    ans = 1;
    for(int i=1;i<=len;i++)
        ans *= fastpow(prime[i],cnt[i]);
}

int main() {
    static int n,sum;
    sieve();
    scanf("%d",&n);
    cut(n-2,1);
    for(int i=1,t;i<=n;i++) {
        scanf("%d",&t) , sum += t;
        if( n - 1 && !t ) return puts("0"),0;
        cut(t-1,-1);
    }
    if( sum != n * 2 - 2 ) return puts("0"),0;
    getans();
    printf("%lld\n",ans);
    return 0;
}
