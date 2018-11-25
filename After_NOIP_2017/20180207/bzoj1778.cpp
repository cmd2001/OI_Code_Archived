#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cassert>
#define debug cout
using namespace std;
const int maxn=3e2+1e1,maxm=maxn*maxn>>1;
const long double eps = 1e-16;

int x[maxm],y[maxm];
int deg[maxn];
long double g[maxn][maxn],f[maxn];
int n,p,q;

inline int dcmp(long double x) {
    if( fabs(x) <= eps ) return 0;
    return x < 0 ? -1 : 1;
}
inline void gauss() {
    for(int i=1,pos;i<=n;i++) {
        pos = 0;
        for(int j=i;j<=n;j++)
            if( fabs(g[j][i]) > fabs(g[pos][i]) ) pos = j;
        assert( dcmp(g[pos][i]) );
        if( pos != i ) {
            for(int j=1;j<=n+1;j++)
                swap( g[i][j] , g[pos][j] );
            pos = i;
        }
        for(int j=1;j<=n;j++)
            if( i != j && dcmp(g[j][i]) ) {
                long double mul = g[j][i] / g[i][i];
                for(int k=1;k<=n+1;k++)
                    g[j][k] -= g[i][k] * mul;
            }
    }
    for(int i=1;i<=n;i++)
        f[i] = g[i][n+1] / g[i][i];
}
inline void init(int m) {
    long double t = 1.0 - (long double) p / q;
    for(int i=1;i<=m;i++) {
        g[x[i]][y[i]] += t / deg[y[i]];
        g[y[i]][x[i]] += t / deg[x[i]];
    }
    for(int i=1;i<=n;i++)
        g[i][i] -= 1.0;
    g[1][n+1] = - (long double) p / q;
}

int main() {
    static int m;
    scanf("%d%d%d%d",&n,&m,&p,&q);
    for(int i=1;i<=m;i++) scanf("%d%d",x+i,y+i) , ++deg[x[i]] , ++deg[y[i]];
    init(m) , gauss();
    for(int i=1;i<=n;i++)
        printf("%0.9Lf\n",f[i]+eps);
    return 0;
}
