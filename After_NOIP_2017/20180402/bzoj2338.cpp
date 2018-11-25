#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1.5e3+1e1,maxe=maxn*maxn;

struct Point {
    lli x,y;
    friend bool operator < (const Point &a,const Point &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
    friend Point operator - (const Point &a,const Point &b) {
        return (Point){a.x-b.x,a.y-b.y};
    }
    friend Point operator + (const Point &a,const Point &b) {
        return (Point){a.x+b.x,a.y+b.y};
    }
    friend lli operator * (const Point &a,const Point &b) {
        return a.x * b.y - a.y * b.x;
    }
    friend bool operator == (const Point &a,const Point &b) {
        return a.x == b.x && a.y == b.y;
    }
}ps[maxn];

inline lli sq(const lli &x) {
    return x * x;
}
inline lli dis(const Point &a,const Point &b) {
    return sq(a.x-b.x) + sq(a.y-b.y);
}

int cnt;
struct Line {
    Point a,b,mid;
    lli dis;
    friend lli operator * (const Line &a,const Line &b) {
        return abs( (a.a-b.a) * (a.b-b.a) );
    }
    friend bool operator < (const Line &a,const Line &b) {
        return (! ( a.mid == b.mid ) ) ? a.mid < b.mid : a.dis < b.dis;
    }
    friend bool operator == (const Line &a,const Line &b) {
        return a.mid == b.mid && a.dis == b.dis;
    }
}ls[maxe>>1];

int main() {
    static int n;
    static lli ans;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&ps[i].x,&ps[i].y);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++) {
            ls[++cnt] = (Line){ps[i],ps[j],ps[i]+ps[j],dis(ps[i],ps[j])};
        }
    sort(ls+1,ls+1+cnt);
    for(int l=1,r;l<=cnt;l=r+1) {
        for(r=l;r<cnt&&ls[r+1]==ls[l];r++) ;
        for(int i=l;i<=r;i++) for(int j=l+1;j<=r;j++) ans = max( ans , ls[i] * ls[j] );
    }
    printf("%lld\n",ans);
    return 0;
}
