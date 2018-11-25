#include<cstdio>
#include<algorithm>
const int maxn=1e6+1e2;

int d[maxn],u[maxn];
int q[maxn],s=1,t,n,ans=1,tp;

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",d+i,u+i);
    for(int i=1;i<=n;i++) {
        while( s <= t && d[q[s]] > u[i] ) ++s;
        if( s <= t ) ans = std::max( ans , i - q[s] + 1 );
        tp = i;
        while( s <= t && d[q[t]] <= d[i] ) tp = q[t--];
        d[q[++t]=tp] = d[i];
    }
    printf("%d\n",ans);
    return 0;
}
