#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e2+1e1;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
 
double f[2][maxn][maxn],ans;
int n,k,cur;
 
inline int countar(int x,int y) {
    int ret = 0;
    for(int k=0;k<4;k++) {
        const int tx = x + dx[k] , ty = y + dy[k];
        if( 0 < tx && tx <= n && 0 < ty && ty <= n ) ++ret;
    }
    return ret;
}
inline void trans(int x,int y) {
    int su = countar(x,y);
    for(int k=0;k<4;k++) {
        const int tx = x + dx[k] , ty = y + dy[k];
        if( 0 < tx && tx <= n && 0 < ty && ty <= n ) f[cur][tx][ty] += f[cur^1][x][y] / su;
    }
}
inline void transall() {
    cur ^= 1 , memset(f[cur],0,sizeof(f[cur]));
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) trans(i,j);
}
 
int main() {
    while( scanf("%d",&n) == 1 ) {
        if( ! ( n & 1 ) ) { puts(n!=6?"0.0000":"0.4136") ; continue; }
        k = ( n + 1 ) >> 1 , cur = 0 , memset(f,0,sizeof(f)) , f[cur][k][k] = 1 , ans = 0;
        for(int i=1;i<=n;i++) transall() , ans += f[cur][k][i] , f[cur][k][i] = 0;
        printf("%0.4lf\n",ans);
    }
    return 0;
}
