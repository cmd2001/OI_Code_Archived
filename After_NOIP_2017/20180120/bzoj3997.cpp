#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define lli long long int
using namespace std;
const int maxn=1e3+1e2;

int in[maxn][maxn];
lli f[maxn][maxn];

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) ) ;
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int n,m,T;
    T = getint();
    while(T--) {
        memset(f,0,sizeof(f));
        n = getint() , m = getint();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                in[i][j] = getint();
        for(int i=n;i;i--)
            for(int j=1;j<=m;j++)
                f[i][j] = max( f[i+1][j] , f[i][j-1] ) ,
                f[i][j] = max( f[i][j] , f[i+1][j-1] + in[i][j] );
        printf("%lld\n",f[1][m]);
    }
    
    return 0;
}