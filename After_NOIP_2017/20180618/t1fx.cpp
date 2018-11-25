#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=8,maxm=5e6+1e2;
const int mod=1e9+7;

inline int add(const int &x,const int &y) {
    const int ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline int sub(const int &x,const int &y) {
    const int ret = x - y;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}
inline void sube(int &dst,const int &x) {
    if( ( dst -= x ) < 0 ) dst += mod;
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

char in[maxm];
int n,m,k,t,R;
struct Matrix { // dat[1][i] means i number all same with R .
    int dat[maxn][maxn];
    Matrix(int tpe=0) {
        memset(dat,0,sizeof(dat));
        for(int i=0;i<=n;i++) dat[i][i] = tpe;
    }
    int* operator [] (const int &x) { return dat[x]; }
    const int* operator [] (const int &x) const { return dat[x]; }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) for(int k=0;k<=n;k++) adde(ret[i][j],mul(a[i][k],b[k][j]));
        return ret;
    }
    friend Matrix operator + (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) ret[i][j] = add(a[i][j],b[i][j]);
        return ret;
    }
}trans[maxn][2],f[maxn];
int g[maxn],fac[maxn],inv[maxn],lam[maxn][maxn],sel[maxn<<1];
int tab[1<<7];

inline int countbit(int x) {
    return tab[x];
}
inline int c(int n,int m) {
    return mul(fac[n],mul(inv[m],inv[n-m]));
}
inline void getrans(int n) {
    // get trans 0 .
    for(int same=0;same<=n;same++) {
        const int different = n - same;
        for(int different_select=0;different_select<=different;different_select++)
            if( ! ( different_select & 1 ) ) {
                adde(trans[n][0][same][same],c(different,different_select));
            }
    }
    // get trans 1 .
    for(int same=0;same<=n;same++) {
        const int different = n - same;
        for(int same_select=0;same_select<=same;same_select++)
            for(int different_select=0;different_select<=different;different_select++)
                if( ! ( ( same_select + different_select ) & 1 ) ) {
                    adde(trans[n][1][same][same_select],mul(c(same,same_select),c(different,different_select)));
                }
    }
}

inline Matrix fastpow(Matrix base,int tim) {
    Matrix ret(1);
    while(tim) {
        if( tim & 1 ) ret = ret * base;
        if( tim >>= 1 ) base = base * base;
    }
    return ret;
}
inline void getans() {
    for(int i=1;i<=n;i++) f[i][0][i] = 1;
    for(int j=1;j<=n;j++) {
        Matrix cur(1);
        for(int i=1;i<=t;i++) cur = cur * trans[j][(int)in[i]-'0'];
        f[j] = f[j] * fastpow(cur,m/t);
    }
    g[0] = 1;
    for(int i=1;i<=n;i++) g[i] = f[i][0][0];
    for(int i=1;i<=n;i++) if( ( i & 1 ) == ( n & 1 ) ) {
        for(int j=i&1;j<i;j+=2) sube(g[i],mul(g[j],lam[i][j]));
        mule(g[i],inv[i]);
    }
}

inline int getpir(int used,int ned) {
    int base = sub(R,used) , ret = 1;
    for(int i=1;i<=ned;i++) mule(ret,base) , sube(base,1);
    return mul(ret,inv[ned]);
}
inline void calc(int pos,int fs,int su) {
    if( pos < fs ) return;
    int ret = mul(getpir(fs,pos-fs-1),fac[su]);
    for(int i=1;i<pos;i++) mule(ret,inv[sel[i]]);
    adde(lam[su][fs],ret);
}
inline void dfs_lam(int pos,int rem,int fs,int su) {
    if(!rem) return calc(pos,fs,su);
    for(int i=1+(pos>fs);i<=rem;i+=2) sel[pos] = i , dfs_lam(pos+1,rem-i,fs,su);
}

inline void pre_lam() {
    *fac = 1;
    for(int i=1;i<=n;i++) fac[i] = mul(fac[i-1],i);
    inv[n] = fastpow(fac[n],mod-2);
    for(int i=n;i;i--) inv[i-1] = mul(inv[i],i);
    for(int i=1;i<=m;i++) adde(R,R) , adde(R,in[i]-'0');
    for(int i=1;i<=n;i++) if( ( i & 1 ) == ( n & 1 ) ) for(int j=i&1;j<i;j+=2) dfs_lam(1,i,j,i);
}

int main() {
    scanf("%d%d%s",&n,&k,in+1) , t = m = strlen(in+1);
    for(int i=1;i<1<<n;i++) tab[i] = tab[i>>1] + (i&1);
    for(int j=1;j<=m;j++) for(int i=1;i<k;i++) in[i*m+j] = in[j];
    m *= k , pre_lam();
    for(int i=1;i<=n;i++) if( ( i & 1 ) == ( n & 1 ) ) getrans(i);
    getans() , printf("%d\n",g[n]);
    return 0;
}

