#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=2e5+1e2;
const int inf=0x3f3f3f3f;

struct Node {
    int x,y;
    friend bool operator < (const Node &a,const Node &b) {
        return a.x < b.x;
    }
}ns[maxn];

int x[maxn],y[maxn];
int id[maxn],stk[maxn],top;
int n;
lli ans;

struct BinaryIndexTreeA {
    int dat[maxn];
    #define lowbit(x) (x&-x)
    BinaryIndexTreeA() { memset(dat,0x3f,sizeof(dat)); }
    inline void update(int pos,int x) {
        while( pos <= n ) dat[pos] = min( dat[pos] , x ) , pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = inf;
        while( pos ) ret = min( ret , dat[pos] ) , pos -= lowbit(pos);
        return ret;
    }
    inline void reset(int pos) {
        while( pos <= n ) dat[pos] = inf , pos += lowbit(pos);
    }
}bx;
struct BinaryIndexTreeB {
    lli dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,int x) {
        while( pos <= n ) dat[pos] += x , pos += lowbit(pos);
    }
    inline lli query(int pos) {
        lli ret = 0;
        while( pos ) ret += dat[pos], pos -= lowbit(pos);
        return ret;
    }
    inline void reset(int pos) {
        while( pos <= n ) dat[pos] = 0 , pos += lowbit(pos);
    }
}by;

inline bool cmp(int a,int b) {
    return y[a] < y[b];
}
inline void solve(int l,int r) {
    if( l == r ) return;
    const int mid = ( l + r ) >> 1;
    for(int i=l;i<=r;i++) id[i] = i;
    sort(id+l,id+r+1,cmp);
    top = 0;
    for(int i=r;i>=l;i--) {
        const int p = id[i];
        if( p > mid ) {
            while( top && x[stk[top]] > x[p] ) by.update(y[stk[top--]],-1);
            stk[++top] = p;
            by.update(y[p],1);
        } else {
            int mxy = bx.query(n-x[p]+1);
            mxy = min( mxy , n );
            ans += by.query(mxy) - by.query(y[p]-1);
            bx.update(n-x[p]+1,y[p]);
        }
    }
    for(int i=r;i>=l;i--) {
        const int p = id[i];
        if( p > mid ) by.reset(y[p]);
        else bx.reset(n-x[p]+1);
    }
    solve(l,mid);
    solve(mid+1,r);
}

inline void refac(int* sou) {
    static int srt[maxn],len;
    memcpy(srt+1,sou+1,sizeof(int)*n);
    sort(srt+1,srt+1+n);
    len = unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++) sou[i] = lower_bound(srt+1,srt+1+len,sou[i]) - srt;
}
inline void ncpy(int ope) {
    if( ope == 1 ) {
        for(int i=1;i<=n;i++)
            ns[i].x = x[i] , ns[i].y = y[i];
    } else if( !~ope ) {
        for(int i=1;i<=n;i++)
            x[i] = ns[i].x , y[i] = ns[i].y;
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",x+i,y+i);
    
    refac(x) , refac(y);
    ncpy(1) , sort(ns+1,ns+1+n) , ncpy(-1);
    solve(1,n);
    
    printf("%lld\n",ans);
    
    return 0;
}

