#include<cstdio>
typedef long long int lli;
const int maxn=3e6+1e2;

int mod;

inline int add(const int &a,const int &b) {
    const int ret = a + b;
    return ret >= mod ? ret - mod : ret;
}
inline int mul(const int &a,const int &b) {
    return (lli) a * b % mod;
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

int f[maxn],g[maxn],n,pi,ans;

inline void sieve() {
    ans = f[0] = 0 , pi = g[1] = f[1] = 1;
    for(int i=2;i<=n;i++) g[i] = f[i] = add(f[i-2],add(f[i-1],f[i-1]));
    for(int i=1,inv;i<=n;i++) {
        mule(pi,g[i]) , adde(ans,mul(pi,i)) , inv = fastpow(g[i],mod-2);
        for(int j=i+i;j<=n;j+=i) mule(g[j],inv);
    }
}

int main() {
    static int T;
    scanf("%d",&T);
    while(T--) scanf("%d%d",&n,&mod) , sieve() , printf("%d\n",ans);
    return 0;
}
