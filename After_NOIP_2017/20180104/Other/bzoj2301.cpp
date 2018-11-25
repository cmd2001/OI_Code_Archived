#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e4+1e2;

lli summu[maxn],ans;

inline void getmu(int lim) {
    static int prime[maxn],mu[maxn],cnt;
    static char vis[maxn];
    mu[1] = 1;
    for(int i=2;i<=lim;i++) {
        if( !vis[i] )
            prime[++cnt] = i,
            mu[i] = -1;
        for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            mu[i*prime[j]] = -mu[i];
            if( ! ( i % prime[j] ) ) {
                mu[i*prime[j]] = 0;
                break;
            } 
        }
    }
    for(int i=1;i<=lim;i++)
        summu[i] = summu[i-1] + mu[i];
}

inline lli calc(lli n,lli m) {
    lli ret = 0;
    const lli t = min(n,m);
    for(lli i=1,j;i<=t;i=j+1) {
        j = min( n / ( n / i ) , m / ( m / i ) );
        ret += ( summu[j] - summu[i-1] ) * ( n / i ) * ( m / i );
    }
    return ret;
}

int main() {
    static int t,a,b,c,d,k;
    getmu(5e4);
    /*for(int i=1;i<=10;i++)
        debug<<summu[i]<<" ";debug<<endl;*/
    scanf("%d",&t);
    while( t-- ) {
        scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
        a-- , c--;
        a /= k , b /= k , c /= k , d /= k;
        ans = calc(b,d) + calc(a,c) -  calc(b,c) - calc(a,d);
        printf("%lld\n",ans);
    }
    return 0;
}