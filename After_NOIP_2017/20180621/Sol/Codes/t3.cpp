#pragma GCC optimize("Ofast")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=512;
const int mod=1004535809;

inline int add(const int &x,const int &y) {
    const int ret = x + y;
    return ret >= mod ? ret - mod : ret;
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

int f[maxn][maxn],c[maxn][maxn],mem[maxn][17];

int main() {
    c[0][0] = 1;
    for(int i=1;i<maxn;i++) {
        c[i][0] = 1;
        for(int j=1;j<=i;j++) c[i][j] = add(c[i-1][j-1],c[i-1][j]);
    }
    f[1][1] = 1;
    for(int i=2;i<maxn;i++) {
        f[i][i] = 1;
        for(int j=i-1;j>=1;j--) {
            for(int t=1;t<=i;t++) adde(f[i][j],mul(mul(f[t][1],c[i][t]),f[i-t][j-1]));
            mule(f[i][j],fastpow(j,mod-2));
        }
        f[i][1] = fastpow(2,i*(i-1)>>1);
        for(int j=2;j<=i;j++) sube(f[i][1],f[i][j]);
    }
    int t;
    scanf("%d",&t) , memset(mem,-1,sizeof(mem));
    while(t--) {
        int n,k,ans=0;
        scanf("%d%d",&n,&k);
        if( ~mem[n][k] ) printf("%d\n",mem[n][k]);
        else {
            for(int i=1;i<=n;i++) adde(ans,mul(f[n][i],fastpow(i,k)));
            mule(ans,fastpow(fastpow(2,n*(n-1)>>1),mod-2)) , printf("%d\n",mem[n][k]=ans);
        }
    }
    return 0;
}

