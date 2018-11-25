#include<cstdio>
const int maxn = (1<<20) + 5;

double f[maxn],g[maxn],ans;
int mul[maxn];

int main() {
    static int n,full,u;
    scanf("%d",&n) , full = 1 << n , *mul = 1;
    for(int i=0;i<full;i++) scanf("%lf",f+i) , u |= ( f[i] ? i : 0 );
    for(int i=1;i<full;i++) mul[i] = ( i & 1 ) ? -mul[i>>1] : mul[i>>1];
    if( u != full - 1 ) return puts("INF"),0;
    for(int bit=0;bit<n;bit++) for(int i=0;i<full;i++) if( i & ( 1 << bit ) ) f[i] += f[i^(1<<bit)];
    for(int i=0;i<full-1;i++) ans += mul[(full-1)^i] / ( f[i] - 1 );
    return printf("%0.16lf\n",ans) , 0;
}
