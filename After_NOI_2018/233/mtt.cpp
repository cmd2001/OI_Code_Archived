#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define debug cerr
#define int long long
typedef long long lli;
using namespace std;
const int maxn = 262145;
const int p[]={469762049,998244353,1004535809};

int a[maxn],b[maxn],mod;
lli ans[maxn];

class NTTer {
private:
    int a[maxn],b[maxn],mod;
    inline int add(const int &x,const int &y) {
        const int ret = x + y;
        return ret >= mod ? ret - mod : ret;
    }
    inline int sub(const int &x,const int &y) {
        const int ret = x - y;
        return ret < 0 ? ret + mod : ret;
    }
    inline lli mul(const int &x,const int &y) {
        return (lli) x * y % mod;
    }
    inline int fastpow(int base,int tim) {
        int ret = 1;
        while(tim) {
            if(tim & 1) ret = mul(ret,base);
            if(tim >>= 1) base = mul(base,base);
        }
        return ret;
    }
    inline void NTT(int* dst,const int n,const int ope) {
        for(int i=0,j=0;i<n;i++) {
            if(i < j) swap(dst[i],dst[j]);
            for(int t=n>>1;(j^=t)<t;t>>=1);
        }
        for(int len=2,h=1;len<=n;len<<=1,h<<=1) {
            int per = fastpow(3,mod/len);
            if(!~ope) per = fastpow(per,mod-2);
            for(int st=0;st<n;st+=len) {
                int w = 1;
                for(int pos=0;pos<h;pos++) {
                    const int u = dst[st+pos], v = mul(dst[st+pos+h],w);
                    dst[st+pos] = add(u,v), dst[st+pos+h] = sub(u,v), w = mul(w,per);
                }
            }
        }
        if(!~ope) {
            const int inv = fastpow(n,mod-2);
            for(int i=0;i<n;i++) dst[i] = mul(dst[i],inv);
        }
    }
public:
    const int& operator [] (const int &x) const {
        return a[x];
    }
    inline void work(const int len) {
        NTT(a,len,1), NTT(b,len,1);
        for(int i=0;i<len;i++) a[i] = mul(a[i],b[i]);
        NTT(a,len,-1);
    }
    inline void init(const int &mm,int* aa,int* bb,const int n,const int m) {
        memcpy(a,aa,sizeof(int)*n), memcpy(b,bb,sizeof(int)*m), mod = mm;
    }
}ntt[3];

inline int fastpow(int base,int tim,int mod) {
    int ret = 1;
    while(tim) {
        if(tim & 1) ret = (lli) ret * base % mod;
        if(tim >>= 1) base = (lli) base * base % mod;
    }
    return ret;
}

inline lli mul(lli x,lli y,const lli mod) {
    lli ret = 0;
    while(x) {
        if(x & 1) ret = (ret + y) % mod;
        if(x >>= 1) y = (y + y) % mod;
    }
    return ret;
}

inline void CRT(int len) {
    static lli ms[2],M,inv;
    ms[0] = (lli) p[1] * fastpow(p[1]%p[0],p[0]-2,p[0]), ms[1] = (lli) p[0] * fastpow(p[0]%p[1],p[1]-2,p[1]),
    M = (lli) p[0] * p[1], inv = fastpow(M%p[2],p[2]-2,p[2]);
    for(int i=0;i<=len;i++) {
        ans[i] = (mul(ntt[0][i],ms[0],M) + mul(ntt[1][i],ms[1],M)) % M;
        lli k = ((ntt[2][i] - ans[i]) % p[2] + p[2]) % p[2] * inv % p[2];
        ans[i] = (mul(k,M,mod) + ans[i]) % mod;
    }
}

signed main() {
    static int n,m,len;
    scanf("%lld%lld%lld",&n,&m,&mod);
    for(len=1;len<=n+m;len<<=1);
    for(int i=0;i<=n;i++) scanf("%lld",a+i), a[i] %= mod;
    for(int i=0;i<=m;i++) scanf("%lld",b+i), b[i] %= mod;
    for(int i=0;i<3;i++) ntt[i].init(p[i],a,b,n+1,m+1), ntt[i].work(len);
    CRT(n+m);
    for(int i=0;i<=n+m;i++) printf("%lld%c",ans[i],"\n "[i!=n+m]);
    return 0;
}
