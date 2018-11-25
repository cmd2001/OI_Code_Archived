#pragma GCC optimize(2)
#include<cstdio>
typedef long long int lli;
const int maxn=20,maxs=1<<20,mod=998244353;

int in[maxn],su[maxs],f[maxs],g[maxs];

inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}
inline int fix(int x) {
    while( x >= mod ) x -= mod;
    while( x < 0 ) x += mod;
    return x;
}

int main() {
    static int n,fs,ans;

    scanf("%d",&n) , fs = ( 1 << n ) - 1;
    for(int i=0;i<n;i++) scanf("%d",in+i) , su[1<<i] = in[i] , f[1<<i] = 1;

    #define lowbit(x) (x&-x)
    for(int i=0;i<=fs;i++) su[i] = su[i-lowbit(i)] + su[lowbit(i)];

    for(int i=0;i<=fs;i++) if( su[i] > 0 ) for(int j=0;j<n;j++) if( ! ( i & ( 1 << j ) ) ) adde(f[i|(1<<j)],f[i]);

    g[0] = 1;
    for(int i=0;i<=fs;i++) if( su[i] <= 0 ) for(int j=0;j<n;j++) if( i & ( 1 << j ) ) adde(g[i],g[i^(1<<j)]);

    for(int i=0;i<=fs;i++) adde(ans,mul(fix(su[i]),mul(f[i],g[fs^i])));
    printf("%d\n",ans);
    
    return 0;
}
