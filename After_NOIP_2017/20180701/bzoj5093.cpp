#include<cstdio>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=524289;
const int mod=998244353,g=3;

inline int add(const int &x,const int &y) {
    const int ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline int sub(const int &x,const int &y) {
    const int ret = x - y;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}
inline void mule(int &dst,const int &x) {
    dst = (lli) dst * x % mod;
}
inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) mule(ret,base);
        if( tim >>= 1 ) mule(base,base);
    }
    return ret;
}
inline void NTT(int* dst,int n,int tpe) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) swap(dst[i],dst[j]);
        for(int t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) {
        int per = fastpow(g,mod/len);
        if( !~tpe ) per = fastpow(per,mod-2);
        for(int st=0;st<n;st+=len) {
            int w = 1;
            for(int pos=0;pos<h;pos++) {
                const int u = dst[st+pos] , v = mul(dst[st+pos+h],w);
                dst[st+pos] = add(u,v) , dst[st+pos+h] = sub(u,v) , mule(w,per);
            }
        }
    }
    if( !~tpe ) {
        const int inv = fastpow(n,mod-2);
        for(int i=0;i<n;i++) mule(dst[i],inv);
    }
}

int fac[maxn],inv[maxn],facn[maxn],str[maxn];
int a[maxn],b[maxn];

int main() {
    static int n,k,len,ans;
    scanf("%d%d",&n,&k) , --n;
    for(len=1;len<=k<<1;len<<=1) ;
    *fac = 1; for(int i=1;i<=k;i++) fac[i] = mul(fac[i-1],i);
    inv[k] = fastpow(fac[k],mod-2); for(int i=k;i;i--) inv[i-1] = mul(inv[i],i);
    *facn = 1; for(int i=1;i<=k;i++) facn[i] = mul(facn[i-1],n-i+1);
    for(int i=0;i<=k;i++) {
        a[i] = mul( ( i & 1 ) ? mod - 1 : 1 , inv[i] );
        b[i] = mul( fastpow(i,k) , inv[i] );
    }
    NTT(a,len,1) , NTT(b,len,1);
    for(int i=0;i<len;i++) str[i] = mul(a[i],b[i]);
    NTT(str,len,-1);
    for(int i=0;i<=min(n,k);i++) adde(ans,mul(str[i],mul(facn[i],fastpow(2,n-i))));
    mule(ans,n+1) , mule(ans,fastpow(2,((lli)n*(n-1)>>1)%(mod-1))) , printf("%d\n",ans);
    return 0;
}

