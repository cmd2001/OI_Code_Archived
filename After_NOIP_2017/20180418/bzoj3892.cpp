#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int maxn=5e2+1e1;
const int inf=0x3f3f3f3f;

int x[maxn],y[maxn],f[maxn][maxn];
int n,k,ans;

inline int dis(int a,int b) {
    return abs(x[a]-x[b]) + abs(y[a]-y[b]);
}
int main() {
    scanf("%d%d",&n,&k) , memset(f,0x3f,sizeof(f)) , ans = **f , f[1][0] = 0;
    for(int i=1;i<=n;i++) scanf("%d%d",x+i,y+i);
    for(int i=2;i<=n;i++) {
        for(int j=0,lim=min(i-1,k);j<=lim;j++)
            for(int u=0;u<=j;u++)
                f[i][j] = min( f[i][j] , f[i-u-1][j-u] + dis(i-u-1,i) );
    }
    for(int i=0;i<=k;i++) ans = min( ans , f[n][i] );
    printf("%d\n",ans);
    return 0;
}
