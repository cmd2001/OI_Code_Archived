#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1.5e5+1e2;

int prime[maxn],f[maxn],cnt,n;

inline void sieve() {
    static bool vis[maxn];
    for(int i=2;i<=n;i++) {
        if( !vis[i] ) prime[++cnt] = i;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=n;j++) {
            vis[i*prime[j]] = 1;
            if( ! ( i % prime[j] ) ) break;
        }
    }
}
inline void getf() {
    for(int i=1;i<=cnt;i++) for(int j=1;j<=cnt&&prime[i]+prime[j]<=n;j++) ++f[prime[i]+prime[j]];
}
inline lli calc() {
    lli ret = 0;
    for(int i=1;i<=n;i++) ret += (lli) f[i] * f[n-i];
    return ret;
}

int main() {
    scanf("%d",&n) , sieve() , getf() , printf("%lld\n",calc());
    return 0;
}
