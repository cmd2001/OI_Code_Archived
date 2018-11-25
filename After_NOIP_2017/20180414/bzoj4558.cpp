#include<cstdio>
#include<algorithm>
#include<tr1/unordered_set>
using namespace std;
using namespace tr1;
typedef long long int lli;
using namespace std;
using namespace tr1;
const int maxp=2e3+1e2;
const int mod=1e8+7;

struct Point {
    int x,y;
    friend bool operator < (const Point &a,const Point &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
    friend Point operator - (const Point &a,const Point &b) {
        return (Point){a.x-b.x,a.y-b.y};
    }
    friend Point operator + (const Point &a,const Point &b) {
        return (Point){a.x+b.x,a.y+b.y};
    }
    friend Point operator * (const Point &a,const int &b) {
        return (Point){a.x*b,a.y*b};
    }
    friend Point operator / (const Point &a,const int &b) {
        return (Point){a.x/b,a.y/b};
    }
    inline Point swp() const {
        return (Point){y,-x};
    }
    inline bool candiv() const {
        return ( ! ( x & 1 ) ) && ( ! ( y & 1 ) );
    }
}pt[maxp];
unordered_set<lli> st;
int n,m,t;
lli ans,ini,sig,dou,tri,qua;

inline void insert(const Point &p) {
    lli h = (lli) p.x * ( m + 1 ) + p.y;
    st.insert(h);
}
inline bool inside(const Point &p) {
    return 0 <= p.x && p.x <= n && 0 <= p.y && p.y <= m;
}
inline bool legal(const Point &pa,const Point &pb) {
    return inside(pa) && inside(pb);
}
inline bool have(const Point &p) {
    lli h = (lli) p.x * ( m + 1 ) + p.y;
    return st.find(h) != st.end();
}
inline lli calcini(lli n,lli m) {
    lli ret = 0 , lim = min( n , m );
    for(lli i=1;i<=lim;i++) ret = ( ret + ( n - i + 1 ) % mod * ( m - i + 1 ) % mod * i % mod ) % mod;
    return ret;
}
inline lli calcedge(const lli &l,const lli &r,const lli &h) {
    lli t = min( l + r , h );
    if( !t ) return 0;
    lli ret = ( t * ( t + 3 ) >> 1 ) % mod;
    if( t > l ) ret -= ( ( t - l ) * ( t - l + 1 ) >> 1 ) % mod;
    if( t > r ) ret -= ( ( t - r ) * ( t - r + 1 ) >> 1 ) % mod;
    return ( ret % mod + mod ) % mod;
}
inline lli calcsingle(lli x,lli y) {
    const lli a = n - x , b = m - y , c = x , d = y;
    lli ret = ( calcedge(d,b,a) + calcedge(d,b,c) + calcedge(a,c,b) + calcedge(a,c,d) ) % mod;
    ret -= ( min(a,b) + min(b,c) + min(c,d) + min(d,a) ) % mod;
    return ( ret % mod + mod ) % mod;
}
inline lli calcdouble(const Point &a,const Point &b) {
    const Point delta = (a-b).swp();
    int ret = legal(a+delta,b+delta) + legal(a-delta,b-delta);
    const Point mid = a + b , pa = mid + delta , pb = mid - delta;
    if( pa.candiv() && pb.candiv() && legal(pa/2,pb/2) ) ++ret;
    return ret;
}
inline lli calctriple(const Point &a,const Point &b) {
    const Point delta = (a-b).swp();
    int ret = 0;
    if( legal(a+delta,b+delta) ) ret += have(a+delta) + have(b+delta);
    if( legal(a-delta,b-delta) ) ret += have(a-delta) + have(b-delta);
    const Point mid = a + b , pa = mid + delta , pb = mid - delta;
    if( pa.candiv() && pb.candiv() && legal(pa/2,pb/2) ) ret += have(pa/2) + have(pb/2);
    return ret;
}
inline lli calcquad(const Point &a,const Point &b) {
    const Point delta = (a-b).swp();
    int ret = 0;
    if( legal(a+delta,b+delta) ) ret += ( have(a+delta) && have(b+delta) );
    if( legal(a-delta,b-delta) ) ret += ( have(a-delta) && have(b-delta) );
    const Point mid = a + b , pa = mid + delta , pb = mid - delta;
    if( pa.candiv() && pb.candiv() && legal(pa/2,pb/2) ) ret += ( have(pa/2) && have(pb/2) );
    return ret;
}

int main() {
    scanf("%d%d%d",&n,&m,&t);
    for(int i=1;i<=t;i++) scanf("%d%d",&pt[i].x,&pt[i].y) , insert(pt[i]);
    ini = calcini(n,m);
    for(int i=1;i<=t;i++) sig += calcsingle(pt[i].x,pt[i].y);
    for(int i=1;i<=t;i++) for(int j=i+1;j<=t;j++) {
        dou += calcdouble(pt[i],pt[j]) , tri += calctriple(pt[i],pt[j]) , qua += calcquad(pt[i],pt[j]);
    }
    tri /= 3 , qua /= 6;
    ans = ( ( ini - sig + dou - tri + qua ) % mod + mod ) % mod;
    printf("%lld\n",ans);
    return 0;
}

