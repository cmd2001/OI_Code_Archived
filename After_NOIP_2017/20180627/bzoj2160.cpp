#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
typedef long long int lli;
const int maxn=1e6+1e2,mod=19930726;

inline void mule(int &dst,const int &x) {
    dst = (lli) dst * x % mod;
}
inline int fastpow(int base,lli tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) mule(ret,base);
        if( tim >>= 1 ) mule(base,base);
    }
    return ret;
}

char in[maxn];
int f[maxn],n,ans=1;
lli way[maxn],su[maxn]; // su is suffix sum .
lli k;

inline void manacher() {
    int mxr = 0 , pos = 0;
    in[0] = '$' , in[n+1] = '#';
    for(int i=1;i<=n;i++) {
        if( i < mxr ) f[i] = min( f[pos*2-i] , mxr - i );
        while( in[i-f[i]] == in[i+f[i]] ) ++f[i];
        ++way[f[i]*2-1];
        if( i + f[i] > mxr ) mxr = i + f[i] , pos = i;
    }
    for(int i=n;i;i--) way[i] += way[i+1];
    for(int i=n;i;i--) su[i] = su[i+1] + ( i & 1 ) * way[i];
}

inline int getpos() { // ret is last full pos .
    int ret = 0;
    for(ret=n;ret;ret--) if( su[ret] >= k ) break;
    return ret ? ret + 1 : 0;
}

inline void calc(int ful) {
    for(int i=n;i>=ful;i--) if( i & 1 ) mule(ans,fastpow(i,way[i]));
    mule(ans,fastpow(ful-1,k-su[ful]));
}

int main() {
    scanf("%d%lld%s",&n,&k,in+1) , manacher();
    int p = getpos();
    if( !p ) return puts("-1") , 0;
    calc(p) , printf("%d\n",ans);
    return 0;
}
