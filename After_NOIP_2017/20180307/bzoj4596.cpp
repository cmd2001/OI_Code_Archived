#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
const int maxn=20,maxe=8e3+1e1;
const int mod=1e9+7;

lli d[maxn][maxn],a[maxn][maxn],c[maxn][maxn],ans;
int x[maxe],y[maxe],bels[maxe];
int n,m,full;

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}

inline lli gauss(int len) {
    lli ret = 1;
    for(int i=1,p;i<=len;i++) {
        p = -1;
        for(int j=i;j<=len;j++) if( c[j][i] ) {
            p = j;
            break;
        }
        if( !~p ) return 0;
        if( p != i ) {
            for(int j=1;j<=len;j++) std::swap(c[i][j],c[p][j]);
            p = i , ret = mod - ret;
        }
        const lli mul = fastpow(c[i][i],mod-2);
        ret = ret * c[i][i] % mod;
        for(int j=1;j<=len;j++) c[i][j] = c[i][j] * mul % mod;
        for(int k=1;k<=len;k++) if( k != i && c[k][i] ) {
            const lli mul = c[k][i];
            for(int j=1;j<=len;j++) c[k][j] = ( c[k][j] - c[i][j] * mul % mod + mod ) % mod;
        }
    }
    return ret;
}

inline void rebuild(int sta) {
    memset(d,0,sizeof(d)) , memset(a,0,sizeof(a)) , memset(c,0,sizeof(c));
    for(int i=1;i<=m;i++)
        if( sta & ( 1 << bels[i] ) ) {
            ++d[x[i]][x[i]] , ++d[y[i]][y[i]] ,
            ++a[x[i]][y[i]] , ++a[y[i]][x[i]];
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            c[i][j] = ( d[i][j] - a[i][j] + mod ) % mod;
}

inline int countbit(int x) {
    int ret = 0;
    #define lowbit(x) (x&-x)
    while(x) ++ret , x -= lowbit(x);
    return ret;
}
inline int pm(int x) {
    return ( x & 1 ) ? -1 : 1;
}

inline void calc() {
    full = 1 << ( n - 1 );
    for(int i=0;i<full;i++) {
        rebuild(i);
        ans += gauss(n-1) * pm(n-1-countbit(i)) % mod;
        ans = ( ans % mod + mod ) % mod;
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1,k;i<n;i++) {
        scanf("%d",&k);
        while(k--) {
            bels[++m] = i-1 , scanf("%d%d",x+m,y+m);
        }
    }
    calc();
    printf("%lld\n",ans);
    return 0;
}

