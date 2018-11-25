#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=2e3+1e2;
const double eps = 1e-8;

inline int dcmp(const double &x) {
    return fabs(x) <= eps ? 0 : x < 0 ? -1 : 1;
}
struct Point {
    double x,y;
    friend Point operator - (const Point &a,const Point &b) {
        return (Point){a.x-b.x,a.y-b.y};
    }
    friend double operator * (const Point &a,const Point &b) {
        return a.x * b.y - a.y * b.x;
    }
    friend double operator & (const Point &a,const Point &b) {
        const double dx = a.x - b.x , dy = a.y - b.y;
        return sqrt( dx * dx + dy * dy );
    }
}in[maxn],stk[maxn];
int n,top;

bool operator < (const Point &a,const Point &b) {
    double mul = ( a - in[1] ) * ( b - in[1] );
    if( !dcmp(mul) ) return ( a & in[1] ) < ( b & in[1] );
    return mul > 0;
}

inline void pre() {
    for(int i=2;i<=n;i++)
        if( in[i].x < in[1].x || ( !dcmp(in[i].x-in[1].x) && in[i].y < in[1].y) ) swap( in[i] , in[1] );
    sort(in+2,in+1+n);
    stk[top++] = in[1] , stk[top++] = in[2];
    for(int i=3;i<=n;i++) {
        while( top > 1 && ( stk[top-1] - stk[top-2] ) * ( in[i] - stk[top-1] ) < 0 ) --top;
        stk[top++] = in[i];
    }
}
inline double getans() {
    double ret = 0;
    for(int x=0;x<top;x++) {
        int a = (x+1)%top , b = (x+3)%top;
        for(int y=(x+2)%top;y<top;y++) {
            while( ( a + 1 ) % top != y && ( stk[(a+1)%top] - stk[x] ) * ( stk[y] - stk[x] ) >= ( stk[a] - stk[x] ) * ( stk[y] -stk[x] ) )
                a = ( a + 1 ) % top;
            while( ( b + 1 ) % top != x && ( stk[y] - stk[x] ) * ( stk[(b+1)%top] - stk[x] ) >= ( stk[y] - stk[x] ) * ( stk[b] - stk[x] ) )
                b = ( b + 1 ) % top;
            ret = max( ret , ( stk[a] - stk[x] ) * ( stk[y] -stk[x] ) + ( stk[y] - stk[x] ) * ( stk[b] - stk[x] ) );
        }
    }
    return ret / 2;
}

int main() {
    static double ans;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lf%lf",&in[i].x,&in[i].y);
    pre();
    ans = getans();
    printf("%0.3lf\n",ans);
    return 0;
}
