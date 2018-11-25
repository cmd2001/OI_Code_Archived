#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=65537,lim=5e4;
const int mod=1e9+7,inv=500000004;

inline int add(const int &a,const int &b) {
    int ret = a + b;
    return ret >= mod ? ret - mod : ret;
}
inline int sub(const int &a,const int &b) {
    int ret = a - b;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &a,const int &b) {
    return (lli) a * b % mod;
}
int prime[maxn],cnt,len;
int dat[maxn];

inline void FWT(int* dst,int n) {
    for(int len=2;len<=n;len<<=1) {
        const int h = len >> 1;
        for(int st=0;st<n;st+=len)
            for(int pos=0;pos<h;pos++) {
                const int u = dst[st+pos] , v = dst[st+pos+h];
                dst[st+pos] = add(u,v) , dst[st+pos+h] = sub(u,v);
            }
    }
}
inline void UFWT(int* dst,int n) {
    for(int len=2;len<=n;len<<=1) {
        const int h = len >> 1;
        for(int st=0;st<n;st+=len)
            for(int pos=0;pos<h;pos++) {
                const int u = dst[st+pos] , v = dst[st+pos+h];
                dst[st+pos] = mul(add(u,v),inv) ,  dst[st+pos+h] = mul(sub(u,v),inv);
            }
    }
}

inline void sieve() {
    static bool vis[maxn];
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            if( ! ( i % prime[j] ) ) break;
        }
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

int main() {
    static int n,m;
    sieve();
    while( scanf("%d%d",&n,&m) == 2 ) {
        for(len=1;len<=m;len<<=1) ;
        memset(dat,0,sizeof(int)*len);
        for(int i=1;i<=cnt;i++)
            if( prime[i] <= m ) dat[prime[i]] = 1;
            else break;
        FWT(dat,len);
        for(int i=0;i<len;i++) dat[i] = fastpow(dat[i],n);
        UFWT(dat,len);
        printf("%d\n",dat[0]);
    }
    return 0;
}
