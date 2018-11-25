#include<bits/stdc++.h>
using namespace std;
const int maxn=3e2+1e1,maxe=5e2+1e1;

int f[maxn][maxe];

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) for(int j=0;j<=m;j++) f[i][j] = i;
    for(int i=1;i<=n;i++)
        for(int k=1;k<=i;k++)
            for(int j=2;j<=m;j++)
                f[i][j] = min( f[i][j] , max( f[k-1][j-1] , f[i-k][j] ) + 1 );
    printf("%d\n",f[n][m]);
    return 0;                
}