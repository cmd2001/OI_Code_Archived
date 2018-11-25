#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
typedef long long int lli;
using namespace std;
const int maxn=5e4+1e2,lim=5e4;
const lli inf=2147483649ll;

int prime[maxn],cnt;
int n,sq;
lli ans = inf;

inline void sieve() {
    static bool vis[maxn];
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            if( ! ( i % prime[j] ) ) break;
        }
    }
}
inline bool isprime(int x) {
    const int sq = sqrt(x);
    for(int i=2;i<=sq;i++) if( ! ( x % i ) ) return 0;
    return 1;
}

inline void dfs(int pos,int cur,lli pi) {
    if( cur == 1 ) return void(ans=min(ans,pi));
    if( cur > sq && isprime(cur+1) ) return void(ans=min(ans,pi*(cur+1)));
    for(int i=pos+1;i<=cnt;i++) if( ! ( cur % ( prime[i] - 1 ) ) ) {
        int ncur = cur / ( prime[i] - 1 );
        lli npi = pi * prime[i];
        dfs(i,ncur,npi);
        while( ! ( ncur % prime[i] ) ) {
            ncur /= prime[i] , npi *= prime[i] , dfs(i,ncur,npi);
        }
    }
}

int main() {
    scanf("%d",&n) , sq = sqrt(n) , sieve();
    dfs(1,n,1) , printf("%lld\n",ans!=inf?ans:-1ll);
    return 0;
}
