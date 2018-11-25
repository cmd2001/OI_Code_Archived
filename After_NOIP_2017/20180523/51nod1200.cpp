#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long int lli;
const int maxn=131073;
const int mod=1e9+7,inv=(mod+1)>>1;

int f[maxn],n,m,len;

inline int add(const int &a,const int &b) {
    int ret = a + b;
    return ret >= mod ? ret - mod : ret;
}
inline int sub(const int &a,const int &b) {
    int ret = a + mod - b;
    return ret >= mod ? ret - mod : ret;
}
inline int mul(const int &a,const int &b) {
    return (lli) a * b % mod;
}

inline void FWT(int* dst,int n) {
    for(int len=2,h=1;len<=n;len<<=1,h<<=1)
        for(int st=0;st<n;st+=len)
            for(int pos=0;pos<h;pos++) {
                const int u = dst[st+pos] , v = dst[st+pos+h];
                dst[st+pos] = add(u,v) , dst[st+pos+h] = sub(u,v);
            }
}
inline void UFWT(int* dst,int n) {
    for(int len=2,h=1;len<=n;len<<=1,h<<=1)
        for(int st=0;st<n;st+=len)
            for(int pos=0;pos<h;pos++) {
                const int u = dst[st+pos] , v = dst[st+pos+h];
                dst[st+pos] = mul(add(u,v),inv) , dst[st+pos+h] = mul(sub(u,v),inv);
            }
}

inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) ret = mul(ret,base);
        if( tim >>= 1 ) base = mul(base,base);
    }
    return ret;
}

inline void sieve() {
    static int prime[maxn],cnt;
    static bool vis[maxn];
    for(int i=2;i<=m;i++) {
        if( !vis[i] ) f[prime[++cnt]=i]=1;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=m;j++) {
            vis[i*prime[j]] = 1;
            if( ! ( i % prime[j] ) ) break;
        }
    }
}

int main() {
    scanf("%d%d",&n,&m) , sieve();
    for(len=1;len<=m<<1;len<<=1) ;
    FWT(f,len);
    for(int i=0;i<len;i++) f[i] = fastpow(f[i],n);
    UFWT(f,len);
    printf("%d\n",*f);
    return 0;
}
