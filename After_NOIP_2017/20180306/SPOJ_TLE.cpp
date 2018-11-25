#include<cstdio>
#include<cstring>
const int maxn=55,maxe=32873;
const int mod=1000000000;

int f[maxn][maxe],sum[maxe],ans;
int c[maxn];
int n,m,lim,neg;

inline void rebuild(int* sou) {
    memcpy(sum,sou,sizeof(sum));
    for(int i=0;i<m;i++)
        for(int j=0;j<lim;j++)
            if( ( j & ( 1 << i ) ) )
                sum[j] = ( sum[j] + sum[j^(1<<i)] ) % mod;
}
inline void trans(int* f,int c) {
    for(int i=0;i<lim;i++)
        if( i % c )
            f[i] = ( f[i] + sum[neg^i] ) % mod;
}

int main() {
    static int T;
    scanf("%d",&T);
    while(T--) {
        memset(f,0,sizeof(f)) , ans = 0;
        scanf("%d%d",&n,&m) , lim = 1 << m , neg = lim - 1;
        for(int i=1;i<=n;i++) scanf("%d",c+i);
        for(int i=0;i<lim;i++) if( i % c[1] ) f[1][i] = 1;
        for(int i=2;i<=n;i++) rebuild(f[i-1]) , trans(f[i],c[i]);
        for(int i=0;i<lim;i++) ans = ( ans + f[n][i] ) % mod;
        printf("%d\n",ans);
    }
    return 0;
}
