#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int on_ring[maxn],ring_nxt[maxn],vis[maxn];
int ring[maxn*3],ringlen;
lli l[maxn<<1],dis_nxt[maxn],dis_sum[maxn*3],ring_f[maxn*3],mx;

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline bool findring(int pos,int fa) {
    if( vis[pos] ) return ring_nxt[pos] = fa , on_ring[pos] = 1 , ring[++ringlen] = pos;
    vis[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) {
        if( t[at] != fa && findring(t[at],pos) ) {
            if( !on_ring[pos] ) return ring_nxt[pos] = fa , on_ring[pos] = 1 , ring[++ringlen] = pos;
            else return vis[pos] = 1 , 0;
        }
    }
    return vis[pos] = 0 , 0;
}
inline void complete_ring() { // only ring[ringlen] hasn't got nxt .
    ring_nxt[ring[ringlen]] = ring[1];
    for(int i=1;i<=ringlen;i++) for(int at=s[ring[i]];at;at=nxt[at]) if( t[at] == ring_nxt[ring[i]] ) { dis_nxt[i] = l[at]; break; }
    for(int i=1;i<=ringlen;i++) ring[i+ringlen] = ring[i+ringlen*2] = ring[i] , dis_sum[i+1] = dis_sum[i+ringlen+1] = dis_sum[i+ringlen*2+1] = dis_nxt[i];
    for(int i=1;i<=ringlen*3;i++) dis_sum[i] += dis_sum[i-1];
}
inline lli ring_dis(int i,int j) { // assert j >= i .
    lli adis = dis_sum[j] - dis_sum[i];
    #define bel(x) (x<=ringlen?(ringlen+1):x<=2*ringlen?(2*ringlen+1):(3*ringlen+1))
    lli bdis = dis_sum[i] + dis_sum[bel(i)] - dis_sum[j];
    return min( adis , bdis );
}
inline lli getf(int i,int j) {
    debug<<"i = "<<i<<"j = "<<j<<"dis = "<<ring_dis(i,j)<<endl;
    return ring_dis(i,j) + ring_f[i] + ring_f[j];
}
inline lli dfs(int pos,int fa) {
    lli ret = 0 , fs;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !on_ring[t[at]] ) fs = dfs(t[at],pos) + l[at] , mx = max( mx , fs + ret ) , ret = max( ret , fs );
    return ret;
}
inline void getans() {
    for(int i=1,j=1;i<=ringlen;i++) {
        while( getf(i,j+1) > getf(i,j) ) ++j;
        mx = max( mx , getf(i,j) );
    }
}

int main() {
    static int n;
    scanf("%d",&n);
    debug<<"n = "<<n<<endl;
    for(int i=1,a,b,l;i<=n;i++) debug<<"i = "<<i<<endl,scanf("%d%d%d",&a,&b,&l) , addedge(a,b,l) , addedge(b,a,l);
    //debug<<"readed"<<endl;
    findring(1,-1) , complete_ring();
    debug<<"ring_len = "<<ringlen<<endl;
    for(int i=1;i<=ringlen;i++) debug<<ring[i]<<" "; debug<<endl;
    for(int i=1;i<=ringlen;i++) debug<<dis_nxt[i]<<" "; debug<<endl;
    for(int i=1;i<=ringlen;i++) ring_f[i] = ring_f[i+ringlen] = ring_f[i+ringlen*2] = dfs(ring[i],-1);
    for(int i=1;i<=ringlen;i++) debug<<ring_f[i]<<" "; debug<<endl;
    for(int i=1;i<=ringlen*3;i++) debug<<dis_sum[i]<<" "; debug<<endl;
    getans() , printf("%lld\n",mx);
    return 0;
}
