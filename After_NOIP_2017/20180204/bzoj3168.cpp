#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define bool unsigned char
#define debug cout
using namespace std;
const int maxn=3e2+1e1;

int n;

namespace FindWay {
    const int mod = 1e9 + 7;
    inline lli fastpow(lli base,int tim,int mod) {
        lli ret = 1;
        while( tim ) {
            if( tim & 1 ) ret = ret * base % mod;
            if( tim >>= 1 ) base = base * base % mod;
        }
        return ret;
    }
    struct Matrix {
        lli dat[maxn][maxn];
        Matrix(int tpe=0) {
            memset(dat,0,sizeof(dat));
            if( tpe ) {
                for(int i=1;i<=n;i++)
                    dat[i][i] = 1;
            }
        }
        lli* operator [] (const int id) {
            return dat[id];
        }
        inline Matrix getinv() {
            Matrix ret(1);
            for(int i=1;i<=n;i++) {
                int pos = -1;
                for(int j=i;j<=n&&!~pos;j++)
                    if( dat[j][i] ) pos = j;
                if( !~pos ) {
                    //debug<<"There is no way to find a inv matrix !"<<endl;
                    //exit(0);
                    puts("NIE");
                    exit(0);
                }
                if( pos != i ) {
                    for(int j=1;j<=n;j++) {
                        swap( dat[i][j] , dat[pos][j] );
                        swap( ret[i][j] , ret[pos][j] );
                    }
                    pos = i;
                }
                const lli inv = fastpow( dat[i][i] , mod - 2 , mod );
                for(int j=1;j<=n;j++) {
                    dat[i][j] = dat[i][j] * inv % mod ,
                    ret[i][j] = ret[i][j] * inv % mod ;
                }
                for(int j=1;j<=n;j++)
                    if( j != i && dat[j][i] ) {
                        const lli mul = dat[j][i];
                        for(int k=1;k<=n;k++) {
                            dat[j][k] = ( dat[j][k] - dat[i][k] * mul % mod + mod ) % mod ,
                            ret[j][k] = ( ret[j][k] - ret[i][k] * mul % mod + mod ) % mod ;
                        }
                    }
            }
            return ret;
        }
        friend Matrix operator * (const Matrix &a,const Matrix &b) {
            Matrix ret;
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    for(int k=1;k<=n;k++)
                        ret[i][j] += a.dat[i][k] * b.dat[k][j] % mod ,
                        ret[i][j] %= mod;
            return ret;
        }
        inline void read() {
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    scanf("%lld",dat[i]+j);
        }
    }od,nw;
    inline void work() {
        nw = nw * od.getinv();
    }
}
namespace BinaryGraph {
    int fa[maxn],pir[maxn];
    bool can[maxn][maxn],vis[maxn];
    inline bool dfs1(int pos) {
        for(int i=1;i<=n;i++)
            if( can[pos][i] && !vis[i] ) {
                //debug<<"i = "<<i<<endl;
                vis[i] = 1;
                if( !fa[i] || dfs1(fa[i]) ) {
                    //debug<<"i = "<<i<<endl;
                    fa[i] = pos;
                    return 1;
                }
            }
        return 0;
    }
    inline bool dfs2(int pos,int st,bool mrk) {
        if( mrk && pos == st ) return 1;
        for(int i=1;i<=n;i++)
            if( can[pos][i] && !vis[i] ) {
                vis[i] = 1;
                if( dfs2(fa[i],st,1) ) {
                    fa[i] = pos , pir[pos] = i;
                    return 1;
                }
            }
        return 0;
    }
    inline bool judge() {
        int ret = 0;
        for(int i=1;i<=n;i++) {
            memset(vis,0,sizeof(vis));
            ret += dfs1(i);
        }
        return ret == n;
    }
    inline void getans() {
        for(int i=1;i<=n;i++) {
            pir[fa[i]] = i;
            //if( !fa[i] ) debug<<"!fa[i] i = "<<i<<endl,exit(0);
        }
        for(int i=1;i<=n;i++) {
            memset(vis,0,sizeof(vis));
            dfs2(i,i,0);
            for(int j=1;j<=n;j++)
                can[j][pir[i]] = 0;
        }
    }
}

inline void Trans() {
    using BinaryGraph::can;
    using FindWay::nw;
    /*for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) debug<<nw[i][j]<<" ";debug<<endl;
    }*/
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            can[i][j] = nw[i][j] ? 1 : 0;
}

int main() {
    scanf("%d",&n);
    FindWay::od.read() , FindWay::nw.read();
    FindWay::work();
    Trans();
    if( ! BinaryGraph::judge() ) return puts("NIE"),0;
    puts("TAK");
    BinaryGraph::getans();
    for(int i=1;i<=n;i++)
        printf("%d\n",BinaryGraph::fa[i]);
    return 0;
}


