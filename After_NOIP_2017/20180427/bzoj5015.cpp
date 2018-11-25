#include<cstdio>
#include<cstring>
typedef long long int lli;
const int maxn=15,mod=1e9+7;

lli c[maxn][maxn];
int k,len;

struct Matrix {
    lli dat[maxn][maxn];
    Matrix(int tpe=0) { memset(dat,0,sizeof(dat)); for(int i=0;i<=len;i++) dat[i][i] = tpe; }
    lli* operator [] (const int &x) { return dat[x]; }
    const lli* operator [] (const int &x) const { return dat[x]; }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=0;i<=len;i++) for(int k=0;k<=len;k++) for(int j=0;j<=len;j++) ( ret[i][j] += a[i][k] * b[k][j] % mod ) %= mod;
        return ret;
    }
}ini,trans,tp;

inline Matrix fastpow(Matrix base,lli tim) {
    Matrix ret(1);
    while( tim ) {
        if( tim & 1 ) ret = ret * base;
        if( tim >>= 1 ) base = base * base;
    }
    return ret;
}
inline void gen() {
    c[0][0] = 1;
    for(int i=1;i<=k;i++) {
        c[i][0] = 1;
        for(int j=1;j<=i;j++) c[i][j] = ( c[i-1][j-1] + c[i-1][j] ) % mod;
    }
    len = k + 1;
    for(int i=0;i<=k;i++) for(int j=0;j<=i;j++) trans[j][i] = c[i][j];
    trans[len][len] = 2 ; for(int j=0;j<=k;j++) trans[j][len] = c[k][j];
    ini[0][0] = 1;
}

int main() {
    static lli n;
    scanf("%lld%d",&n,&k) , gen();
    printf("%lld\n",((ini*fastpow(trans,n))[0][len] - (ini*fastpow(trans,n-1))[0][len] + mod ) % mod);
    return 0;
}

