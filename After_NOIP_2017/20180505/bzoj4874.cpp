#include<cstdio>
const int maxn=2e5+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int vise[maxn],visp[maxn];

inline void addedge(int from,int to) {
    static int cnt = 1;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos,int &ret) {
    visp[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) {
        if( !vise[at>>1] ) vise[at>>1] = 1 , ++ret;
        if( !visp[t[at]] ) dfs(t[at],ret);
    }
}

int main() {
    static int n,m,ans;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=n;i++) scanf("%d%d",&a,&b) , addedge(a,b) , addedge(b,a);
    for(int i=1,su;i<=m;i++) if( !visp[i] ) su = 0 , dfs(i,su) , ans += ( su & 1 );
    printf("%d\n",ans);
    return 0;
}
