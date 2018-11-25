#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
typedef long long int lli;
const int maxn=1e6+1e2;

int a[maxn],b[maxn],c[maxn],n;
lli ans;

struct BinaryIndexTree {
    int dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int x) {
        while( x <= n ) ++dat[x] , x += lowbit(x);
    }
    inline int query(int x) {
        int ret = 0;
        while(x) ret += dat[x] , x -= lowbit(x);
        return ret;
    }
    inline void reset() {
        memset(dat,0,sizeof(dat));
    }
}bit;

struct Point {
    int x,y;
    friend bool operator < (const Point &a,const Point &b) {
        return a.x < b.x;
    }
}ps[maxn];

inline lli C(lli n) {
    return n * ( n - 1 ) / 2;
}

inline lli calc(int* a,int* b) {
    lli ret = 0;
    for(int i=1;i<=n;i++) ps[i] = (Point){a[i],b[i]};
    bit.reset() , std::sort(ps+1,ps+1+n);
    for(int i=1;i<=n;i++) bit.update(ps[i].y) , ret += i - bit.query(ps[i].y);
    return ret;
}

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st=buf+BS,*ed=buf+BS;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0;
    char ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    freopen("order.in","r",stdin);
    freopen("order.out","w",stdout);
    n = getint();
    for(int i=1;i<=n;i++) a[getint()] = i;
    for(int i=1;i<=n;i++) b[getint()] = i;
    for(int i=1;i<=n;i++) c[getint()] = i;
    ans = calc(a,b) + calc(a,c) + calc(b,c);
    ans = C(n) - ( ans >> 1 );
    return printf("%lld\n",ans) , fclose(stdout);
}

