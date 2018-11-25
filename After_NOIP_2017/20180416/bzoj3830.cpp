#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e6+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

lli t[maxn],f[maxn],s;
int n;

struct BinaryIndexTree {
    lli dat[maxn];
    #define lowbit(x) (x&-x)
    BinaryIndexTree() { memset(dat,0x3f,sizeof(dat)); }
    inline void update(int pos,lli x) {
        while( pos <= n ) dat[pos] = min( dat[pos] , x ) , pos += lowbit(pos);
    }
    inline lli query(int pos) {
        lli ret = inf;
        while( pos ) ret = min( ret , dat[pos] ) , pos -= lowbit(pos);
        return ret;
    }
}bit;

inline int bin(int i) {
    int l = 0 , r = i, mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if(t[i]-i>=f[mid]-mid-1) l = mid;
        else r = mid;
    }
    return r;
}

int main() {
    scanf("%d%lld",&n,&s);
    for(int i=1;i<=n;i++) {
        scanf("%lld",t+i);
        if( i != 1 ) t[i] = max( t[i-1] + 1 , t[i] );
    }
    for(int i=1,b;i<=n;i++) {
        if( i == 1 ) f[i] = t[i] + 2 * s;
        else {
            b = bin(i);
            f[i] = min( t[i] - i + 2 * s + 2 * i - ( b - 1 ) - 1 , bit.query(n-b+1) + 2 * s + 2 * i );
            bit.update(n-i+1,f[i]-2*i-2);
        }
    }
    printf("%lld\n",f[n]);
    return 0;
}
