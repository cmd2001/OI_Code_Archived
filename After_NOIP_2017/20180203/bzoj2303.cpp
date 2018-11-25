#include<cstdio>
#include<algorithm>
const int maxn=2e6+1e2;
const int mod=1e9;

int fa[maxn],rel[maxn];
int x[maxn>>1],y[maxn>>1],in[maxn>>1];
int n,m,k,ans;

inline int fastpow(int base,int tme,int mod) {
    int ret = 1;
    base = base % mod;
    while( tme ) {
        if( tme & 1) ret = (long long) ret * base % mod;
        base = (long long) base * base % mod;
        tme >>= 1;
    }
    return ret;
}
inline int findfa(int x) {
    if( fa[x] == x ) return x;
    int f = fa[x];
    fa[x] = findfa(fa[x]);
    rel[x] ^= rel[f];
    return fa[x];
}
inline bool merge(int x,int y,int re) {
    int xx = findfa(x) , yy = findfa(y);
    if( xx == yy ) {
        if( re == ( rel[x] ^ rel[y] ) ) return 1;
        return 0;
    }
    if( !yy ) std::swap( x , y ) , std::swap( xx , yy );
    fa[yy] = x;
    rel[yy] = re ^ rel[y];
    return 1;
}
inline bool calcr(int base) {
    if( !merge( 0 , 1 , base ) ) return 0;
    if( !merge( 0 , 1 + n , base ) ) return 0;
    for(int i=1;i<=k;i++) {
        if( x[i] == 1 && y[i] == 1 ) {
            if( in[i] != base ) return 0;
        } else if( x[i] == 1 ) {
            if( !merge( 0 , y[i] + n , in[i] ) ) return 0;
        } else if( y[i] == 1 ) {
            if( ! merge( 0 , x[i] , in[i] ) ) return 0;
        }   
    }
    return 1;
}
inline bool calc(int base) {
    for(int i=1;i<=k;i++)
        if( x[i] != 1 && y[i] != 1 ) {
            int k = ! ( ( x[i] | y[i] ) & 1 );
            if( !merge( x[i] , y[i] + n , in[i] ^ base ^ k ) ) return 0;
        }
    return 1;
}
inline void init() {
    for(int i=0;i<=n+m;i++)
        fa[i] = i , rel[i] = 0;
}
inline int count() {
    int ret = 0;
    for(int i=1;i<=n+m;i++)
        ret += ( fa[i] == i );
    return ret;
}

int main() {
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;i++)
        scanf("%d%d%d",x+i,y+i,in+i);
    for(int b=0;b<2;b++) {
        init();
        if( calcr(b) && calc(b) )
            ans = ( ans + fastpow(2,count(),mod) ) % mod;
    }
    printf("%d\n",ans);
    return 0;
}

