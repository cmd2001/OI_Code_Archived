#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxx=1e3+1e2,maxe=5e3+1e2,maxl=3e2+1e1;
const double eps=1e-8;

int n,m,ee,xx;
double ans;
namespace Simplex {
    double e[maxx][maxe],d[maxx],v[maxe],ret; // less equation .
    const double inf=0x3f3f3f3f;
    inline void pivot(int id,int x) {
        e[id][x] = 1 / e[id][x] , d[id] *= e[id][x];
        for(int i=1;i<=xx;i++) if( i != x ) e[id][i] *= e[id][x];
        for(int i=1;i<=ee;i++) if( i != id && fabs(e[i][x]) > eps ) {
            for(int j=1;j<=xx;j++) if( j != x ) e[i][j] -= e[i][x] * e[id][j];
            d[i] -= d[id] * e[i][x] , e[i][x] *= -e[id][x];
        }
        for(int i=1;i<=xx;i++) if( i != x ) v[i] -= v[x] * e[id][i];
        ret += v[x] * d[id] , v[x] *= -e[id][x];
    }
    inline double simplex() {
        int id,x;
        while(1) {
            for(x=1;x<=xx;x++) if( v[x] > 0 ) break;
            if( x > xx ) return ret;
            double miv = inf;
            for(int i=1;i<=ee;i++) if( e[i][x] > 0 && miv > d[i] / e[i][x] ) miv = d[i] / e[i][x] , id = i;
            if( miv == inf ) return inf;
            pivot(id,x);
        }
    }
    
}

namespace Build {
    int u[maxx],v[maxx],w[maxx],a[maxx],b[maxx],tpe[maxx];
    int can[maxl][maxl],ts[maxx],cnt;
    
    inline void readin() {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++) {
            scanf("%d%d%d%d%d%d",u+i,v+i,w+i,tpe+i,a+i,b+i);
            if( tpe[i] ) can[u[i]][v[i]] = can[v[i]][u[i]] = i;
        }
    }
    inline bool dfs(int pos,int fa,int tar) {
        if( pos == tar ) return 1;
        for(int i=1;i<=n;i++)
            if( can[pos][i] && i != fa ) {
                if( dfs(i,pos,tar) ) {
                    ts[++cnt] = can[pos][i];
                    return 1;
                }
            }
        return 0;
    }
    inline void genedge(int id) {
        cnt = 0;
        dfs(u[id],-1,v[id]);
        for(int i=1;i<=cnt;i++) if( w[ts[i]] > w[id] ) {
            ++xx;
            using Simplex::e; using Simplex::v;
            e[ts[i]][xx] = e[id][xx] = 1;
            v[xx] = w[ts[i]] - w[id];
        }
    }
    inline void gen() {
        using Simplex::d;
        for(int i=1;i<=m;i++) {
            if( !tpe[i] ) {
                genedge(i);
                d[i] = a[i];
            } else d[i] = b[i];
        }
        ee = m;
    }
}

int main() {
    Build::readin();
    Build::gen();
    ans = Simplex::simplex();
    printf("%.0lf\n",floor(ans+0.5));
    return 0;
}

