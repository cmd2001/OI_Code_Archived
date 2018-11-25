#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
#include<iostream>
using namespace std;
const int maxn=4e2+1e1;
const int inf=0x3f3f3f3f;

int in[maxn][maxn];
int n;

namespace Force {
    int pts[maxn],ans[maxn],sta=-1;
    inline int judge() { // return 0 if it is a ring , 1 if it is a chain .
        for(int i=1;i<n;i++)
            if( !in[pts[i]][pts[i+1]] ) return -1;
        return 1 - in[pts[n]][pts[1]];
    }
    inline void work() {
        for(int i=1;i<=n;i++) pts[i] = i;
        do {
            int t = judge();
            if( t == 0 ) {
                sta = 0 , memcpy(ans+1,pts+1,sizeof(int)*n);
                break;
            } else if( t == 1 && !~sta ) {
                sta = 1 , memcpy(ans+1,pts+1,sizeof(int)*n);
            }
        } while( std::next_permutation(pts+1,pts+1+n) );
        printf("%d\n",sta);
        if( ~sta ) for(int i=1;i<=n;i++) printf("%d%c",ans[i],i!=n?' ':'\n');
    }
}
namespace Exp {
    int dis[maxn][maxn];
    int ans[maxn],cnt,sta=-1,sx,sy;
    inline void gen() {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++) {
                dis[i][j] = -inf;
                if( in[i][j] ) dis[i][j] = 1;
            }
    }
    inline void floyd() {
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++) {
                    if( i == k || j == k ) continue;
                    if( dis[i][j] < dis[i][k] + dis[k][j] ) {
                        dis[i][j] = dis[i][k] + dis[k][j];
                    }
                }
    }
    inline void getans() {
        for(int i=1;i<=n;i++)
            if( dis[i][i] == n ) {
                sta = 0 , sx = i;
                return;
            }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if( dis[i][j] == n - 1 ) {
                    sta = 1 , sx = i;
                    return;
                }
    }
    int t = 0;
    inline void work() {
        gen() , floyd() , getans();
        if( ~sta ) {
            for(int i=1;i<=n;i++) ans[dis[sx][i]%n] = i;
            printf("%d\n",sta);
            for(int i=0;i<n;i++) printf("%d ",ans[i]);
        }
    }
}

int main() {
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&in[i][j]);
    if( n <= 15 ) Force::work();
    else Exp::work();
    fclose(stdout);
    return 0;
}


