#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<functional>
#include<vector>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e4+1e2,maxl=1<<17;
const int mod = 2013265921 , g = 31;

int len[maxn];
lli fac[maxn],invfac[maxn];
vector<lli> v[maxn];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;

inline lli fastpow(lli base,int tme,int mod) {
    lli ret = 1;
    while( tme ) {
        if( tme & 1 ) ret = ret * base % mod;
        base = base * base % mod;
        tme >>= 1;
    }
    return ret;
}
inline lli getinv(lli x) {
    return fastpow(x,mod-2,mod);
}
inline lli c(int n,int m) {
    return fac[n] * invfac[m] % mod * invfac[n-m] % mod;
}

inline int revbit(int x,int len) {
    int ret = 0;
    for(int t=1;t<len;t<<=1)
        ret <<= 1 , ret |= x&1 , x >>= 1;
    return ret;
}
inline void NTT(lli* dst,int n,int ope) {
    for(int i=0,j;i<n;i++) {
        j = revbit(i,n);
        if( i < j ) swap(dst[i],dst[j]);
    }
    for(int len=2;len<=n;len<<=1) {
        lli per = fastpow( g , mod / len , mod );
        if( !~ope ) per = getinv(per);
        for(int st=0;st<n;st+=len) {
            lli w = 1;
            for(int pos=0;pos<len>>1;pos++) {
                const lli x = dst[st+pos] , y = dst[st+pos+(len>>1)] * w % mod;
                dst[st+pos] = ( x + y ) % mod ,
                dst[st+pos+(len>>1)] = ( x - y + mod ) % mod;
                w = w * per % mod;
            }
        }
    }
    if( !~ope ) {
        lli inv = getinv(n);
        for(int i=0;i<n;i++)
            dst[i] = dst[i] * inv % mod;
    }
}
inline void mul(int x,int y) { // multi v[x] v[y] into v[x] and update len[x]
    static lli a[maxl],b[maxl];
    int n = 1 , lx = len[x] , ly = len[y];
    while( n <= lx + ly ) n <<= 1;
    memset(a,0,sizeof(lli)*(n+1)) , memset(b,0,sizeof(lli)*(n+1));
    for(int i=0;i<=lx;i++) a[i] = v[x][i];
    for(int i=0;i<=ly;i++) b[i] = v[y][i];
    NTT(a,n,1) , NTT(b,n,1);
    for(int i=0;i<n;i++)
        a[i] = a[i] * b[i] % mod;
    NTT(a,n,-1);
    n = len[x] + len[y];
    v[x].resize(n+1) , len[x] = n;
    for(int i=0;i<=n;i++)
        v[x][i] = a[i];
}

inline void merge() {
    while( pq.size() > 1 ) {
        const int y = pq.top().second; pq.pop();
        const int x = pq.top().second; pq.pop();
        mul(x,y) , v[y].resize(0);
        pq.push( make_pair(len[x],x) );
    }
}
inline void prefac(int x) {
    *fac = 1;
    for(int i=1;i<=x;i++)
        fac[i] = fac[i-1] * i % mod;
    invfac[x] = getinv(fac[x]);
    for(int i=x-1;~i;i--)
        invfac[i] = invfac[i+1] * ( i + 1 ) % mod;
}
inline void getans() {
    int n , sum = 0 , exp = 1006632961;
    lli ans = 0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",len+i) , sum += len[i];
    prefac(sum);
    for(int i=1;i<=n;i++) {
        v[i].resize(len[i]+1);
        for(int j=1;j<=len[i];j++)
            v[i][j] = c(len[i]-1,j-1) * invfac[j] % mod;
        pq.push( make_pair(len[i],i) );
    }
    merge();
    const int x = pq.top().second; pq.pop();
    for(int i=1;i<=len[x];i+=2)
        ans += v[x][i] * fac[i] % mod , ans %= mod;
    if( n == sum ) exp = n & 1;
    printf("%d %lld\n",exp,ans);
}

int main() {
    static int t;
    scanf("%d",&t);
    while( t-- )
        getans();
    return 0;
}
