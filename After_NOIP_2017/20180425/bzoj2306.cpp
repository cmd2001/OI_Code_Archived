#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=1e2+1e1,inf=0x3f3f3f3f;
const long double eps=1e-8;

long double in[maxn],f[maxn][maxn],tp[maxn][maxn];
int n;

inline void reset(long double dst[maxn][maxn]) {
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dst[i][j] = -inf;
    for(int i=1;i<=n;i++) dst[i][i] = 0;
}
inline void trans(const double &mul) {
    reset(tp);
    for(int i=1;i<=n;i++)
        for(int k=1;k<=n;k++)
            for(int j=1;j<=n;j++)
                tp[i][j] = std::max( tp[i][j] , f[i][k] + f[k][j] * mul );
    memcpy(f,tp,sizeof(f));
}

int main() {
    static int m,v;
    static long double p , ans = -inf;
    scanf("%d%d",&n,&m) , reset(f);
    for(int i=1;i<=n;i++) scanf("%Lf",in+i);
    scanf("%d%Lf",&v,&p);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , f[a][b] = in[b] * p;
    for(long double mul = p ; mul > eps ; mul = mul * mul ) trans(mul);
    for(int i=1;i<=n;i++) ans = std::max( ans , f[v][i] + in[v] );
    printf("%0.1Lf\n",ans);
    return 0;
}
