#include<cstdio>
#define lli long long int

lli mod;
struct Moding_Int {
    lli d;
    friend Moding_Int operator + (const Moding_Int &a,const Moding_Int &b) { return (Moding_Int){(a.d+b.d)%mod}; }
    friend Moding_Int operator - (const Moding_Int &a,const Moding_Int &b) { return (Moding_Int){(a.d-b.d+mod)%mod}; };
    friend Moding_Int operator * (const Moding_Int &a,const Moding_Int &b) { return (Moding_Int){a.d*b.d%mod}; }
    Moding_Int() {}
    Moding_Int(lli t) { d = mod ? t % mod : t; };
}nn,mm,kk,ans;

inline Moding_Int fastpow(Moding_Int base,lli tim) {
    Moding_Int ret(1);
    while(tim) {
        if( tim & 1 ) ret = ret * base;
        if( tim >>= 1 ) base = base * base;
    }
    return ret;
}

int main() {
    static lli n,k,m;
    scanf("%lld%lld%lld%lld",&n,&k,&m,&mod) , nn = Moding_Int(n) , mm = Moding_Int(m) , kk = Moding_Int(k-1);
    ans = fastpow(mm,k-2) * ( nn * mm - Moding_Int( ( m * ( m + 1 ) ) >> 1 ) * kk );
    printf("%lld\n",ans.d);
    return 0;
}
