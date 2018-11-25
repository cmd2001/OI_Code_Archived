#include<cstdio>
#include<algorithm>
#include<bitset>
#include<cmath>
typedef long long int lli;
const int maxn=2.5e5+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int siz[maxn],mxs[maxn],root;
int tim[maxn],n,sq;
lli ans,su;
std::bitset<maxn> f;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos,int fa) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) pre(t[at],pos) , mxs[pos] = std::max( mxs[pos] , siz[t[at]] ) , siz[pos] += siz[t[at]];
    if( ( mxs[pos] = std::max( mxs[pos] , n - siz[pos] ) ) < mxs[root] ) root = pos;
}
inline void dfs(int pos,int fa) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) dfs(t[at],pos) , siz[pos] += siz[t[at]];
    su += siz[pos] - 1;
}
inline void getans(int cent) {
    dfs(cent,-1) , f[0] = 1;
    for(int at=s[cent];at;at=nxt[at]) {
        if( siz[t[at]] > sq ) f |= f << siz[t[at]];
        else ++tim[siz[t[at]]];
    }
    for(int i=1;i<=sq;i++) if( tim[i] ) {
        for(int t=1;t<=tim[i];t<<=1) f |= f << t * i , tim[i] -= t;
        if(tim[i]) f |= f << i * tim[i];
    }
    for(int i=0;i<n;i++) if( f[i] ) ans = std::max( ans , (lli) i * ( n - i - 1 ) );
    ans += su;
}

int main() {
    scanf("%d",&n) , sq = std::sqrt(n) , *mxs = inf;
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b) , addedge(b,a);
    pre(1,-1) , getans(root);
    printf("%d %lld\n",n-1,ans);
    return 0;
}