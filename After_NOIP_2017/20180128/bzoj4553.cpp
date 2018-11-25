#pragma GCC optimize(3)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using std::sort;
using std::min;
using std::max;
const int maxn=1e5+1e2+1;

int in[maxn],mi[maxn],mx[maxn];
int f[maxn],srtl[maxn],srtr[maxn];

struct BinaryIndexTree {
    int dat[maxn],len;
    #define lowbit(x) (x&-x)
    inline void update(int pos,int val) {
        while( pos <= len )
            dat[pos] = max( dat[pos] , val ) ,
            pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while( pos )
            ret = max( ret , dat[pos] ) ,
            pos -= lowbit(pos);
        return ret;
    }
    inline void reset(int pos) {
        while( pos <= len )
            dat[pos] = 0 ,
            pos += lowbit(pos);
    }
    inline void resize(int p) {
        len = p;
    }
}bit;

inline bool cmp1(int a,int b) {
    return in[a] < in[b];
}
inline bool cmp2(int a,int b) {
    return mi[a] < mi[b];
}
inline void solve(int ll,int rr) {
    
    if( ll == rr ) {
        f[ll] = max( f[ll] , 1 );
        return;
    }
    const int mid = ( ll + rr ) >> 1;
    solve(ll,mid);
    for(int i=ll;i<=mid;i++) srtl[i] = i;
    for(int i=mid+1;i<=rr;i++) srtr[i] = i;
    sort(srtl+ll,srtl+mid+1,cmp1) ,
    sort(srtr+mid+1,srtr+rr+1,cmp2) ;
    int p = ll;
    for(int i=mid+1;i<=rr;i++) {
        const int now = srtr[i];
        while( p <= mid && in[srtl[p]] <= mi[now] ) {
            const int pre = srtl[p];
            bit.update(mx[pre],f[pre]);
            ++p;
        }
        f[now] = max( f[now] , bit.query(in[now]) + 1 );
    }
    for(int i=ll;i<=mid;i++) bit.reset(mx[i]);
    solve(mid+1,rr);
}

inline int getint() {
    int ret = 0 , ch ;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int n,m,ans,t;
    n = getint() , m = getint();
    for(int i=1;i<=n;i++)
        mi[i] = mx[i] = in[i] = getint();
    for(int i=1,x,y;i<=m;i++) {
        x = getint() , y = getint() ,
        mi[x] = min( mi[x] , y ) ,
        t = max( t , mx[x] = max( mx[x] , y ) );
    }
    bit.resize(t);
    solve(1,n);
    for(int i=1;i<=n;i++) ans = max( ans , f[i] );
    printf("%d\n",ans);
    return 0;
}
