#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define lli long long int
using namespace std;
const int maxn=5e3+1e2;

struct Point {
    lli x,y;
    friend Point operator + (const Point &a,const Point &b) {
        return (Point){a.x+b.x,a.y+b.y};
    }
    friend Point operator - (const Point &a,const Point &b) {
        return (Point){a.x-b.x,a.y-b.y};
    }
    friend lli operator * (const Point &a,const Point &b) {
        return a.x * b.y - b.x * a.y;
    }
}ps[maxn],stk[maxn];
double ans;
int n;

inline lli dis(const Point &a,const Point &b) {
    const lli dx = a.x - b.x , dy = a.y - b.y;
    return dx * dx + dy * dy;
}
inline bool operator < (const Point &a,const Point &b) {
    lli t = ( a - ps[1] ) * ( b - ps[1] );
    if( !t ) return dis(a,ps[1]) < dis(b,ps[1]);
    return t > 0;
}

inline void getans() {
    static lli top;
    for(int i=2;i<=n;i++)
        if( ps[i].y < ps[1].y || ( ps[i].y == ps[1].y && ps[i].x < ps[1].x ) ) swap(ps[i],ps[1]);
    sort(ps+2,ps+1+n);
    stk[++top] = ps[1] , stk[++top] = ps[2];
    for(int i=3;i<=n;i++) {
        while( top >= 2 && ( stk[top] - stk[top-1] ) * ( ps[i] - stk[top] ) <= 0 ) --top;
        stk[++top] = ps[i];
    }
    stk[top+1] = stk[1];
    for(int i=1;i<=top;i++)
        ans += sqrt( dis( stk[i] , stk[i+1] ) );
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&ps[i].x,&ps[i].y);
    getans();
    printf("%0.2lf\n",ans);
    return 0;
}
