#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=2e2+1e1,maxlen=8e4+1e3,delta=4e4+50;

char f[maxn][maxlen];
int x[maxn],y[maxn],n;
double ans;

inline void dp(int* s) {
    memset(f,0,sizeof(f));
    f[0][delta] = 1;
    for(int i=1;i<=n;i++)
        for(int j=0;j<maxlen;j++) {
            if( j - s[i] >= 0 ) f[i][j] |= f[i-1][j-s[i]];
            if( j + s[i] < maxlen ) f[i][j] |= f[i-1][j+s[i]];
        }
    for(int i=0;i<maxn;i++)
        if( f[n][i+delta] || f[n][delta-i] ) {
            ans += i*i;
            return;
        }
}
int main() {
    freopen("dat.txt","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d%d",x+i,y+i);
        ans -= ( x[i]*x[i] + y[i]*y[i] );
    }
    
    dp(x); dp(y);
    
    printf("%0.2lf\n",ans/2.0);
    
    return 0;
}

