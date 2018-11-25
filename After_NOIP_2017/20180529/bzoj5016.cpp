#include<cstdio>
#include<algorithm>
#include<cmath>
typedef long long int lli;
const int maxn=5e4+1e2;

int in[maxn],appl[maxn],appr[maxn],bel[maxn];
lli ans[maxn],cur;
int n,m,l,r,cnt;

struct Node {
    int l,r,id,mul;
    friend bool operator < (const Node &a,const Node &b) {
        return bel[a.l] != bel[b.l] ? bel[a.l] < bel[b.l] : a.r < b.r;
    }
}qs[maxn<<2];

inline void mov(const Node &tar) {
    while( l < tar.l ) ++appl[in[++l]] , cur += appr[in[l]];
    while( tar.l < l ) cur -= appr[in[l]] , --appl[in[l--]];
    while( r < tar.r ) ++appr[in[++r]] , cur += appl[in[r]];
    while( tar.r < r ) cur -= appl[in[r]] , --appr[in[r--]];
}

inline void initblk() {
    const int bs = std::sqrt(n);
    for(int l=1,r,cnt=0;l<=n;l=r+1) {
        r = std::min( n , l + bs - 1 ) , ++cnt;
        for(int i=l;i<=r;i++) bel[i] = cnt;
    }
}

int main() {
    scanf("%d",&n) , initblk();
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    scanf("%d",&m);
    for(int i=1,l,r,ll,rr;i<=m;i++) {
        scanf("%d%d%d%d",&l,&ll,&r,&rr);
        qs[++cnt] = (Node){l-1,r-1,i,1} , qs[++cnt] = (Node){ll,rr,i,1} ,
        qs[++cnt] = (Node){l-1,rr,i,-1} , qs[++cnt] = (Node){ll,r-1,i,-1};
    }
    std::sort(qs+1,qs+1+cnt);
    for(int i=1;i<=cnt;i++) mov(qs[i]) , ans[qs[i].id] += cur * qs[i].mul;
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}
