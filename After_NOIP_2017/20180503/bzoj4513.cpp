#include<cstdio>
#include<algorithm> 
#include<cstring>
typedef long long int lli;
const int maxn=1e2+1e1;

lli f[maxn][2][2][2],g[maxn][2][2][2]; // f is sum , g is count .
int ba[maxn],bb[maxn],bc[maxn],mod;

inline void dfs(int bit,int la,int lb,int lc) { // bit is the bit that we are determining in range [1,64] .
    if( ~f[bit][la][lb][lc] ) return;
    if( !bit ) {
        f[bit][la][lb][lc] = 0 , g[bit][la][lb][lc] = 1;
        return;
    } int lima = !la || ba[bit] , limb = !lb || bb[bit] , limc = lc && bc[bit];
    f[bit][la][lb][lc] = g[bit][la][lb][lc] = 0;
    for(int i=0;i<=lima;i++) for(int j=0;j<=limb;j++) if( ( i ^ j ) >= limc ) {
        int ta = la&&i==lima , tb = lb&&j==limb , tc = lc&&(i^j)==limc;
        dfs(bit-1,ta,tb,tc);
        g[bit][la][lb][lc] = ( g[bit][la][lb][lc] + g[bit-1][ta][tb][tc] ) % mod ,
        f[bit][la][lb][lc] = ( f[bit][la][lb][lc] + f[bit-1][ta][tb][tc] + ( (lli) ( i ^ j ) << ( bit -  1 ) ) % mod * g[bit-1][ta][tb][tc] % mod ) % mod;
    }
}

inline int cutbit(lli t,int* dst) {
    int ret = 0; memset(dst,0,sizeof(int)*maxn);
    while(t) dst[++ret] = t & 1 , t >>= 1;
    return ret;
}

int main() {
    static int T,mx;
    static lli n,m,k,ans;
    scanf("%d",&T);
    while(T--) {
        scanf("%lld%lld%lld%d",&n,&m,&k,&mod) , --n , --m , memset(f,-1,sizeof(f)) , memset(g,0,sizeof(g)) , mx = std::max( cutbit(k,bc) , std::max( cutbit(n,ba) , cutbit(m,bb) ) ) ,
        dfs(mx,1,1,1) , ans = (f[mx][1][1][1]-g[mx][1][1][1]*(k%mod)%mod+mod)%mod , printf("%lld\n",ans);
    }
    return 0;
}

