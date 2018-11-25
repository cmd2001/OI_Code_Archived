#include<cstdio>
const int maxn=1e6+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],siz[maxn],sum[maxn];

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos,int fa) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) dfs(t[at],pos) , siz[pos] += siz[t[at]];
}

int main() {
    static int n,ans;
    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b) , addedge(b,a);
    dfs(1,-1); for(int i=1;i<=n;i++) ++sum[siz[i]];
    for(int i=1;i<=n;i++) if( ! ( n % i ) ) {
        int su = 0;
        for(int j=i;j<=n;j+=i) su += sum[j];
        ans += ( su == n / i );
    }
    printf("%d\n",ans);
    return 0;
}