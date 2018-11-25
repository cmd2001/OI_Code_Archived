#include<cstdio>
#include<cstring>
#include<algorithm>
#define bool unsigned char
#define debug cout
typedef long long int lli;
const int maxn=2e3+1e2;

lli su[maxn];
int n,a,b,bit;

inline bool check(const int &bit,const lli &su,const lli &now) {
    return ( ( su >> ( bit + 1 ) ) | now ) == now && ! ( ( su >> bit ) & 1 );
}

namespace Sub1 {
    const int maxn=1e2+1e1;
    bool f[maxn][maxn];
    inline lli getans(int bit) {
        lli ret = 0;
        while(~bit) {
            memset(f,0,sizeof(f)) , **f = 1;
            for(int i=1;i<=n;i++) for(int j=1,bound=std::min(i,b);j<=bound;j++) for(int k=0;k<i;k++) if( f[k][j-1] && check(bit,su[i]-su[k],ret) ) { f[i][j] = 1; break; }
            int cur = 1;
            for(int i=a;i<=b;i++) if( f[n][i] ) cur = 0;
            --bit , ret = ( ret << 1 ) | cur;
        }
        return ret;
    }
}

namespace Sub2 {
    int f[maxn];
    inline lli getans(int bit) {
        lli ret = 0;
        while(~bit) {
            memset(f,0x3f,sizeof(f)) , *f = 0;
            for(int i=1;i<=n;i++) for(int j=0;j<i;j++) if( check(bit,su[i]-su[j],ret) ) f[i] = std::min( f[i] , f[j] + 1 );
            --bit , ret = ( ret << 1 ) | ( f[n] > b );
        }
        return ret;
    }
}

int main() {
    scanf("%d%d%d",&n,&a,&b);
    for(int i=1;i<=n;i++) scanf("%lld",su+i) , su[i] += su[i-1];
    while( su[n] > ( 1ll << bit ) ) ++bit;
    printf("%lld\n",a==1?Sub2::getans(bit):Sub1::getans(bit));
    return 0;
}

