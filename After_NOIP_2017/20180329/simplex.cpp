
// public define .
const int maxe=1e3+1e2,maxn=1e4+1e2;
double e[maxe][maxn],d[maxe],v[maxn];
int n,m;

// new code .
inline void pivot(int id,int x) {
    e[id][x] = 1 / e[id][x] , d[id] *= e[id][x];
    for(int i=1;i<=m;i++) if( i != x ) e[id][i] *= e[id][x];
    for(int i=1;i<=n;i++)
        if( i != id && fabs(e[i][x]) > eps ) {
            for(int j=1;j<=m;j++) if( j != x ) e[i][j] -= e[id][j] * e[i][x];
            d[i] -= d[id] * e[i][x] , e[i][x] *= -e[id][x];
        }
    for(int i=1;i<=m;i++) if( i != x ) v[i] -= v[x] * e[id][i];
    ret += v[x] * e[id] , v[x] *= -e[id][x];
}
inline double simplex() {
    int x,id;
    while(1) {
        for(x=1;x<=m;x++) if( v[x] > eps ) break;
        if( x > m ) return ret;
        double miv = inf;
        for(int i=1;i<=n;i++) if( e[i][x] > 0 && d[i] / e[i][x] < miv ) miv = d[i] / e[i][x] , id = i;
        if( miv == inf ) return inf;
        pivot(id,x);
    }
}

// old code .
inline void pivot(int id,int x) {
    e[id][x] = 1 / e[id][x] , d[id] *= e[id][x];
    for(int i=1;i<=m;i++) if( i != x ) e[id][i] *= e[id][x];
    for(int i=1;i<=n;i++)
        if( i != id && std::fabs(e[i][x]) > eps ) {
            for(int j=1;j<=m;j++) if( j != x ) e[i][j] -= e[id][j] * e[i][x];
            d[i] -= d[id] * e[i][x] , e[i][x] *= -e[id][x];
        }
    for(int i=1;i<=m;i++) if( i != x ) v[i] -= v[x] * e[id][i];
    ret += v[x] * d[id] , v[x] *= -e[id][x];
}
inline double simplex() {
    int x,id;
    while(1) {
        for(x=1;x<=m;x++) if( v[x] > eps ) break;
        if( x > m ) return ret;
        double miv = inf;
        for(int i=1;i<=n;i++) if( e[i][x] > 0 && d[i] / e[i][x] < miv ) miv = d[i] / e[i][x] , id = i;
        if( miv == inf ) return inf;
        pivot(id,x);
    }
}