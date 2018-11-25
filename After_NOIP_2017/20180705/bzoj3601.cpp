#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxw=1e3+1e2,maxt=2e2+1e1;
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

struct Poly {
    int dat[maxt],len;
    Poly() { memset(dat,0,sizeof(dat)) , len = 0; }
    Poly(int x) { memset(dat,0,sizeof(dat)) , len = 1 , *dat = x; }
    Poly(int k,int b) { memset(dat,0,sizeof(dat)) , len = 2 , dat[0] = b , dat[1] = k; }
    int& operator [] (const int &x) { return dat[x]; }
    const int& operator [] (const int &x) const { return dat[x]; }
    friend Poly operator + (const Poly &a,const Poly &b) {
        Poly ret; ret.len = max( a.len , b.len );
        for(int i=0;i<ret.len;i++) ret[i] = add(a[i],b[i]);
        return ret;
    }
    friend Poly operator * (const Poly &a,const int &x) {
        Poly ret = a;
        for(int i=0;i<ret.len;i++) mule(ret[i],x);
        return ret;
    }
    friend Poly operator * (const Poly &a,const Poly &b) {
        Poly ret; ret.len = a.len + b.len - 1;
        for(int i=0;i<a.len;i++) for(int j=0;j<b.len;j++) adde(ret[i+j],mul(a[i],b[j]));
        return ret;
    }
    inline int calc(int x) const {
        int ret = 0 , mu = 1;
        for(int i=0;i<=len;i++) adde(ret,mul(mu,dat[i])) , mule(mu,x);
        return ret;
    }
}way;

struct Inter {
    int xs[maxt],ys[maxt],siz;
    Poly prf[maxt],suf[maxt];
    inline void insert(int xx,int yy) {
        xs[++siz] = xx , ys[siz] = yy;
    }
    inline Poly calc() {
        for(int i=1,pi=1;i<=siz;i++,pi=1) {
            for(int j=1;j<=siz;j++) if( j != i ) mule(pi,fastpow(sub(xs[i],xs[j]),mod-2));
            mule(ys[i],pi);
        }
        prf[0] = suf[siz+1] = Poly(1);
        for(int i=1;i<=siz;i++) prf[i] = prf[i-1] * Poly(1,sub(0,xs[i]));
        for(int i=siz;i;i--) suf[i] = suf[i+1] * Poly(1,sub(0,xs[i]));
        Poly ret;
        for(int i=1;i<=siz;i++) ret = ret + prf[i-1] * suf[i+1] * ys[i];
        return ret;
    }
}inter;

int p[maxw],k[maxw],d,w,ans;

int main() {
    scanf("%d%d",&d,&w);
    for(int i=1;i<=w;i++) scanf("%d%d",p+i,k+i);
    for(int i=0,su=0;i<=d+2;i++) adde(su,fastpow(i,d)) , inter.insert(i,su);
    way = inter.calc();
    for(int i=0,pi=1;i<=d+1;i++,pi=1) {
        for(int x=1;x<=w;x++) mule(pi,mul(fastpow(p[x],(lli)k[x]*i%(mod-1)),sub(1,fastpow(p[x],d-i+mod-1))));
        adde(ans,mul(pi,way[i]));
    }
    printf("%d\n",ans);
    return 0;
}
