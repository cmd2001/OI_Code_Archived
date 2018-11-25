#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

int srt[maxn],len;
struct BinaryIndexTree {
    lli dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,lli x) {
        while( pos <= len ) dat[pos] = max( dat[pos] , x ) , pos += lowbit(pos);
    }
    inline lli query(int pos) {
        lli ret = 0;
        while( pos ) ret = max( ret , dat[pos] ) , pos -= lowbit(pos);
        return ret;
    }
}bit;

struct Point {
    int x,y,v;
    friend bool operator < (const Point &a,const Point &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
}ps[maxn];

int main() {
    static int n;
    static lli ans,f;
    scanf("%*d%*d%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d%d",&ps[i].x,&ps[i].y,&ps[i].v) , srt[i] = ps[i].y;
    sort(ps+1,ps+1+n) , sort(srt+1,srt+1+n) , len = unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++) ps[i].y = lower_bound(srt+1,srt+1+len,ps[i].y) - srt;
    for(int i=1;i<=n;i++) ans = max( ans , f = bit.query(ps[i].y) + ps[i].v ) , bit.update(ps[i].y,f);
    printf("%lld\n",ans);
    return 0;
}
