#include<cstdio>
#include<cstring>
const int maxn=1e2+1e1,mod=30011;

int n,len,m,ans;

struct Matrix {
    int dat[maxn][maxn];
    int* operator [] (const int &x) { return dat[x]; }
    const int* operator [] (const int &x) const { return dat[x]; }
    Matrix(int tpe=0) { memset(dat,0,sizeof(dat)); for(int i=1;i<=len;i++) dat[i][i] = tpe; }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=1;i<=len;i++) for(int j=1;j<=len;j++) for(int k=1;k<=len;k++) {
            ( ret[i][j] += a[i][k] * b[k][j] % mod ) %= mod;
        }
        return ret;
    }
}ini,trans,add,sub;

inline Matrix fastpow(Matrix base,int tim) {
    Matrix ret(1);
    while(tim) {
        if( tim & 1 ) ret = ret * base;
        if( tim >>= 1 ) base = base * base;
    }
    return ret;
}
inline Matrix calc(int step) {
    Matrix ret = ini * fastpow(trans,(step>>1)<<1);
    if( step & 1 ) ret = ret * trans;
    return ret;
}

int main() {
    scanf("%d%d",&n,&m) , len = n << 1;
    if( m <= 2 ) return printf("%d\n",n<=m),0;
    for(int i=1;i<=n;i++) {
        trans[i+n][i] = trans[i][i+n] = 1;
        if( i + 1 <= n ) trans[n+i+1][n+i] = 1;
        if( i - 1 >= 1 ) trans[n+i-1][n+i] = 1;
        trans[n+i][n+i] = 1;
    }
    ini[1][n+1] = 1 , printf("%d\n",(calc(m-1)[1][len]-calc(m-3)[1][len]+mod)%mod);
    return 0;
}
