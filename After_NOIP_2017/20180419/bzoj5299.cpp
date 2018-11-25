#pragma GCC optimize(3)
#include<cstdio>
#include<algorithm>
const unsigned maxn=23,maxs=(1<<20)+3;
const unsigned mod=1e8+7;

struct Point {
    int x,y;
    friend Point operator - (const Point &a,const Point &b) {
        return (Point){a.x-b.x,a.y-b.y};
    }
    friend int operator * (const Point &a,const Point &b) {
        return a.x * b.y - b.x * a.y;
    }
}ps[maxn];

unsigned f[maxs][maxn],ban[maxn][maxn]; // ban[i][j] is statement of Point in way i to j .
unsigned bin[maxn],n,full,ans;

inline void add(unsigned& x,unsigned y) {
    x += y;
    if( x >= mod ) x -= mod;
}
inline bool crs(const Point &from,const Point &mid,const Point &to) {
    return std::min(from.x,to.x) <= mid.x && mid.x <= std::max(from.x,to.x) && std::min(from.y,to.y) <= mid.y && mid.y <= std::max(from.y,to.y) && ! ( ( mid - from ) * ( to - mid ) );
}
inline bool can(unsigned from,unsigned to,unsigned used) {
    return ( ban[from][to] & used ) == ban[from][to];
}
inline unsigned cntbit(unsigned x) {
    unsigned ret = 0;
    while(x) ++ret , x -= (x&-x);
    return ret;
}

int main() {
    scanf("%u",&n) , full = 1 << n , bin[0] = 1;
    for(unsigned i=1;i<=n;i++) scanf("%d%d",&ps[i].x,&ps[i].y) , bin[i] = bin[i-1] << 1;
    for(unsigned i=1;i<=n;i++) for(unsigned j=1;j<=n;j++) if( i != j ) for(unsigned k=1;k<=n;k++) if( i != k && k != j && crs(ps[i],ps[k],ps[j]) ) ban[i][j] |= bin[k-1];
    for(unsigned i=1;i<=n;i++) f[bin[i-1]][i] = 1;
    for(unsigned sta=1,upd;sta<full;sta++) {
        upd = cntbit(sta) >= 4;
        for(unsigned cur=1;cur<=n;cur++) if( f[sta][cur] ) {
            if( upd ) add(ans,f[sta][cur]);
            for(unsigned tar=1;tar<=n;tar++) if( ( ! ( sta & bin[tar-1] ) ) && can(cur,tar,sta) ) add(f[sta|bin[tar-1]][tar] , f[sta][cur] );
        }
    }
    printf("%u\n",ans);
    return 0;
}
