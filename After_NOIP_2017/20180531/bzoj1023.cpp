#include<cstdio>
#include<algorithm>
const int maxn=5e4+1e2,maxe=1e5+1e2;

int s[maxn],t[maxe<<1],nxt[maxe<<1];
int fa[maxn],dfn[maxn],low[maxn],rid[maxn],dd;
int f[maxn],ans;

inline void coredge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}

inline void solve(int rt,int pos) {
    static int rng[maxn<<1],cnt;
    static int que[maxn<<1],st,ed;
    cnt = 0 , st = 1 , ed = 0;
    for(int i=pos;i!=fa[rt];i=fa[i]) rng[++cnt] = i , rid[i] = cnt;
    for(int i=cnt+1;i<=cnt<<1;i++) rng[i] = rng[i-cnt];
    for(int i=1;i<=cnt<<1;i++) {
        while( st <= ed && que[st] < i - ( cnt >> 1 ) ) ++st;
        if( st <= ed ) ans = std::max( ans , i - que[st] + f[rng[i]] + f[rng[que[st]]] );
        while( st <= ed && f[rng[que[ed]]] - que[ed] <= f[rng[i]] - i ) --ed;
        que[++ed] = i;
    }
    for(int i=1;i<=cnt;i++) f[rt] = std::max(f[rt],std::min(i,cnt-i)+f[rng[i]]);
}

inline void dfs(int pos) {
    low[pos] = dfn[pos] = ++dd;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        if( !dfn[t[at]] ) {
            fa[t[at]] = pos , dfs(t[at]) , low[pos] = std::min(low[pos],low[t[at]]);
            if( low[t[at]] > dfn[pos] ) ans = std::max(ans,f[pos]+f[t[at]]+1) , f[pos] = std::max(f[pos],f[t[at]]+1);
        } else low[pos] = std::min(low[pos],dfn[t[at]]);
    }
    for(int at=s[pos];at;at=nxt[at]) if( fa[t[at]] != pos && dfn[t[at]] > dfn[pos] ) solve(pos,t[at]);
    ans = std::max(ans,f[pos]);
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,k,a,b;i<=m;i++) {
        scanf("%d%d",&k,&a) , --k;
        while(k--) b = a , scanf("%d",&a) , addedge(a,b);
    }
    dfs(1) , printf("%d\n",ans);
    return 0;
}
