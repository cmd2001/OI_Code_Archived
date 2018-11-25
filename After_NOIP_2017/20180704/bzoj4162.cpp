#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=55,maxl=1e5+1e2;
const int mod = 1e9+7;

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

int n;

struct Matrix {
    int dat[maxn][maxn];
    Matrix() { memset(dat,0,sizeof(dat)); }
    int* operator [] (const int &x) { return dat[x]; }
    const int* operator [] (const int &x) const { return dat[x]; }
    friend Matrix operator + (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) ret[i][j] = add(a[i][j],b[i][j]);
        return ret;
    }
    friend Matrix operator - (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) ret[i][j] = sub(a[i][j],b[i][j]);
        return ret;
    }
    friend Matrix operator * (const Matrix &a,const int &x) {
        Matrix ret;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) ret[i][j] = mul(a[i][j],x);
        return ret;
    }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) for(int k=1;k<=n;k++) adde(ret[i][j],mul(a[i][k],b[k][j]));
        return ret;
    }
    inline void print() const {
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) printf("%d%c",dat[i][j],j!=n?' ':'\n');
    }
}in,ini,su;

inline int gauss(Matrix dat) {
    int ret = 1;
    for(int i=1,pos=-1;i<=n;i++,pos=-1) {
        for(int j=i;j<=n;j++) if( dat[j][i] ) { pos = j; break; }
        if( !~pos ) return 0;
        if( i != pos ) {
            for(int k=1;k<=n;k++) swap(dat[i][k],dat[pos][k]);
            ret = sub(0,ret) , pos = i;
        }
        const int inv = fastpow(dat[i][i],mod-2); mule(ret,dat[i][i]);
        for(int k=1;k<=n;k++) mule(dat[i][k],inv);
        for(int j=1;j<=n;j++) if( i != j && dat[j][i] ) {
            const int mu = dat[j][i];
            for(int k=1;k<=n;k++) sube(dat[j][k],mul(dat[i][k],mu));
        }
    }
    return ret;
}

struct Poly {
    int dat[maxn<<1],len;
    Poly() { memset(dat,0,sizeof(dat)) , len = 0; }
    Poly(int k,int b) { memset(dat,0,sizeof(dat)) , len = 2 , dat[0] = b , dat[1] = k; }
    int& operator [] (const int &x) { return dat[x]; }
    const int& operator [] (const int &x) const { return dat[x]; }
    friend Poly operator + (const Poly &a,const Poly &b) {
        Poly ret; ret.len = max(a.len,b.len);
        for(int i=0;i<ret.len;i++) ret[i] = add(a[i],b[i]);
        return ret;
    }
    friend Poly operator * (const Poly &a,const Poly &b) {
        Poly ret; ret.len = a.len + b.len;
        for(int i=0;i<a.len;i++) for(int j=0;j<b.len;j++) adde(ret[i+j],mul(a[i],b[j]));
        while( ret.len && !ret[ret.len-1] ) --ret.len;
        return ret;
    }
    friend Poly operator * (const Poly &a,const int &x) {
        Poly ret = a;
        for(int i=0;i<ret.len;i++) mule(ret[i],x);
        return ret;
    }
    friend Poly operator % (const Poly &a,const Poly &b) {
        Poly ret = a; const int inv = fastpow(b[b.len-1],mod-2);
        for(int i=a.len;i>=b.len-1;i--) {
            const int mu = mul(ret.dat[i],inv);
            for(int j=0;j<b.len;j++) sube(ret.dat[i-j],mul(b.dat[b.len-1-j],mu));
        }
        while( ret.len && !ret[ret.len-1] ) --ret.len;
        return ret;
    }
}ans,spe;

struct Interval {
    int xs[maxn],ys[maxn],siz;
    Poly prf[maxn],suf[maxn];
    inline void insert(int x,int y) {
        xs[++siz] = x , ys[siz] = y;
    }
    inline Poly calc() {
        for(int i=1,pi=1;i<=siz;i++,pi=1) {
            for(int j=1;j<=siz;j++) if( i != j ) mule(pi,sub(xs[i],xs[j]));
            mule(ys[i],fastpow(pi,mod-2));
        }
        prf[0] = suf[siz+1] = Poly(0,1);
        for(int i=1;i<=siz;i++) prf[i] = prf[i-1] * Poly(1,sub(0,xs[i]));
        for(int i=siz;i;i--) suf[i] = suf[i+1] * Poly(1,sub(0,xs[i]));
        Poly ret;
        for(int i=1;i<=siz;i++) ret = ret + prf[i-1] * suf[i+1] * ys[i];
        return ret;
    }
}inter;

inline Poly fastpow(Poly base,const Poly &mod,char* s,int li) {
    Poly ret(0,1);
    for(int i=1;i<=li;i++) {
        if( s[i] - '0' ) ret = ret * base % mod;
        if( i != li ) base = base * base % mod;
    }
    return ret;
}

char s[maxl];
int li;

int main() {
    scanf("%s%d",s+1,&n) , reverse(s+1,s+1+(li=strlen(s+1)));
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",in[i]+j);
    for(int i=1;i<=n;i++) ini[i][i] = 1;
    for(int i=1;i<=n+1;i++) inter.insert(i,gauss(in-ini*i));
    spe = inter.calc() , ans = fastpow(Poly(1,0),spe,s,li);
    for(int i=0;i<n;i++) su = su + ini * ans[i] , ini = ini * in;
    su.print();
    return 0;
}
