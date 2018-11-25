#include<cstdio>
#include<algorithm>
#include<cmath>
typedef long long int lli;
const int maxn=1e5+1e2,maxe=3e5+1e2;

int in[maxn],bel[maxn],sul[maxe],sur[maxe],l,r,n,m,k;
lli now,ans[maxn];

struct Query {
    int l,r,id;
    friend bool operator < (const Query &a,const Query &b) {
        return bel[a.l] != bel[b.l] ? bel[a.l] < bel[b.l] : a.r < b.r;
    }
}qs[maxn];

inline void move(const int &tarl,const int &tarr) {
    while( r < tarr ) ++r , ++sul[in[r-1]] , ++sur[in[r]] , now += sul[in[r]^k];
    while( tarl < l ) --l , ++sul[in[l-1]] , ++sur[in[l]] , now += sur[in[l-1]^k];
    while( tarr < r ) --r , now -= sul[in[r+1]^k] , --sul[in[r]] , --sur[in[r+1]];
    while( l < tarl ) ++l , now -= sur[in[l-2]^k] , --sul[in[l-2]] , --sur[in[l-1]];
}

inline void getans() {
    std::sort(qs+1,qs+1+m) , sul[in[0]] = 1 , sur[in[1]] = 1 , l = r = 1 , now = in[1] == k;
    for(int i=1;i<=m;i++) move(qs[i].l,qs[i].r) , ans[qs[i].id] = now;
}

inline void init() {
    const int blk = std::sqrt(n);
    for(int l=1,r,cnt=0;l<=n;l=r+1) r = std::min( l + blk - 1 , n ) , std::fill(bel+l,bel+r+1,++cnt);
}

int main() {
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , in[i] ^= in[i-1];
    for(int i=1;i<=m;i++) scanf("%d%d",&qs[i].l,&qs[i].r) , qs[i].id = i;
    init() , getans();
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}

