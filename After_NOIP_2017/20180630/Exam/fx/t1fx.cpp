#include<cstdio>
#include<algorithm>
using std::max;
const int maxn=3e4+1e2,maxk=2e2+1e1;
const int inf = 0x3f3f3f3f;

enum Type {VALLY,UP,MOUNT,DOWN};
int f[maxn][maxk][4]; // f[pos][sel][vally/up/mountain/down]

int main() {
    static int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++) for(int j=0;j<4;j++) f[0][i][j] = -inf;
    for(int i=1,x;i<=n;i++) {
        scanf("%d",&x);
        for(int j=1;j<=k;j++) {
            const int mul = 2 - ( j == 1 || j == k );
            f[i][j][VALLY] = max( f[i-1][j][VALLY] , f[i-1][j-1][DOWN] ) - mul * x;
            f[i][j][UP] = max( f[i-1][j][UP] , f[i][j][VALLY] );
            f[i][j][MOUNT] = max( f[i-1][j][MOUNT] , f[i-1][j-1][UP] ) + mul * x;
            f[i][j][DOWN] = max( f[i-1][j][DOWN] , f[i][j][MOUNT] );
            if( mul == 2 ) { // we can remove j .
                f[i][j][UP] = max( f[i][j][UP] , f[i-1][j-1][UP] ); // end segment .
                f[i][j][DOWN] = max( f[i][j][DOWN] , f[i-1][j-1][DOWN] );
            }
        }
    }
    printf("%d\n",max(f[n][k][UP],f[n][k][DOWN]));
    return 0;
}
