#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;
const int maxn=4e2+1e1,maxe=2e1+1e1;
const double eps=1e-10;

vector<int> tar[maxe];
double trans[maxe][maxe],p[maxe],deg[maxe];
double f[maxn][maxn];
int n,m,e,a,b;

inline void gauss() {
    for(int i=1,k;i<=e;i++) {
        k = -1;
        for(int j=i;j<=e;j++)
            if( !~k || fabs(f[j][i]) > fabs(f[k][i]) )
                k = j;
        if( k != i ) {
            for(int j=1;j<=e+1;j++) swap(f[k][j],f[i][j]);
            k = i;
        }
        const double mul = 1.0 / f[i][i];
        for(int j=1;j<=e+1;j++) f[i][j] *= mul;
        for(int t=1;t<=e;t++) if( t != i && fabs(f[t][i]) > eps ) {
            const double mul = f[t][i];
            for(int j=1;j<=e+1;j++) f[t][j] -= f[i][j] * mul;
        }
    }
}

inline int cov(int x,int y) {
    return n * --x + y;
}
inline void build() {
    for(int i=1;i<=n;i++) {
        trans[i][i] = p[i]; deg[i] = ( 1 - p[i] ) / deg[i];
        for(unsigned j=0;j<tar[i].size();j++) trans[i][tar[i][j]] = deg[i];
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int x=1;x<=n;x++)
                for(int y=1;y<=n;y++) {
                    if( i == j ) continue ;
                    f[cov(x,y)][cov(i,j)] -= trans[i][x] * trans[j][y];
                }
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[cov(i,j)][cov(i,j)] += 1.0;
    f[cov(a,b)][e+1] += 1;
}

int main() {
    scanf("%d%d%d%d",&n,&m,&a,&b) , e = n * n;
    for(int i=1,x,y;i<=m;i++) {
        scanf("%d%d",&x,&y) , ++deg[x] , ++deg[y] ,
        tar[x].push_back(y) , tar[y].push_back(x);
    }
    for(int i=1;i<=n;i++) scanf("%lf",p+i);
    build() , gauss();
    for(int i=1;i<=n;i++) printf("%0.6lf ",f[cov(i,i)][e+1]+eps);
    putchar('\n');
    return 0;
}

