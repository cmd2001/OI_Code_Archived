#pragma GCC optimize(3)
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC target("mmx")
#include<cstdio>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e2+1e1;
const int mod = 2013265921;

int in[maxn],n;
struct Node {
    lli exp;
    int way,full;
};
inline lli rev(int base) {
    int tme = mod - 2;
    lli ret = 1 , now = base;
    while( tme ) {
        if( tme & 1 ) ret = ret * now % mod;
        now = now * now % mod;
        tme >>= 1;
    }
    return ret;
}

inline bool empty() {
    for(int i=1;i<=n;i++)
        if( in[i] ) return 0;
    return 1;
}
Node dfs() {
    if( empty() )
        return (Node){0,0,1};
    Node ret = (Node){0,0,0};
    int ways = 0 , full = 0;
    for(int i=1;i<=n;i++)
        if( in[i] )
            for(int j=1;j<=in[i];j++) {
                in[i] -= j;
                ++ways;
                Node nxt = dfs();
                ret.exp += ( 1 - nxt.exp + mod ) % mod , ret.exp %= mod , ret.way += nxt.way , full += nxt.full;
                in[i] += j;
            }
    ret.exp = ret.exp * rev(ways) % mod;
    ret.way = full - ret.way;
    ret.full = full;
    return ret;
}

int main() {
    static int T;
    scanf("%d",&T);
    while( T--) {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",in+i);
        //debug<<"scaned"<<endl;
        Node ans = dfs();
        printf("%lld %d\n",ans.exp,ans.way);
    }
    return 0;
}
