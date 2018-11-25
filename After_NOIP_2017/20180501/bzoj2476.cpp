#include<cstdio>
#include<cstring>
typedef long long int lli;
const int mod=987654321;

struct Matrix {
    lli dat[2][2];
    Matrix(int tpe=0) { memset(dat,0,sizeof(dat)); for(int i=0;i<2;i++) dat[i][i] = tpe; }
    lli* operator [] (const int &x) { return dat[x]; }
    const lli* operator [] (const int &x) const { return dat[x]; }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++) ret[i][j] = ( ret[i][j] + a[i][k] * b[k][j] % mod ) % mod;
        return ret;
    }
}trans,ini;

inline Matrix fastpow(Matrix base,int tim) {
    Matrix ret(1);
    while(tim) {
        if( tim & 1 ) ret = ret * base;
        if( tim >>= 1 ) base = base * base;
    }
    return ret;
}

int main() {
    static int p;
    ini[0][0] = ini[0][1] = 1 , trans[1][0] = 1 , trans[0][1] = mod - 1 , trans[1][1] = 3;
    while( scanf("%d",&p) == 1 && p ) {
        if( p & 1 || p < 8 ) puts("0");
        else p>>=1 , printf("%lld\n",((ini*fastpow(trans,p-1)).dat[0][0]-(p-1)+mod)%mod);
    }
    return 0;
}

