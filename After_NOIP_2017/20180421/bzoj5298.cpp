#include<cstdio>
#include<cstring>
typedef unsigned long long int ulli;
const int maxn=185;
// Compilation technology is well developed and we don't need to support it.
// There is a lack of system resources so we need to do optimization.

unsigned n,a,b,mod,len,sum,delta;
unsigned c[maxn][maxn];

struct Matrix {
    ulli dat[maxn][maxn];
    Matrix() { memset(dat,0,sizeof(dat)); }
    ulli* operator [] (const unsigned &x) { return dat[x]; }
    const ulli* operator [] (const unsigned &x) const { return dat[x]; }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(unsigned i=0;i<len;i++) for(unsigned k=0;k<len;k++) {
            const ulli t = a[i][k];
            for(unsigned j=0;j<len;j++) ret[i][j] += t * b[k][j];
        }
        for(unsigned i=0;i<len;i++) for(unsigned j=0;j<len;j++) ret[i][j] %= mod;
        return ret;
    }
}ans,base;

inline void fastpow(Matrix &ans,Matrix &base,unsigned tim) {
    while( tim ) {
        if( tim & 1 ) ans = ans * base;
        if( tim >>= 1 ) base = base * base;
    }
}
inline void initc() {
    c[0][0] = 1;
    for(unsigned i=1;i<=a+b;i++) {
        c[i][0] = 1;
        for(unsigned j=1;j<=i;j++) c[i][j] = ( c[i-1][j-1] + c[i-1][j] ) % mod;
    }
}
inline void initmatrix() {
    ans[0][0] = 1;
    for(int i=0;i<=a+b;i++) for(int k=0;k<=i;k++) base[k+delta][i] = base[k][i] = c[i][k];
    for(int i=0;i<=a+b;i++) base[i][i+delta] = 1;
}

int main() {
    scanf("%u%u%u%u",&n,&a,&b,&mod) , len = ( delta = ( a + b + 1 ) ) << 1 ,
    initc() , initmatrix();
    fastpow(ans,base,n);
    for(unsigned i=0,pn=1,pls;i<=b;i++,pn=(ulli)pn*n%mod) {
        pls = ( ans[0][a+b-i] + ans[0][a+b-i+delta] ) % mod;
        pls = (ulli) c[b][i] * pls % mod * pn % mod;
        if( ( b - i ) & 1 ) pls = mod - pls;
        sum = ( sum + pls ) % mod;
    }
    printf("%u\n",sum);
    return 0;
}
