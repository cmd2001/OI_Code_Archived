#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
typedef unsigned int uint;
typedef unsigned long long int ulli;
const int maxn=1e5+1e2;
const uint mod=1e9+9;

inline uint add(const uint &x,const uint &y) {
    register uint ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline uint sub(const uint &x,const uint &y) {
    register uint ret = x + mod - y;
    return ret >= mod ?  ret - mod : ret;
}
inline uint mul(const uint &a,const uint &b) {
    return (ulli) a * b % mod;
}
inline uint fastpow(uint base,uint tim) {
    uint ret = 1;
    while(tim) {
        if( tim & 1 ) ret = mul(ret,base);
        if( tim >>= 1 ) base = mul(base,base);
    }
    return ret;
}

struct Matrix {
    uint dat[5][5];
    uint* operator [] (const uint &x) { return dat[x]; }
    const uint* operator [] (const uint &x) const { return dat[x]; }
    Matrix() { memset(dat,0,sizeof(dat)); }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(uint i=0;i<5;i++) for(uint k=0;k<5;k++) for(uint j=0;j<5;j++) ret[i][j] = add(ret[i][j],mul(a[i][k],b[k][j]));
        return ret;
    }
}ini,ans;

uint c[maxn],inv[maxn],n;

inline Matrix getrans(const uint &i) { // assert ci != 0 .
    Matrix ret;
    if( i == n ) return ret[0][0] = ret[0][2] = ret[0][4] = 1 , ret;
    ret[0][0] = ret[0][2] = ret[1][1] = ret[1][3] = c[i+1] , ret[4][1] = ret[4][3] = mod - c[i+1];
    ret[2][2] = ret[3][3] = add(1,ret[2][0]=ret[3][1]=mod-mul(c[i+1]-1,inv[n-i])) , ret[4][4] = 1;
    return ret;
}

struct SegmentTree { // warning :: multi from right to left .
    Matrix dat[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void build(int pos,int l,int r) { // l should starts from 0 because we need f[0] .
        if( l == r ) return void( dat[pos] = getrans(l) );
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r);
        dat[pos] = dat[rson(pos)] * dat[lson(pos)];
    }
    inline void update(int pos,int l,int r,const int &tar) {
        if( l == r ) return void(dat[pos] = getrans(tar));
        const int mid = ( l + r ) >> 1;
        tar <= mid ? update(lson(pos),l,mid,tar) : update(rson(pos),mid+1,r,tar);
        dat[pos] = dat[rson(pos)] * dat[lson(pos)];
    }
    inline Matrix query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return dat[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        return query(rson(pos),mid+1,r,ll,rr) * query(lson(pos),l,mid,ll,rr);
    }
}sgt;

inline uint calc(const Matrix &equ) {
    return mul(mod-equ[0][1],fastpow(equ[0][0],mod-2));
}

namespace FastIO {
    inline unsigned char nextchar() {
        static const int BS = 1 << 22;
        static unsigned char buf[BS],*st,*ed;
        if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
        return st == ed ? 0 : *st++;
    }
    inline uint getint() {
        uint ret = 0 , ch;
        while( !isdigit(ch=nextchar()) );
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
}
using FastIO::getint;


int main() {
   static uint m;
   n = getint() , m = getint();
   for(uint i=1;i<=n;i++) c[i] = getint();
   inv[1] = 1; for(uint i=2;i<=n;i++) inv[i] = mul(sub(mod,mod/i),inv[mod%i]);
   sgt.build(1,0,n);
   for(uint i=1,p,x;i<=m;i++) {
       if( getint() == 1 ) p = getint() , printf("%u\n",calc(sgt.query(1,0,n,p,n)));
       else p = getint() , x = getint() , c[p] = x , sgt.update(1,0,n,p-1);
   }
   return 0;
}

