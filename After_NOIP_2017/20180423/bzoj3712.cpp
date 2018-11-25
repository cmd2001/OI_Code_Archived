#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=1e6+1e2;

int in[maxn],id[maxn],used[maxn];
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int dep[maxn],fa[maxn],siz[maxn],son[maxn],top[maxn];

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) {
            fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 , pre(t[at]) ,
            siz[pos] += siz[t[at]] , son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
        }
}
inline void dfs(int pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) dfs(t[at]);
}
inline int lca(int x,int y) {
    while( top[x] != top[y] ) {
        if( dep[top[x]] < dep[top[y]] ) std::swap(x,y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

struct Node {
    int dl,id,a,b;
    friend bool operator < (const Node &a,const Node &b) {
        return a.dl != b.dl ? a.dl > b.dl : a.id < b.id;
    }
}ns[maxn];

int main() {
    static int n,m,k,cnt;
    static lli ans;
    scanf("%d%d%d",&n,&m,&k) , cnt = n;
    for(int i=1;i<=n;i++) scanf("%d",in+i) , id[i] = i;
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d",&a,&b) , ++cnt , used[a] = 1;
        addedge(cnt,id[a]) , addedge(cnt,id[b]) , id[b] = cnt;
    }
    for(int i=1;i<=n;i++) if( !used[i] ) addedge(0,id[i]);
    pre(0) , dfs(0);
    for(int i=1,a,b,l;i<=k;i++) {
        scanf("%d%d",&a,&b) , l = lca(a,b);
        ns[i] = (Node){dep[l],i,a,b};
    }
    std::sort(ns+1,ns+1+k);
    for(int i=1,add;i<=k;i++) if( ns[i].dl ) ans += ( ( add = std::min( in[ns[i].a] , in[ns[i].b] ) ) << 1 ) , in[ns[i].a] -= add , in[ns[i].b] -= add;// , debug<<"a = "<<ns[i].a<<"b = "<<ns[i].b<<endl;
    printf("%lld\n",ans);
    return 0;
}

