#include<cstdio>
typedef long long int lli;
const int maxn=5e3+1e2;

int in[maxn<<1],n;
lli f[maxn][maxn],ans;

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , in[i+n] = in[i];
    for(int i=1;i<=n;i++) for(int j=1;j<n;j++) f[i][j] = f[i][j-1] + ( in[i+j] > in[i] );
    for(int i=1;i<=n;i++) for(int j=i+1;j<i+n;j++) if( in[j] > in[i] ) ans += f[j>n?j-n:j][n-(j-i+1)];
    printf("%lld\n",ans);
    return 0;
}
