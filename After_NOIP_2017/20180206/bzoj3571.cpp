#include<cstdio>
#include<cstring>
#include<algorithm>
#define bool unsigned char
using namespace std;
const int maxn=1e2+1e1;
const int inf=0x3f3f3f3f;

int inx[maxn][maxn],iny[maxn][maxn],ans=inf;
int n;

struct Node {
    int x,y;
    Node() {
        x = y = 0;
    }
    friend bool operator == (const Node &a,const Node &b) {
        return a.x == b.x && a.y == b.y;
    }
    inline void update() {
        ans = min( ans , x * y );
    }
    inline void print() {
        printf("%d %d\n",x,y);
    }
}ls,rs;
namespace KM {
    int g[maxn][maxn];
    int vara[maxn],varb[maxn],lnk[maxn],tp;
    bool visa[maxn],visb[maxn];
    
    inline bool dfs(int pos) {
        visa[pos] = 1;
        for(int i=1;i<=n;i++)
            if( !visb[i] ) {
                if( vara[pos] + varb[i] == g[pos][i] ) {
                    visb[i] = 1;
                    if( !lnk[i] || dfs(lnk[i]) ) {
                        lnk[i] = pos;
                        return 1;
                    }
                } else tp = min( tp , vara[pos] + varb[i] - g[pos][i] );
            }
        return 0;
    }
    inline Node pir() {
        for(int i=1;i<=n;i++) {
            while(1) {
                memset(visa,0,sizeof(visa)) , memset(visb,0,sizeof(visb)) , tp = inf;
                if( dfs(i) ) break;
                for(int i=1;i<=n;i++) {
                    if( visa[i] ) vara[i] -= tp;
                    if( visb[i] ) varb[i] += tp;
                }
            }
        }
        Node ret;
        for(int i=1;i<=n;i++)
            ret.x += inx[lnk[i]][i] , ret.y += iny[lnk[i]][i];
        return ret;
    }
    inline void rebuild(int mx,int my) {
        for(int i=1;i<=n;i++) vara[i] = -inf;
        memset(varb,0,sizeof(varb));
        memset(lnk,0,sizeof(lnk));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++) {
                g[i][j] = inx[i][j] * mx + iny[i][j] * my;
                vara[i] = max( vara[i] , g[i][j] );
            }
    }
}

inline void solve(Node l,Node r) {
    l.update() , r.update();
    KM::rebuild(r.y-l.y,l.x-r.x);
    Node mid = KM::pir();
    if( mid == l || mid == r ) return;
    solve(l,mid) , solve(mid,r);
}

int main() {
    static int T;
    scanf("%d",&T);
    while( T-- ) {
        scanf("%d",&n) , ans = inf;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",inx[i]+j);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",iny[i]+j);
        KM::rebuild(-1,0) , ls = KM::pir();
        KM::rebuild(0,-1) , rs = KM::pir();
        solve(ls,rs);
        printf("%d\n",ans);
    }
    return 0;
}
