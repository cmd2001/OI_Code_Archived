#pragma GCC optimize("Ofast")
#include<cstdio>
#include<algorithm>
#include<cctype>
typedef long long int lli;
using namespace std;
const int maxe=1e6+1e5+1e2,maxn=1e5+1e2,maxl=20;
const lli inf=0x3f3f3f3f3f3f3f3fll;

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

inline lli calc(int ll,int rr) {
    if( ll > rr ) return -inf;
    lli ret = su[ll] - su[rr];
    for(int i=1;i<=m;i++) ret += RMQ.query(i,ll,rr);
    return ret;
}
inline void solve(int l_l,int l_r,int r_l,int r_r) {
    if( r_l == r_r ) {
        for(int i=l_l;i<=l_r;i++) ans = max( ans , calc(i,r_l) );
        return;
    } const int r_mid = ( r_l + r_r ) >> 1;
    int l_mid = l_l; f[l_l] = calc(l_l,r_mid);
    for(int i=l_l;i<=l_r;i++) if( ( f[i] = calc(i,r_mid) ) > f[l_mid] ) l_mid = i;
    ans = max( ans , f[l_mid] );
    solve(l_l,l_mid,r_l,r_mid) , solve(l_mid,l_r,r_mid+1,r_r);
}

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
    RMQ.init() , solve(1,n,1,n);
    printf("%lld\n",ans);
    return 0;
}