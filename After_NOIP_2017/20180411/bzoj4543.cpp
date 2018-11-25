#include<cstdio>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],dep[maxn],mxd[maxn],son[maxn],siz[maxn];
lli *f[maxn],*g[maxn],ans;

inline lli* NewArray(int siz) {
    static lli pool[maxn<<4],*st=pool;
    lli* ret = st; st += siz;
    return ret;
}

inline void coredge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}

inline void pre(int pos,int fa) { // assert dep[1] = 1 .
    mxd[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
        dep[t[at]] = dep[pos] + 1 , pre(t[at],pos) , mxd[pos] = max( mxd[pos] , mxd[t[at]] + 1 );
        if( mxd[t[at]] > mxd[son[pos]] ) son[pos] = t[at];
    }
}
inline void getsiz(int pos,int fa) {
    siz[pos] = pos == son[fa] ? siz[fa] + 1 : 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) getsiz(t[at],pos);
    if( !son[pos] ) {
        f[pos] = NewArray(siz[pos]) + siz[pos] - 1 ,
        g[pos] = NewArray(siz[pos]*2);
    }
}
inline void dfs(int pos,int fa) {
    if( son[pos] ) dfs(son[pos],pos) , f[pos] = f[son[pos]] - 1 , g[pos] = g[son[pos]] + 1;
    ++f[pos][0] , ans += g[pos][0];
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && t[at] != son[pos] ) {
        dfs(t[at],pos);
        for(int i=0;i<mxd[t[at]];i++) {
            ans += f[t[at]][i] * g[pos][i+1];
            if( i ) ans += f[pos][i-1] * g[t[at]][i];
        }
        for(int i=0;i<mxd[t[at]];i++) {
            g[pos][i+1] += f[t[at]][i] * f[pos][i+1] , f[pos][i+1] += f[t[at]][i];
            if( i ) g[pos][i-1] += g[t[at]][i];
        }
    }
}

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b);
    pre(1,0) , getsiz(1,0) , dfs(1,0);
    printf("%lld\n",ans);
    return 0;
}
