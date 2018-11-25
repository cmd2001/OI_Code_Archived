#include<cstdio>
#include<algorithm>
#define lli long long int
const int maxn=1e5+1e2;

int ycnt;
struct BinaryIndexTree {
    int dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,int x) {
        while( pos <= ycnt ) dat[pos] = std::max( dat[pos] , x ) , pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while( pos ) ret = std::max( ret , dat[pos] ) , pos -= lowbit(pos);
        return ret;
    }
}bit;
struct Point {
    lli x,y;
    friend lli operator * (const Point &a,const Point &b) {
        return a.x * b.y - a.y * b.x;
    }
    friend bool operator < (const Point &a,const Point &b) {
        return a.x != b.x ? a.x < b.x : a.y > b.y;
    }
    friend bool operator == (const Point &a,const Point &b) {
        return a.x == b.x && a.y == b.y;
    }
}ps[maxn],stx,sty;

lli ys[maxn];
int f[maxn],n,ans;

inline void trans() {
    for(int i=1;i<=n;i++) {
        const Point t = ps[i];
        ps[i].x = - ( t * sty ) , ys[i] = ps[i].y = t * stx; // x1 * y2 - x2 * y1 < 0 .
    }
    std::sort(ps+1,ps+1+n) , std::sort(ys+1,ys+1+n);
    n = std::unique(ps+1,ps+1+n) - ps - 1;
    ycnt = std::unique(ys+1,ys+1+n) - ys - 1;
    for(int i=1;i<=n;i++) ps[i].y = std::lower_bound(ys+1,ys+1+ycnt,ps[i].y) - ys;
}
inline void dp() {
    for(int i=1;i<=n;i++) {
        f[i] = bit.query(ps[i].y-1) + 1 ,
        bit.update(ps[i].y,f[i]);
        if( !ps[i].x && !ys[ps[i].y] ) {
            ans = f[i]-1;
            break;
        }
    }
}

int main() {
    scanf("%d",&n);
    scanf("%lld/%lld",&stx.y,&stx.x) ,
    scanf("%lld/%lld",&sty.y,&sty.x);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&ps[i].x,&ps[i].y);
    ps[++n] = (Point){0,0};
    trans() , dp();
    printf("%d\n",ans);
    return 0;
}
