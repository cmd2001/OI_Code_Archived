#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=16385;
const int mod=1004535809,g=3;

int in[maxn];
lli sou[maxn];
int n,m,x,s,len=1;

inline lli mul(lli a,lli b,lli mod) {
    lli ret = 0;
    a %= mod , b %= mod;
    while( b ) {
        if( b & 1 ) ret = ( ret + a ) % mod;
        if( b >>= 1 ) a = ( a << 1 ) % mod;
    }
    return ret;
}
inline lli fastpow(lli base,lli tme,lli mod) {
    lli ret = 1;
    while( tme ) {
        if( tme & 1 ) ret = mul(ret,base,mod);
        if( tme >>= 1 ) base = mul(base,base,mod);
    }
    return ret;
}
inline void NTT(lli* dst,int n,int ope) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) swap(dst[i],dst[j]);
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
                dst[st+pos] = ( u + v ) % mod ,
                dst[st+pos+h] = ( u - v + mod ) % mod ,
                w = mul( w , per , mod );
            }
        }
    }
    if( !~ope ) {
        lli inv = fastpow(n,mod-2,mod);
        for(int i=0;i<n;i++)
            dst[i] = mul( dst[i] , inv , mod );
    }
}
struct Seqence {
    lli dat[maxn],len;
    Seqence(int t = 0) {
        memset(dat,0,sizeof(dat)) , len = 0;
        if( t ) *dat = 1;
    }
    friend Seqence operator * (Seqence a,Seqence b) {
        Seqence ret;
        lli len = max( a.len , b.len );
        NTT(a.dat,len,1) , NTT(b.dat,len,1);
        for(int i=0;i<len;i++)
            ret.dat[i] = mul( a.dat[i] , b.dat[i] , mod );
        NTT(ret.dat,ret.len=len,-1);
        for(int i=0;i<len;i++)
            if( i > (m-1) ) {
                ret.dat[i%(m-1)] = ( ret.dat[i%(m-1)] + ret.dat[i] ) % mod ,
                ret.dat[i] = 0;
            }
        return ret;
    }
    inline void print() {
        for(int i=0;i<len;i++) debug<<dat[i]<<" ";debug<<endl;
    }
}ini,ans;

Seqence fastpow(Seqence base,int tme) {
    Seqence ret = Seqence(1);
    while( tme ) {
        if( tme & 1 ) ret = ret * base;
        if( tme>>= 1 ) base = base * base;
    }
    return ret;
}

namespace Convert {
    int primes[maxn],len;
    int pows[maxn],root; // convert pows into times
    inline int fastpow(int base,int tme,int mod) {
        int ret = 1;
        while( tme ) {
            if( tme & 1 ) ret = ret * base % mod;
            base = base * base % mod;
            tme >>= 1;
        }
        return ret;
    }
    inline bool judge(int x) {
        for(int i=1;i<=len;i++)
            if( fastpow(x,m/primes[i],m) == 1 ) return 0;
        return 1;
    }
    inline int findroot() {
        for(int i=2;i<m;i++)
            if( judge(i) ) return i;
        debug<<"Fuck you!"<<endl;
    }
    inline void cut(int x) {
        for(int i=2;i*i<=x;i++)
            if( ! ( x % i ) ) {
                primes[++len] = i;
                while( ! ( x % i ) ) x /= i;
            }
    }
    inline void work() {
        cut(m-1);
        int rt = findroot();
        //debug<<"root = "<<rt<<endl;
        for(int i=0,now=1;i<m-1;i++)
            pows[now] = i , now = now * rt % m;
        for(int i=1;i<=s;i++)
            ++sou[pows[in[i]]];
    }
}

int main() {
    scanf("%d%d%d%d",&n,&m,&x,&s);
    for(int i=1;i<=s;i++) scanf("%d",in+i);
    while( len < 2 * m ) len <<= 1;
    Convert::work();
    /*debug<<mul(2147483648ll,2147483648ll,mod)<<endl;
    for(int i=0;i<len;i++) debug<<sou[i]<<" ";debug<<endl;
    NTT(sou,len,1) , NTT(sou,len,-1);
    for(int i=0;i<len;i++) debug<<sou[i]<<" ";debug<<endl;*/
    memcpy(ini.dat,sou,sizeof(lli)*len) , ini.len = len;
    /*ini.print();
    ans = Seqence(1);
    ans = ans * ini;
    ans.print();*/
    //ans = fastpow(ini,n) , x = Convert::pows[x];
    ans = ( ini * ini ) * ( ini ) * ini;
    ans.print();
    ans = fastpow(ini,n);
    ans.print();
    debug<<"new x = "<<x<<endl;
    printf("%lld\n",ans.dat[x]);
    return 0;
}
