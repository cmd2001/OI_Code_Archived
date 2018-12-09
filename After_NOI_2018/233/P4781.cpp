#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn = 2e3 + 1e2;
const int mod = 998244353;

int x[maxn],y[maxn],inv[maxn],n;

inline int sub(const int &x,const int &y) {
    const int ret = x - y;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &dst,const int &x) {
    if((dst += x) >= mod) dst -= mod;
}
inline void mule(int &dst,const int &x) {
    dst = (lli) dst * x % mod;
}

inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if(tim & 1) mule(ret,base);
        if(tim >>= 1) mule(base,base);
    }
    return ret;
}

inline int calc(int t) {
    for(int i=1;i<=n;i++) if(x[i] == t) return y[i];
    int pi = 1, ret = 0;
    for(int i=1;i<=n;i++) mule(pi,sub(t,x[i]));
    for(int i=1;i<=n;i++) adde(ret,mul(y[i],mul(mul(pi,fastpow(sub(t,x[i]),mod-2)),inv[i])));
    return ret;
}

inline void init() {
    for(int i=1;i<=n;i++) {
        inv[i] = 1;
        for(int j=1;j<=n;j++) if(i != j) mule(inv[i],sub(x[i],x[j]));
        inv[i] = fastpow(inv[i],mod-2);
    }
    //for(int i=1;i<=n;i++) debug << pi[i] << " "; debug << endl;
}

int main() {
    static int t;
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;i++) scanf("%d%d",x+i,y+i);
    return init(), printf("%d\n",calc(t)), 0;
}
