#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long lli;
using namespace std;
const int maxn=1e2+1e1,maxl=64;
const lli minf=0xefefefefefefefefll;

int n;
lli m;

struct Matrix {
    lli f[maxn][maxn];
    Matrix() { memset(f,0xef,sizeof(f)); }
    lli* operator [] (const int &x) { return f[x]; }
    const lli* operator [] (const int &x) const { return f[x]; }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) for(int k=1;k<=n;k++) ret[i][j] = std::max( ret[i][j] , a[i][k] + b[k][j] );
        return ret;
    }
    inline bool check() const {
        for(int i=1;i<=n;i++) if( f[1][i] >= m ) return 1;
        return 0;
    }
    inline void reset() { memset(f,0xef,sizeof(f)); }
}dp[maxl],cur,now;

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}
inline lli getlli() {
    lli ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}
int main() {
    static int T,t;
    static lli ans;
    T = getint();
    while(T--) {
        n = getint() , m = getlli() , dp[0].reset() , ans = 0;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if( !( dp[0][i][j] = getlli() ) ) dp[0][i][j] = minf;
        if( !m ) {
            puts("0");
            continue;
        }
        for(t=1;;t++) {
            dp[t] = dp[t-1] * dp[t-1];
            if( dp[t].check() ) break;
        }
        cur = dp[0];
        for(int i=t;~i;i--) {
            now = cur * dp[i];
            if( !now.check() ) cur = now , ans |= ( 1ll << i );
        }
        printf("%lld\n",ans+2);
    }
    return 0;
}
