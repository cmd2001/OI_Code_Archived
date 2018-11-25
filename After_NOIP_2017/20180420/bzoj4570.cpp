#include<cstdio>
#include<algorithm>
#include<cmath>
typedef long long int lli;
const int maxn=1e6+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

struct Point {
    int x,y;
    friend bool operator < (const Point &a,const Point &b) {
        return a.x != b.x ? a.x < b.x : a.y > b.y;
    }
    inline long double calc(const long double &t) const {
        return (long double) x + y + t * x + y / t;
    }
    inline long double gtk() const {
        return std::sqrt( (long double) y / x  );
    }
}in[maxn],ps[maxn];

int n,top;
long double ans = inf;

inline long double slop(const Point &l,const Point &r) {
    return l.x == r.x ? -inf : (long double) ( r.y - l.y ) / ( r.x - l.x );
}

inline void getconvex() {
    std::sort(in+1,in+1+n);
    for(int i=1;i<=n;i++) {
        while( top && ps[top].y < in[i].y ) --top;
        while( top > 1 && slop(ps[top-1],ps[top]) < slop(ps[top],in[i]) ) --top;
        ps[++top] = in[i];
    }
}
inline void calc() {
    if( top == 1 ) ans = ps[top].calc(ps[top].gtk());
    else {
        long double l , r = 0 , k;
        for(int i=1;i<=top;i++) {
            l = i != top ? slop(ps[i],ps[i+1]) : -inf , k = ps[i].gtk();
            if( l <= -k && -k <= r ) ans = std::min( ans , ps[i].calc(k) );
            else if( i != 1 ) ans = std::min( ans , ps[i].calc(-r) );
            r = l;
        }
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&in[i].x,&in[i].y);
    getconvex() , calc() , printf("%0.4Lf\n",ans);
    return 0;
}