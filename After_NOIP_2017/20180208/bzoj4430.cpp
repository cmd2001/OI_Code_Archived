#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=2e5+1e2;

int a[maxn],b[maxn],c[maxn];
int p[maxn],pp[maxn];
int n;
lli ans,minu;

struct BinaryIndexTree {
    lli dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos) {
        while( pos <= n ) dat[pos]++ , pos += lowbit(pos);
    }
    inline lli query(int pos) {
        lli ret = 0;
        while( pos ) ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
    inline void reset() {
        memset(dat,0,sizeof(dat));
    }
}bit;
struct Node {
    int px,py;
    friend bool operator < (const Node &a,const Node &b) {
        return a.px < b.px;
    }
}ns[maxn];

inline lli calc(int* x,int* y) {
    for(int i=1;i<=n;i++)
        p[x[i]] = i , pp[y[i]] = i;
    for(int i=1;i<=n;i++)
        ns[i] = (Node){p[i],pp[i]};
    sort(ns+1,ns+1+n) , bit.reset();
    lli ret = 0;
    for(int i=1;i<=n;i++) {
        bit.update(ns[i].py);
        ret += i - bit.query(ns[i].py);
    }
    return ret;
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) scanf("%d",b+i);
    for(int i=1;i<=n;i++) scanf("%d",c+i);
    ans = (lli) n * ( n - 1 ) >> 1;
    minu = calc(a,b) + calc(b,c) + calc(c,a);
    ans -= minu >> 1;
    printf("%lld\n",ans);
    return 0;
}