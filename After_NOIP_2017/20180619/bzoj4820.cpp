#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=3e2+1e1;
const double eps=1e-10;

char in[maxn][maxn];
int fail[maxn][maxn];
double a[maxn][maxn],pows[maxn];
int n,m;


inline void kmp(char* s,int* fail) {
    fail[1] = 0;
    for(int i=1,j;i<m;i++) {
        j = fail[i];
        while( j && s[i+1] != s[j+1] ) j = fail[j];
        fail[i+1] = j + ( s[i+1] == s[j+1] );
    }
}
inline double calc(int a,int b) {
    double ret = 0;
    int cur = 0;
    for(int i=1;i<=m;i++) {
        while( cur && in[a][cur+1] != in[b][i] ) cur = fail[a][cur];
        cur += ( in[a][cur+1] == in[b][i] );
    }
    while(cur) ret += pows[m-cur] , cur = fail[a][cur];
    return ret;
}

inline void gauss() {
    for(int i=1;i<=n;i++) {
        int pos = 0;
        for(int j=i;j<=n;j++) if( fabs(a[j][i]) > fabs(a[pos][i]) ) pos = j;
        if( pos != i ) for(int j=1;j<=n+1;j++) swap(a[i][j],a[pos][j]);
        for(int j=1;j<=n;j++) if( j != i && fabs(a[j][i]) > eps ) {
            const double mul = a[j][i] / a[i][i];
            for(int k=1;k<=n+1;k++) a[j][k] -= a[i][k] * mul;
        }
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",in[i]+1) , kmp(in[i],fail[i]);
    *pows = 1; for(int i=1;i<=m;i++) pows[i] = pows[i-1] * 0.5;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j] = calc(i,j);
    for(int i=1;i<=n;i++) a[n+1][i] = 1.0 , a[i][n+1] = -1.0;
    ++n , a[n][n+1] = 1.0;
    gauss();
    for(int i=1;i<n;i++) printf("%0.10lf\n",a[i][n+1]/a[i][i]);
    return 0;
}
