#include<cstdio>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
lli l[maxn<<1],dis_nxt[maxn],dis_sum[maxn],f[maxn],mx,mi,ans;
lli suf[maxn],prf[maxn],ssuf[maxn],pprf[maxn];
int ring[maxn],ring_nxt[maxn],rlen,n;
bool on[maxn],vis[maxn];

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline bool findring(int pos,int fa) {
    if( vis[pos] ) return on[ring[++rlen]=pos] = 1;
    vis[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
        if( findring(t[at],pos) ) {
            if( !on[pos] ) return ring_nxt[t[at]] = pos , on[ring[++rlen]=pos] = 1;
            else return 0;
        }
    }
    return vis[pos] = 0;
}
inline void prering() {
    ring_nxt[ring[rlen]] = ring[1];
    for(int i=1;i<=rlen;i++) for(int at=s[ring[i]];at;at=nxt[at]) if( t[at] == ring_nxt[ring[i]] ) { dis_nxt[i] = l[at]; break; }
    for(int i=1;i<=rlen;i++) dis_sum[i+1] = dis_nxt[i];
    for(int i=1;i<=rlen+1;i++) dis_sum[i] += dis_sum[i-1];
}
inline lli dfs(int pos,int fa) {
    lli ret = 0 , fs;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !on[t[at]] ) fs = dfs(t[at],pos) + l[at] , mx = max( mx , ret + fs ) , ret = max( ret , fs );
    return ret;
}
inline void dp() {
    for(int i=1;i<=rlen;i++) f[i] = dfs(ring[i],-1);
    for(int i=1;i<=rlen;i++) prf[i] = max( prf[i-1] , dis_sum[i] + f[i] );
    for(int i=rlen;i>=1;i--) suf[i] = max( suf[i+1] , dis_sum[rlen] - dis_sum[i] + f[i] );
    for(int i=1,sel=0;i<=rlen;i++) {
        pprf[i] = max( pprf[i-1] , dis_sum[i] + f[i] - dis_sum[sel] + f[sel] );
        if( f[i] - dis_sum[i] >= f[sel] - dis_sum[sel] ) sel = i;
    }
    for(int i=rlen,sel=rlen;i>=0;i--) {
        ssuf[i] = max( ssuf[i+1] , dis_sum[sel] + f[sel] - dis_sum[i] + f[i] );
        if( dis_sum[i] + f[i] >= dis_sum[sel] + f[sel] ) sel = i;
    }
    mi = inf;
    for(int i=1;i<=rlen;i++) mi = min( mi , max( suf[i+1] + dis_nxt[rlen] + prf[i] , max( pprf[i] , ssuf[i+1] ) ) );
    ans = max( mx , mi );
}

int main() {
    scanf("%d",&n);
    for(int i=1,a,b,l;i<=n;i++) scanf("%d%d%d",&a,&b,&l) , addedge(a,b,l) , addedge(b,a,l);
    findring(1,-1) , prering() , dp() , printf("%lld.%lld\n",ans>>1,(ans&1)*5);
    return 0;
}
