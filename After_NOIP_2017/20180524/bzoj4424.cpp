#include<cstdio>
#include<cctype>
const int maxn=1e6+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int dep[maxn],vis[maxn],tpe[maxn<<1],f[maxn],g[maxn]; // f means odd ring , g means even ring .
int ans[maxn],anslen,n,m,top,orcnt;

inline void coredge(int from,int to) {
    static int cnt = 1;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}
inline void dfs(int pos,int edg) {
    vis[pos] = 1 , dep[pos] = ++top;
    for(int at=s[pos];at;at=nxt[at]) {
        if( !~tpe[at] ) continue; // a returning tree edge .
        else if( !vis[t[at]] ) tpe[at] = tpe[at^1] = -1 , dfs(t[at],at>>1) , f[edg] += f[at>>1] , g[edg] += g[at>>1];
        else {
            if( tpe[at] == 1 ) --f[edg];
            else if( tpe[at] == 2 ) --g[edg];
            else {
                if( ( dep[pos] - dep[t[at]] ) & 1 ) tpe[at] = tpe[at^1] = 2 , ++g[edg];
                else tpe[at] = tpe[at^1] = 1 , ++f[edg] , ++orcnt;
            }
        }
    }
    --top;
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint();
    for(int i=1;i<=m;i++) addedge(getint(),getint());
    for(int i=1;i<=n;i++) if( !vis[i] ) dfs(i,0);
    if( !orcnt ) {
        anslen = m;
        for(int i=1;i<=m;i++) ans[i] = i;
    } else {
        for(int i=1;i<=m;i++) {
            if( f[i] == orcnt && !g[i] ) ans[++anslen] = i;
            else if( orcnt == 1 && tpe[i<<1] == 1 ) ans[++anslen] = i;
        }
    }
    printf("%d\n",anslen);
    for(int i=1;i<=anslen;i++) printf("%d%c",ans[i],i!=anslen?' ':'\n');
    return 0;
}
