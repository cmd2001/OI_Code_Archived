#pragma GCC optimize(3)
#include<cstdio>
#include<algorithm>
const int maxn=6e2+1e1,maxe=2e4+1e2;

struct Point {
    int x,y;
    friend Point operator - (const Point &a,const Point &b) {
        return (Point){a.x-b.x,a.y-b.y};
    }
    friend int operator * (const Point &a,const Point &b) {
        return a.x * b.y - a.y * b.x;
    }
}ps[maxn],ss[maxe],now;

unsigned char can[maxn][maxn];
unsigned f[maxn][maxn],nxt[maxn];
int n,m,mod;

inline bool cmp(const Point &a,const Point &b) {
    return ( b - now ) * ( a - now ) > 0;
}

inline void pre() {
    now = ps[1] , std::sort(ps+2,ps+1+n,cmp);
    for(int i=1,k;i<=n;i++) {
        now = ps[i] , std::sort(ss+1,ss+1+m,cmp) , k = 1;
        for(int j=nxt[i];j!=i;j=nxt[j]) {
            while( k <= m && ( ss[k] - now ) * ( ps[j] - now ) < 0 ) ++k;
            if( ( k & 1 ) && ! ( k <= m && ! ( ( ss[k] - now ) * ( ps[j] - now ) ) ) ) can[i][j] = 1;
        }
    }
}
inline void getans() {
    for(int i=1;i<=n;i++) f[i][nxt[i]] = 1;
    for(int len=2;len<=n;len++) {
        for(int st=1;st+len<=n;st++) {
            const int ed = st + len <= n ? st + len : st + len - 1 - n ;
            for(int k=nxt[st];k!=ed;k=nxt[k]) if( can[st][k] & can[k][ed] ) ( f[st][ed] += f[st][k] * f[k][ed] % mod ) %= mod;
        }
    }
}

int main() {
    scanf("%d%d%d",&n,&m,&mod);
    for(int i=1;i<=n;i++) nxt[i] = i == n ? 1 : i + 1;
    for(int i=1;i<=n;i++) scanf("%u%u",&ps[i].x,&ps[i].y);
    for(int i=1;i<=m;i++) scanf("%u%u",&ss[i].x,&ss[i].y);
    pre() , getans() , printf("%u\n",f[1][n]);
    return 0;
}
