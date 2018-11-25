#include<cstdio>
#include<cstring>
typedef unsigned long long int ulli;
const ulli mod=1125899839733759ull,phi=1125899839733758ull;

inline ulli mul(ulli a,ulli b,const ulli &mod) {
    ulli ret = 0;
    while(b) {
        if( b & 1 ) ret = ( ret + a ) % mod;
        if( b >>= 1 ) a = ( a + a ) % mod;
    }
    return ret;
}

struct Matrix {
    ulli dat[2][2];
    ulli* operator [] (const int &x) { return dat[x]; }
    const ulli* operator [] (const int &x) const { return dat[x]; }
    Matrix(int tpe=0) { memset(dat,0,sizeof(dat)) , dat[0][0] = dat[1][1] = tpe; }
}base,trans,ans;

inline Matrix mul(const Matrix &a,const Matrix &b,const ulli &mod) {
    Matrix ret;
    for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++) ret[i][j] = ( ret[i][j] + mul(a[i][k],b[k][j],mod) ) % mod;
    return ret;
}

ulli fastpow(ulli base,ulli tim,const ulli &mod) {
    ulli ret(1);
    while(tim) {
        if( tim & 1 ) ret = mul(ret,base,mod);
        if( tim >>= 1 ) base = mul(base,base,mod);
    }
    return ret;
}
Matrix fastpow(Matrix base,ulli tim,const ulli &mod) {
    Matrix ret(1);
    while(tim) {
        if( tim & 1 ) ret = mul(ret,base,mod);
        if( tim >>= 1 ) base = mul(base,base,mod);
    }
    return ret;
}

int main() {
    static int T;
    static ulli n;
    scanf("%d",&T);
    while(T--) {
        scanf("%llu",&n) , base[0][1] = trans[0][1] = trans[1][0] = trans[1][1] = 1;
        ans = mul(base,fastpow(trans,fastpow(2,n,phi),mod),mod) , printf("%llu\n",ans[0][0]);
    }
    return 0;
}
