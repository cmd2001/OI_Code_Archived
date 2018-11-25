#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e2+1e1;
const int mod=1e9+7;

int l[maxn],r[maxn],srt[maxn<<1],len;
lli inv[maxn],c[maxn<<1][maxn];
lli f[maxn][maxn<<1];
int n;

inline lli fastpow(lli base,int tme,int mod) {
    lli ret = 1;
    while( tme ) {
        if( tme & 1 ) ret = ret * base % mod;
        base = base * base % mod;
        tme >>= 1;
    }
    return ret;
}
inline void getinv() {
    *inv = 1;
    for(int i=1;i<=n;i++)
        inv[i] = inv[i-1] * i % mod;
    inv[n] = fastpow(inv[n],mod-2,mod);
    for(int i=n-1;~i;i--)
        inv[i] = inv[i+1] * ( i + 1 ) % mod;
}
inline lli calcc(int n,int m) {
    if( n < m ) return 0;
    lli ret = 1;
    for(int i=n;i>n-m;i--)
        ret = ret * i % mod;
    ret = ret * inv[m] % mod;
    return ret;
}
inline void getc() {
    for(int i=1;i<len;i++)
        for(int j=1;j<=n;j++)
            c[i][j] = calcc(srt[i+1]-srt[i]+1,j);
}
inline void getans() {
    l[0] = 0 , r[0] = len+1;
    for(int i=0;i<=len;i++)
        f[0][i] = 1;
    for(int i=1;i<=n;i++) {
        for(int j=l[i];j<r[i];j++)
            for(int k=i-1;k>=0&&l[k]<=j-1&&j-1<r[k];k--) {
                debug<<"i = "<<i<<"j = "<<j<<endl;
                f[i][j] += f[k][j-1] * c[j][i-k] % mod , f[i][j] %= mod;
            }
        debug<<"inital f = "<<endl;
        for(int j=1;j<len;j++) debug<<f[i][j]<<" ";debug<<endl;
        for(int j=1;j<len;j++)
            f[i][j] += f[i][j-1] , f[i][j] %= mod;
        for(int j=1;j<len;j++)
            f[i][j] += f[i-1][j] , f[i][j] %= mod;
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",l+i) , srt[++len] = l[i] ,
        scanf("%d",r+i) , srt[++len] = r[i] ;
    sort(srt+1,srt+1+len) , len = unique(srt+1,srt+1+len) - srt - 1;
    for(int i=1;i<=n;i++)
        l[i] = lower_bound(srt+1,srt+1+len,l[i]) - srt ,
        r[i] = lower_bound(srt+1,srt+1+len,r[i]) - srt ;
    getinv() , getc() , getans();
    //for(int i=1;i<=len;i++) debug<<srt[i]<<" ";debug<<endl;
    //for(int i=1;i<len;i++) for(int j=1;j<=n;j++) debug<<"len = "<<(srt[i+1]-srt[i]+1)<<"m = "<<j<<" c = "<<c[i][j]<<endl;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<len;j++) debug<<f[i][j]<<" ";
        debug<<endl;
    }
    debug<<f[n][r[n]-1]<<endl;
    return 0;
}
