#include<cstdio>
#include<algorithm>
#include<cstring>
const int maxn=5e2+1e1;

int s[maxn],t[maxn<<2],nxt[maxn<<2],cnt;
int bel[maxn],bsiz[maxn],bcnt,ban;
bool iscut[maxn],vis[maxn];

inline void coredge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] ,  s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}
inline void pre(int pos) {
    vis[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( !vis[t[at]] && t[at] != ban ) pre(t[at]);
}
inline void dfs(int pos) {
    vis[pos] = 1;
    if( bel[pos] ) bel[pos] = -1;
    else bel[pos] = bcnt;
    for(int at=s[pos];at;at=nxt[at]) if( !vis[t[at]] && !iscut[t[at]] ) dfs(t[at]);
}

inline void reset() {
    memset(bel,0,sizeof(bel)) , memset(bsiz,0,sizeof(bsiz)) , memset(iscut,0,sizeof(iscut));
    memset(s,0,sizeof(s)) , bcnt = ban = cnt = 0;
}

int main() {
    static int n,m,ned,T;
    unsigned long long way;
    while( scanf("%d",&m) == 1 && m ) {
        reset() , n = ned = 0 , way = 1;
        for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , n = std::max(n,std::max(a,b)) , addedge(a,b);
        for(int i=1;i<=n;i++) {
            memset(vis,0,sizeof(vis)) , ban = i;
            pre(1+(i==1));
            for(int j=1;j<=n;j++) if( i != j && !vis[j] ) { iscut[i] = 1; break; }
        }
        for(int i=1;i<=n;i++) if( iscut[i] ) {
            memset(vis,0,sizeof(vis));
            for(int at=s[i];at;at=nxt[at]) if( !vis[t[at]] && !iscut[t[at]] ) {
                ++bcnt , dfs(t[at]);
            }
        }
        for(int i=1;i<=n;i++) if( ~bel[i] ) ++bsiz[bel[i]];
        for(int i=1;i<=bcnt;i++) if( bsiz[i] ) ++ned , way *= bsiz[i];
        printf("Case %d: ",++T);
        if( !ned ) printf("%d %d\n",2,n*(n-1)>>1);
        else printf("%d %llu\n",ned,way);
    }
    return 0;
}
