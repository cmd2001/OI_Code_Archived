#include<cstdio>
#include<cstring>
typedef long long int lli;
const int maxn=1e5+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],mrk[maxn];
bool vis[maxn],fail;
int cnt[3],ecnt;

inline void addedge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos,int col) {
    static const int ne[]={1,2,0},pr[]={2,0,1};
    if( vis[pos] ) return void(fail |= col != mrk[pos]);
    vis[pos] = 1 , ++cnt[mrk[pos]=col];
    for(int at=s[pos];at;at=nxt[at]) ++ecnt , dfs(t[at],(at&1)?ne[col]:pr[col]);
}

int main() {
    static int n,m;
    static lli ans;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , addedge(a,b) , addedge(b,a);
    for(int i=1;i<=n;i++) if( !vis[i] ) {
        memset(cnt,0,sizeof(cnt)) , ecnt = fail = 0 , dfs(i,0);
        if(fail) ans += (lli) ( cnt[0] + cnt[1] + cnt[2] ) * ( cnt[0] + cnt[1] + cnt[2] );
        else if( !cnt[0] || !cnt[1] || !cnt[2] ) ans += ecnt >> 1;
        else ans += (lli) cnt[0] * cnt[1] + (lli) cnt[1] * cnt[2] + (lli) cnt[2] * cnt[0];
    }
    printf("%lld\n",ans);
    return 0;
}
