#pragma GCC optimize("Ofast")
#include<cstdio>
#include<algorithm>
#include<cctype>
typedef long long int lli;
using namespace std;
const int maxe=1e6+1e2,maxn=1e5,maxl=20;
// I am a sb and I can't solve any problem, although all over the world has solved T1.
// Compilation technology is well developed, we don't need to support it.

int n,m;

struct RMQ {
    struct Array {
        int dat[maxe][maxl];
        inline int* operator () (const int &i,const int &j) { // i is kind , j is pos .
            return dat[n*(i-1)+j];
        }
    }arr;
    int Log[maxn];

    inline void init() {
        for(int i=2;i<=n;i++) Log[i] = Log[i>>1] + 1;
        for(int i=1;i<=m;i++) for(int k=1;k<=Log[n];k++) for(int j=1;j<=n;j++)
            arr(i,j)[k] = max( arr(i,j)[k-1] , arr(i,j+(1<<(k-1)))[k-1] );
    }
    inline int query(int k,int l,int r) {
        const int Lo = Log[r-l+1];
        return max( arr(k,l)[Lo] , arr(k,r-(1<<Lo)+1)[Lo] );
    }
}RMQ;

lli su[maxn],f[maxn],ans;

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) ) ;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}
int main() {
    n = getint() , m = getint();
    for(int i=2;i<=n;i++) su[i] = su[i-1] + getint();
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) *RMQ.arr(j,i) = getint();
    RMQ.init();
    for(int r=n,l=n;r;r--) {
        l = min( l , r );
        for(int j=l;j;j--) {
            f[j] = su[j] - su[r];
            for(int k=1;k<=m;k++) f[j] += RMQ.query(k,j,r);
            if( f[j] >= f[l] ) l = j;
        }
        ans = max( ans , f[l] );
    }
    printf("%lld\n",ans);
    return 0;
}
