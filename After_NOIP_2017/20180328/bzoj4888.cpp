#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxs=(1<<20)+10,lim=1<<20;

int in[maxn],n,ans;

struct BinaryIndexTree {
    int dat[maxs];
    #define lowbit(x) (x&-x)
    inline void update(int pos) {
        ++pos;
        while( pos <= lim ) dat[pos]++ , pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0; ++pos;
        while( pos ) ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
    inline void reset() {
        memset(dat,0,sizeof(dat));
    }
}zero,one;

inline int mask(const int &x,const int &t) {
    return x & ( ( 1 << t ) - 1 );
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , in[i] += in[i-1];
    for(int bit=0,sum;bit<21;bit++) {
        zero.reset() , one.reset() , sum = 0;
        zero.update(0);
        for(int i=1,o;i<=n;i++) {
            const int m = mask(in[i],bit);
            o = 0;
            if( in[i] & ( 1 << bit ) ) {
                o = zero.query(m) + ( one.query(lim) - one.query(m) );
                one.update(m);
            } else {
                o = one.query(m) + ( zero.query(lim) - zero.query(m) );
                zero.update(m);
            }
            sum += o;
        }
        if( sum & 1 ) ans |= ( 1 << bit );
    }
    printf("%d\n",ans);
    return 0;
}
