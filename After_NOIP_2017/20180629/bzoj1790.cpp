#include<cstdio>
#include<algorithm>
#include<cctype>
using namespace std;
const int maxn=2e5+1e2;

int srt[maxn],n;
struct ReversedBinaryIndexTree {      
    int dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,const int &val) {
        while(pos) dat[pos] = max( dat[pos] , val ) , pos -= lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while( pos <= n ) ret = max( ret , dat[pos] ) , pos += lowbit(pos);
        return ret;
    }
    inline void reset(int pos) {
        while(pos) dat[pos] = 0 , pos -= lowbit(pos);
    }
}bit;

bool can[maxn];
struct Point {
    int x,y,xx,yy,id;
    friend bool operator < (const Point &a,const Point &b) {
        return a.y < b.y;
    }
}ps[maxn];
inline bool cmp(const Point &a,const Point &b) {
    return a.x < b.x;
}

inline void merge(int l,int mid,int r) {
    static Point tmp[maxn];
    int lptr = l , rptr = mid + 1 , pos = l;
    while( lptr <= mid && rptr <= r ) tmp[pos++] = ps[lptr] < ps[rptr] ? ps[lptr++] : ps[rptr++];
    while( lptr <= mid ) tmp[pos++] =  ps[lptr++];
    while( rptr <= r ) tmp[pos++] = ps[rptr++];
    for(int i=l;i<=r;i++) ps[i] = tmp[i];
}
inline void solve(int l,int r) {
    if( l == r ) return;
    const int mid = ( l + r ) >> 1;
    solve(l,mid) , solve(mid+1,r);
    for(int i=mid+1,j=l;i<=r;i++) {
        while( j <= mid && ps[j].y < ps[i].y ) bit.update(ps[j].xx,ps[j].yy) , ++j;
        can[ps[i].id] |= ( bit.query(ps[i].xx) > ps[i].yy );
    }
    for(int i=l;i<=mid;i++) bit.reset(ps[i].xx);
    merge(l,mid,r);
}

inline int getint() {
    int ret = 0 , fix = 1; char ch;
    while( !isdigit(ch=getchar()) ) fix = ch == '-' ? -fix : fix;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret; 
}

int main() {
    static int su;
    n = getint();
    for(int i=1;i<=n;i++) ps[i].x = getint() , ps[i].y = getint() , srt[i] = ps[i].xx = getint() , ps[i].yy = getint() , ps[i].id = i;
    sort(srt+1,srt+1+n) , sort(ps+1,ps+1+n,cmp);
    for(int i=1;i<=n;i++) ps[i].xx = lower_bound(srt+1,srt+1+n,ps[i].xx) - srt;
    solve(1,n);
    for(int i=1;i<=n;i++) su += can[i];
    printf("%d\n",su);
    return 0;
}
 
