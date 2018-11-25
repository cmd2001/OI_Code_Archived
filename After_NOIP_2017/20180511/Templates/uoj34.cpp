#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=262145,mod=998244353,g=3;

lli a[maxn],b[maxn],c[maxn];

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}

inline void NTT(lli* dst,int n,int tpe) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) std::swap(dst[i],dst[j]);
        for(int t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) {
        lli per = fastpow(g,mod/len);
        if( !~tpe ) per = fastpow(per,mod-2);
        for(int st=0;st<n;st+=len) {
            lli w = 1;
            for(int pos=0;pos<h;pos++) {
                const lli u = dst[st+pos] , v = dst[st+pos+h] * w % mod;
                dst[st+pos] = ( u + v ) % mod , dst[st+pos+h] = ( u - v + mod ) % mod , w = w * per % mod;
            }
        }
    }
    if( !~tpe ) {
        lli inv = fastpow(n,mod-2);
        for(int i=0;i<n;i++) dst[i] = dst[i] * inv % mod;
    }
}

int main() {
    static int n,m,len;
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++) scanf("%lld",a+i);
    for(int i=0;i<=m;i++) scanf("%lld",b+i);
    for(len=1;len<=n+m+1;len<<=1) ;
    NTT(a,len,1) , NTT(b,len,1);
    for(int i=0;i<len;i++) c[i] = a[i] * b[i] % mod;
    NTT(c,len,-1);
    for(int i=0;i<=n+m;i++) printf("%lld%c",c[i],i!=n+m?' ':'\n');
    return 0;
}
