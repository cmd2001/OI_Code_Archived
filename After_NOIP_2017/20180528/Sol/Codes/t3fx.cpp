#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=524289;
const int mod=998244353,g=3;

int fac[maxn],inv[maxn],a[maxn],b[maxn],ans[maxn];

inline int add(const int &a,const int &b) {
    register int ret = a + b;
    return ret >= mod ? ret - mod : ret;
}
inline int sub(const int &a,const int &b) {
    register int ret = a - b;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &a,const int &b) {
    return (lli) a * b % mod;
}
inline void adde(int &a,const int &b) {
    if( ( a += b ) >= mod ) a -= mod;
}

inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) ret = mul(ret,base);
        if( tim >>= 1 ) base = mul(base,base);
    }
    return ret;
}
inline void NTT(int* dst,int n,int tpe) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) std::swap(dst[i],dst[j]);
        for(int k=n>>1;(j^=k)<k;k>>=1);
    }
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) {
        int per = fastpow(g,mod/len);
        if( !~tpe ) per = fastpow(per,mod-2);
        for(int st=0;st<n;st+=len) {
            int w = 1;
            for(int pos=0;pos<h;pos++) {
                const int u = dst[st+pos] , v = mul(dst[st+pos+h],w);
                dst[st+pos] = add(u,v) , dst[st+pos+h] = sub(u,v) , w = mul(w,per);
            }
        }
    }
    if( !~tpe ) {
        const int inv = fastpow(n,mod-2);
        for(int i=0;i<n;i++) dst[i] = mul(dst[i],inv);
    }
}

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1],siz[maxn];
int n,q,su;

inline void coredge(int from,int to,int len) {
    static int cnt;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b,int l) {
    coredge(a,b,l) , coredge(b,a,l);
}
inline void dfs(int pos,int fa) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
        dfs(t[at],pos) , siz[pos] += siz[t[at]];
        adde(a[siz[t[at]]],mul(fac[siz[t[at]]],l[at])) , adde(a[n-siz[t[at]]],mul(fac[n-siz[t[at]]],l[at]));
    }
}

inline void preans() {
    int len;
    for(len=1;len<=n<<1;len<<=1);
    for(int i=0;i<=n;i++) b[n-i] = inv[i];
    NTT(a,len,1) , NTT(b,len,1);
    for(int i=0;i<len;i++) ans[i] = mul(a[i],b[i]);
    NTT(ans,len,-1);
}
inline int c(int n,int m) {
    return mul(fac[n],mul(inv[m],inv[n-m]));
}
inline int getans(int k) {
    if( k == 1 ) return 0;
    int fs = c(n,k) , sb = mul(ans[n+k],inv[k]) , sum = mul(fs,su);
    return mul(sub(sum,sb),fastpow(fs,mod-2));
}

inline void init() {
    *fac = 1;
    for(int i=1;i<=n;i++) fac[i] = mul(fac[i-1],i);
    inv[n] = fastpow(fac[n],mod-2);
    for(int i=n;i;i--) inv[i-1] = mul(inv[i],i);
}

int main() {
    scanf("%d%d",&n,&q) , init();
    for(int i=1,a,b,l;i<n;i++) scanf("%d%d%d",&a,&b,&l) , addedge(a,b,l<<1) , adde(su,l<<1);
    dfs(1,-1) , preans();
    for(int i=1,k;i<=q;i++) scanf("%d",&k) , printf("%d\n",getans(k));
    return 0;
}
