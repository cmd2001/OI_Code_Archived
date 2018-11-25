#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<tr1/unordered_map>
#define debug cout
typedef long long int lli;
using namespace std;
using namespace tr1;
const int maxn=5e6+1e2,lim=5e6,maxk=1e3+1e2;
const int mod=1e9+9;

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

int phi[maxn],su[maxn],suk[maxn],susk[maxn];
int fac[maxk],refac[maxk];
int n,k; // judge k == 0 .

struct Interval {
    int dat[maxk],siz,*pre;
    unordered_map<int,int> mem;
    int& operator [] (const int &x) { return dat[x]; }
    inline void init(const int &ss,int* pp) {
        siz = ss , pre = pp;
        for(int i=0;i<siz;i++) mule(dat[i],fastpow(mul(fac[i],refac[siz-i-1]),mod-2));
    }
    inline int calc(int x) {
        if( x <= lim ) return pre[x];
        if( mem.find(x) != mem.end() ) return mem[x];
        int pi = 1 , ret = 0;
        for(int i=0;i<siz;i++) mule(pi,sub(x,i));
        for(int i=0,t;i<siz;i++) t = mul(pi,fastpow(sub(x,i),mod-2)) , adde(ret,mul(t,dat[i]));
        return mem[x] = ret;
    }
}ik,isk;

inline int calc(int x) {
    static int mem[maxn];
    static bool vis[maxn];
    if( x <= lim ) return su[x];
    if( vis[n/x] ) return mem[n/x];
    int &ret = mem[n/x]; vis[n/x] = 1 , ret = ik.calc(x);
    for(int i=2,j;i<=x;i=j+1) j = x / ( x / i ) , sube(ret,mul(sub(isk.calc(j),isk.calc(i-1)),calc(x/i)));
    return ret;
}

inline void sieve() {
    static int prime[maxn],cnt;
    static bool vis[maxn];
    phi[1] = su[1] = suk[1] = susk[1] = 1;
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i , phi[i] = i - 1 , suk[i] = mul(susk[i]=fastpow(i,k-1),i);
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
            const int tar = i * prime[j];
            vis[tar] = 1 , suk[tar] = mul(suk[i],suk[prime[j]]) , susk[tar] = mul(susk[i],susk[prime[j]]);
            if( i % prime[j] ) phi[tar] = phi[i] * ( prime[j] - 1 );
            else { phi[tar] = phi[i] * prime[j]; break; }
        }
    }
    *fac = *refac = 1;
    for(int i=1;i<=k+1;i++) fac[i] = mul(fac[i-1],i) , refac[i] = mul(refac[i-1],sub(0,i));
    for(int i=1;i<=lim;i++) su[i] = add(su[i-1],mul(phi[i],susk[i])) , adde(suk[i],suk[i-1]) , adde(susk[i],susk[i-1]);
    for(int i=0;i<=k+1;i++) ik[i] = suk[i];
    for(int i=0;i<=k;i++) isk[i] = susk[i];
    ik.init(k+2,suk) , isk.init(k+1,susk);
}

int main() {
    scanf("%d%d",&n,&k);
    if( !k ) return printf("%d\n",n) , 0;
    sieve() , printf("%d\n",calc(n));
    return 0;
}

// Powered by <!-- ??? 世界第一的毒瘤殿下 ??? --!>

