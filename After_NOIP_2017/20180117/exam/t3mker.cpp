#include<bits/stdc++.h>
#define lli long long int
using namespace std;
const lli maxm=2000,lim=2000,llim=1e18;

int prime[maxm],cnt;
unsigned char vis[maxm];

inline void sieve() {
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i;
        for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            if( !( i % prime[j] ) ) break;
        }
    }
}

inline lli dfs(int dep,lli rem) {
    if( llim / rem < dep ) return rem;
    return ( rand() & 1 )  ? dfs(dep+1,rem) : dfs(dep+1,rem*dep);
}

int main() {
    sieve();
    int T = 10 , n = 17;
    freopen("dat.txt","w",stdout);
    srand((unsigned long long)new char);
    printf("%d\n",T);
    for(int t=1;t<=T;t++) {
        printf("%d\n",n);
        for(int j=1;j<=n;j++)
            //printf("%lld%c",prime[j]*prime[j+1],j!=n?' ':'\n');
            printf("%lld%c",dfs(1,1),j!=n?' ':'\n');
    }
    return fclose(stdout);
}