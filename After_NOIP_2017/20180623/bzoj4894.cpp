#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=3e2+1e1;
const int mod=1e9+7;

inline int sub(const int &x,const int &y) {
    const int ret = x - y;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void sube(int &dst,const int &x) {
    if( ( dst -= x ) < 0 ) dst += mod;
}
inline void mule(int &dst,const int &x) {
    dst = (lli) dst * x % mod;
}
inline void fix(int &dst) {
    while( dst < 0 ) dst += mod;
    while( dst >= mod ) dst -= mod;
}
inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) mule(ret,base);
        if( tim >>= 1 ) mule(base,base);
    }
    return ret;
}

int dat[maxn][maxn],n;

inline int gauss() {
    int ret = 1;
    for(int i=2,pos=-1;i<=n;i++,pos=-1) {
        for(int j=i;j<=n;j++) if( dat[j][i] ) { pos = j; break; }
        if( !~pos ) return 0;
        if( pos != i ) {
            for(int j=2;j<=n;j++) swap(dat[i][j],dat[pos][j]);
            ret = sub(mod,ret) , pos = i;
        }
        const int inv = fastpow(dat[i][i],mod-2); mule(ret,dat[i][i]);
        for(int j=2;j<=n;j++) mule(dat[i][j],inv);
        for(int j=2;j<=n;j++) if( j != i && dat[j][i] ) {
            const int m = dat[j][i];
            for(int k=2;k<=n;k++) sube(dat[j][k],mul(m,dat[i][k]));
        }
    }
    return ret;
}

int main() {
    static char s[maxn];
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%s",s+1);
        for(int j=1;j<=n;j++) if( s[j] - '0' ) --dat[i][j] , ++dat[j][j];
    }
    for(int i=2;i<=n;i++) for(int j=2;j<=n;j++) fix(dat[i][j]);
    printf("%d\n",gauss());
    return 0;
}



