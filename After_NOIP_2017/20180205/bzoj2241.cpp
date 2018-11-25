#include<cstdio>
#include<cstring>
#include<cctype>
const int maxn=1e2+2e0;

int in[maxn][maxn],t[maxn][maxn];
int n,m,ans,sum;

inline bool judge(int x,int y) {
    if( sum % ( x * y ) ) return 0;
    memset(t,0,sizeof(t));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            int g = in[i][j] - ( t[i][j] += t[i][j-1] + t[i-1][j] - t[i-1][j-1] );
            if( g < 0 ) return 0;
            if( !g ) continue;
            if( i + x - 1 > n || j + y - 1 > m ) return 0;
            t[i][j] += g , t[i+x][j+y] += g , t[i+x][j] -= g , t[i][j+y] -= g;
        }
    return 1;
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) ) ;
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    n = getint() , m = getint();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            sum += ( in[i][j] = getint() );
    for(int x=n;x;x--)
        for(int y=m;y;y--)
            if( x*y > ans && judge(x,y) ) ans = x * y;
    printf("%d\n",sum/ans);
    return 0;
}
