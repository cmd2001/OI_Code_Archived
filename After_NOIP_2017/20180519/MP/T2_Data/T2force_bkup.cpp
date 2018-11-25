#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long int lli;
const int maxn=1e4+1e2;
const int mod=1e9+9;

struct Equation {
    lli k,b;
    friend Equation operator + (const Equation &a,const lli &b) {
        return (Equation){a.k,(a.b+b)%mod};
    }
    friend Equation operator - (const Equation &a,const lli &b) {
        return (Equation){a.k,(a.b-b+mod)%mod};
    }
    friend Equation operator * (const Equation &a,const lli &b) {
        return (Equation){a.k*b%mod,a.b*b%mod};
    }
    friend Equation operator + (const Equation &a,const Equation &b) {
        return (Equation){(a.k+b.k)%mod,(a.b+b.b)%mod};
    }
    friend Equation operator - (const Equation &a,const Equation &b) {
        return (Equation){(a.k-b.k+mod)%mod,(a.b-b.b+mod)%mod};
    }
}f[maxn],s[maxn];

lli c[maxn],inv[maxn];
int n;

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
inline void trans(int i) {
    Equation &su = s[i+1];
    f[i] = f[i+1] * c[i+1] - su * ( ( c[i+1] - 1 ) * inv[n-i] % mod ) - c[i+1];
    s[i] = s[i+1] + f[i];
}
inline lli solve(const Equation &e) {
    return (mod-e.b) * fastpow(e.k,mod-2) % mod;
}
inline void fix(int t) {
    for(int i=t-1;~i;i--) trans(i);
}

int main() {
    static int m;
    scanf("%d%d",&n,&m) , s[n] = f[n] = (Equation){1,0};
    for(int i=1;i<=n;i++) scanf("%lld",c+i);
    inv[1] = 1; for(int i=2;i<=n;i++) inv[i] = ( mod - mod / i ) * inv[mod%i] % mod;
    fix(n);
    for(int i=1,o,p;i<=m;i++) {
        scanf("%d%d",&o,&p);
        if( o == 1 ) printf("%lld\n",solve(f[p]));
        else scanf("%lld",c+p) , fix(p);
    }
    return 0;
}
