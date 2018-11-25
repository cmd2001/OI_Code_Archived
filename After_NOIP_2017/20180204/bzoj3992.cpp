#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=16385;
const int mod=1004535809,g=3;

int ss[maxn];
lli in[maxn];
int m,s;

/*inline lli mul(lli x,lli y,lli mod) {
    x %= mod , y %= mod;
    lli ret = 0;
    while( y ) {
        if( y & 1 ) ret = ( ret + x ) % mod;
        if( y >>= 1 ) x = ( x << 1 ) % mod;
    }
    return ret;
}*/
inline lli mul(lli x,lli y,lli mod) {
    //return ( x * y - (lli)( (long double) x / mod * y ) * mod + mod ) % mod;
    return x * y % mod;
}
inline lli fastpow(lli base,lli tim,lli mod) {
    lli ret = 1;
    while( tim ) {
        if( tim & 1 ) ret = mul( ret , base , mod );
        if( tim >>= 1 ) base = mul( base , base , mod );
    }
    return ret;
}
inline void NTT(lli* dst,int n,int ope) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) swap( dst[i] , dst[j] );
        for(int t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(int len=2;len<=n;len<<=1) {
        const int h = len >> 1;
        lli per = fastpow(g,mod/len,mod);
        if( !~ope ) per = fastpow(per,mod-2,mod);
        for(int st=0;st<n;st+=len) {
            lli w = 1;
            for(int pos=0;pos<h;pos++) {
                const lli u = dst[st+pos] , v = mul(dst[st+pos+h],w,mod);
                dst[st+pos] = ( u + v ) % mod;
                dst[st+pos+h] = ( u - v + mod ) % mod;
                w = mul(w,per,mod);
            }
        }
    }
    if( !~ope ) {
        lli inv = fastpow(n,mod-2,mod);
        for(int i=0;i<n;i++)
            dst[i] = mul(dst[i],inv,mod);
    }
}
struct Seqence {
    lli dat[maxn],len;
    Seqence(int t=0) {
        memset(dat,0,sizeof(dat)) , len = 0;
        if( t ) *dat = 1;
    }
    friend Seqence operator * (Seqence a,Seqence b) {
        Seqence ret;
        int len = max( a.len , b.len );
        NTT(a.dat,len,1) , NTT(b.dat,len,1);
        for(int i=0;i<len;i++)
            ret.dat[i] = mul(a.dat[i],b.dat[i],mod);
        NTT(ret.dat,ret.len=len,-1);
        for(int i=0;i<len;i++)
            if( i >= m - 1 )
                ret.dat[i%(m-1)] = ( ret.dat[i%(m-1)] + ret.dat[i] ) % mod ,
                ret.dat[i] = 0;
        return ret;
    }
    inline void input(lli* sou,int ll) {
        len = ll;
        memcpy(dat,sou,sizeof(lli)*len);
    }
    void print() {
        for(int i=0;i<len;i++) debug<<dat[i]<<" ";debug<<endl;
    }
}ini,ans;
inline Seqence fastpow(Seqence base,int tim) {
    Seqence ret(1);
    while( tim ) {
        if( tim & 1 ) ret = ret * base;
        if( tim >>= 1 ) base = base * base;
    }
    return ret;
}
namespace Convert {
    int pows[maxn],dvs[maxn],len;
    
    inline int fastpow(int base,int tim,int mod) {
        int ret = 1;
        while( tim ) {
            if( tim & 1 ) ret = ret * base % mod;
            if( tim >>= 1 ) base = base * base % mod;
        }
        return ret;
    }
    inline bool judge(int t) {
        for(int i=1;i<=len;i++)
            if( fastpow(t,(m-1)/dvs[i],m) == 1 ) return 0;
        return 1;
    }
    inline int findrt() {
        for(int i=2;i<m;i++)
            if( judge(i) ) return i;
        debug<<"There is no primary root!"<<endl;
        exit(0);
    }
    inline void cut(int x) {
        for(int i=2;i*i<=x;i++)
            if( ! ( x % i ) ) {
                dvs[++len] = i;
                while( ! ( x % i ) ) x /= i;
            }
    }
    inline void work() {
        cut(m-1);
        int rt = findrt();
        for(int i=0,now=1;i<m-1;i++,now=now*rt%m)
            pows[now] = i;
        for(int i=1;i<=s;i++)
            if( ss[i] )
                in[pows[ss[i]]]++;
    }
}

int main() {
    static int n,x,len=1;
    scanf("%d%d%d%d",&n,&m,&x,&s);
    for(int i=1;i<=s;i++) scanf("%d",ss+i) , ss[i] %= m;
    Convert::work();
    while( len < 2 * ( m - 1 ) + 1 ) len <<= 1;
    ini.input(in,len);
    ans = fastpow(ini,n);
    x = Convert::pows[x];
    printf("%lld\n",ans.dat[x]);
    return 0;
}



