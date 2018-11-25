#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
const int maxn=2.5e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int s[maxn],t[maxn<<1],nxt[maxn<<1],ew[maxn<<1],cnt;
int dep[maxn],dfn[maxn],fa[maxn][18],in[maxn],tar[maxn],siz,m;
lli w[maxn]; // w[1] = inf .
int stk[maxn],top;
int n;

inline void addedge(int from,int to,int val=0) {
    if( from == to ) return;
    t[++cnt] = to , ew[cnt] = val ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    static int dd;
    dfn[pos] = ++dd;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != *fa[pos] ) {
            *fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 ,
            w[t[at]] = std::min( w[pos] , (lli)ew[at] ) ,
            pre(t[at]);
        }
}
inline void gen() {
    dep[1] = 1 , w[1] = inf , pre(1);
    for(int t=1;t<18;t++)
        for(int i=1;i<=n;i++)
            fa[i][t] = fa[fa[i][t-1]][t-1];
    memset(s,0,sizeof(s)) , cnt = 0;
}

inline int lca(int x,int y) {
    if( dep[x] < dep[y] ) std::swap(x,y); // assert dep[x] >= dep[y] .
    for(int i=17;~i;i--)
        if( dep[x] - ( 1 << i ) >= dep[y] )
            x = fa[x][i];
    if( x == y ) return y;
    for(int i=17;~i;i--)
        if( fa[x][i] != fa[y][i] )
            x = fa[x][i] , y = fa[y][i];
    return *fa[x];
}
inline lli dfs(int pos) {
    lli ret = 0;
    for(int at=s[pos];at;at=nxt[at])
        ret += dfs(t[at]);
    s[pos] = 0;
    if( ret ) ret = std::min( ret , w[pos] );
    else ret = w[pos];
    return ret;
}
inline bool cmp(int x,int y) {
    return dfn[x] < dfn[y];
}
inline lli solve() {
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d",in+i);
    std::sort(in+1,in+1+m,cmp) , tar[siz=1] = in[1] , cnt = 0;
    for(int i=2;i<=m;i++) if( lca(in[i],tar[siz]) != tar[siz] ) tar[++siz] = in[i];
    stk[top=1] = 1;
    for(int i=1,l;i<=siz;i++) {
        l = lca(tar[i],stk[top]);
        while(1) {
            if( dep[stk[top-1]] <= dep[l] ) {
                addedge(l,stk[top--]);
                if( stk[top] != l ) stk[++top] = l;
                break;
            } else addedge(stk[top-1],stk[top]) , top--;
        }
        if( stk[top] != tar[i] ) stk[++top] = tar[i];
    }
    while(top) addedge(stk[top-1],stk[top]) , top--;
    return dfs(1);
}

int main() {
    static int T;
    scanf("%d",&n);
    for(int i=1,a,b,l;i<n;i++) {
        scanf("%d%d%d",&a,&b,&l);
        addedge(a,b,l) , addedge(b,a,l);
    }
    gen();
    scanf("%d",&T);
    while(T--) printf("%lld\n",solve());
    return 0;
}

