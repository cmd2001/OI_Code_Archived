#include<cstdio>
#include<cmath>
const int maxn=1e3+1e2,maxe=1e4+1e2;
const double inf = 0x3f3f3f3f;
const double eps = 1e-8;

double e[maxe][maxn],d[maxe],v[maxn],ret;
int n,m;

inline void pivot(int id,int x) {
    e[id][x] = 1 / e[id][x] , d[id] *= e[id][x];
    for(int i=1;i<=n;i++) if( i != x ) e[id][i] *= e[id][x];
    for(int i=1;i<=m;i++)
        if( i != id && std::fabs(e[i][x]) > eps ) {
            for(int j=1;j<=n;j++) if( j != x ) e[i][j] -= e[id][j] * e[i][x];
            d[i] -= d[id] * e[i][x] , e[i][x] *= -e[id][x];
        }
    for(int i=1;i<=n;i++) if( i != x ) v[i] -= v[x] * e[id][i];
    ret += v[x] * d[id] , v[x] *= -e[id][x];
}

inline double simplex() {
    int x,id;
    while(1) {
        for(x=1;x<=n;x++) if( v[x] > eps ) break;
        if( x > n ) return ret;
        double miv = inf;
        for(int i=1;i<=m;i++) if( e[i][x] > 0 && d[i] / e[i][x] < miv ) miv = d[i] / e[i][x] , id = i;
        if( miv == inf ) return inf;
        pivot(id,x);
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lf",v+i);
    for(int i=1,t,a,b;i<=m;i++) {
        scanf("%d",&t);
        while( t-- ) {
            scanf("%d%d",&a,&b);
            for(int j=a;j<=b;j++) e[i][j] = 1;
        }
        scanf("%lf",d+i);
    }
    printf("%.0lf\n",floor(simplex()+0.5));
    return 0;
}

