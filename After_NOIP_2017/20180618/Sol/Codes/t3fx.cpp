#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define Fixy for(int i=1;i<=n;i++) for(int x=-n;x<=n;x++) for(int y=-n;y<=n;y++)
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=2e2+1e1;
const int mod=998244353;
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};

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

int in[4],su,n;
int g[maxn],sumw[maxn],sumf[maxn];
struct Array {
    int dat[maxn>>1][maxn][maxn];
    inline int& operator () (const int &i,const int &x,const int &y) {
        return dat[i][x+n+1][y+n+1];
    }
}w,r,s,f;

inline int judge(const int &x,const int &y) {
    return -n <= x && x <= n && -n <= y && y <= n;
}
inline void getw() {
    w(0,0,0) = 1;
    for(int i=0;i<n;i++) for(int x=-n;x<=n;x++) for(int y=-n;y<=n;y++) if( w(i,x,y) ) for(int j=0;j<4;j++) {
        const int tx = x + dx[j] , ty = y + dy[j];
        if( judge(tx,ty) ) adde(w(i+1,tx,ty),mul(w(i,x,y),in[j]));
    }
}
inline void getg() {
    int pi = 1; g[0] = 1;
    for(int i=1;i<=n;i++) {
        mule(pi,su) , g[i] = pi;
        for(int j=1;j<=i;j++) sube(g[i],mul(w(j,0,0),g[i-j]));
    }
}
inline void getr() {
    Fixy {
        r(i,x,y) = w(i,x,y);
        for(int j=1;j<i;j++) sube(r(i,x,y),mul(w(j,0,0),r(i-j,x,y)));
    }
}
inline void gets() {
    Fixy {
        for(int j=1;j<i;j++) adde(s(i,x,y),mul(w(j,x,y),r(i-j,-x,-y)));
    }
}
inline void getf() {
    Fixy if( x || y ) {
        for(int j=1;j<=i;j++) adde(f(i,x,y),mul(g[i-j],w(j,x,y)));
        for(int j=1;j<=i;j++) sube(f(i,x,y),mul(g[i-j],s(j,x,y)));
        for(int j=1;j<=i;j++) sube(f(i,x,y),mul(f(i-j,x,y),sub(w(j,0,0),s(j,-x,-y))));
    }
}
inline int getans() {
    static int d,d2;
    for(int i=0;i<=n;i++) for(int x=-n;x<=n;x++) for(int y=-n;y<=n;y++) adde(sumf[i],f(i,x,y));
    for(int i=0;i<=n;i++) for(int x=-n;x<=n;x++) for(int y=-n;y<=n;y++) adde(sumw[i],w(i,x,y));
    for(int i=0;i<=n;i++) adde(d,mul(sumw[i],g[n-i]));
    for(int i=0;i<=n;i++) adde(d2,mul(sumf[i],sumw[n-i]));
    adde(d2,d2) , adde(d2,d) , mule(d2,fastpow(su,n));
    return sub(d2,mul(d,d));
}


int main() {
    scanf("%d",&n);
    for(int i=0;i<4;i++) scanf("%d",in+i) , adde(su,in[i]);
    getw() , getg() , getr() , gets() , getf() , printf("%d\n",getans());
    return 0;
}

