#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC target("avx")
#include<cstdio>
#include<cctype>
typedef signed long long int lli;
typedef unsigned long long int ulli;
using namespace std;
const int maxn=19;

unsigned char lnk[maxn][maxn];
unsigned s[maxn],t[maxn<<1],nxt[maxn<<1];
unsigned que[maxn],cnt;
ulli f[maxn][maxn];
unsigned n;

__inline void addedge(unsigned from,unsigned to) {
    static unsigned cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(unsigned pos,const unsigned &fa) {
    for(register unsigned i=1;i<=cnt;i++) f[pos][i] = 1;
    for(register unsigned at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
        dfs(t[at],pos);
        for(register unsigned i=1;i<=cnt;i++) {
            ulli mul = 1;
            for(register unsigned j=1;j<=cnt;j++) if( lnk[que[i]][que[j]] ) mul += f[t[at]][j];
            f[pos][i] *= mul;
        }
    }
}
__inline void getque(const unsigned &sta) {
    cnt = 0;
    for(register unsigned i=1;i<=n;i++) if( sta & ( 1 << ( i - 1 ) ) ) que[++cnt] = i;
}
__inline ulli calc(const unsigned &sta) {
    ulli ret = 0;
    getque(sta) , dfs(1,0);
    for(register unsigned i=1;i<=cnt;i++) ret += f[1][i];
    return ret;
}
__inline unsigned countbit(unsigned x) {
    int ret = 0;
    #define lowbit(x) (x&-x)
    while(x) ++ret , x -= lowbit(x);
    return ret;
}
__inline int getval(const unsigned &x) {
    return ( ( n - countbit(x) ) & 1 ) ? -1 : 1;
}

__inline unsigned getint() {
    register unsigned ret = 0;
    register unsigned char ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static unsigned m,fs;
    static lli ans;
    fs = 1 << ( n = getint() ) , m = getint();
    for(register unsigned i=1,a,b;i<=m;i++) a = getint() , b = getint() , lnk[a][b] = lnk[b][a] = 1;
    for(register unsigned i=1,a,b;i<n;i++) a = getint() , b = getint() , addedge(a,b) , addedge(b,a);
    for(register unsigned i=1;i<fs;i++) ans += getval(i) * calc(i);
    printf("%lld\n",ans);
    return 0;
}
