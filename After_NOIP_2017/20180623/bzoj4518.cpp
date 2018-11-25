#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long double ldb;
using namespace std;
const int maxn=3e3+1e2;

int in[maxn],s[maxn],f[2][maxn],n,m,cur,ans;

inline ldb slop(const int* f,const int &k,const int &j) { // assert k <= j .
    return (ldb) ( f[j] + s[j] * s[j] - f[k] - s[k] * s[k] ) / ( 2.0 * ( s[j] - s[k] ) );
}

inline void trans(int* dst,const int* sou) {
    static int q[maxn],st,ed;
    memset(dst+1,0x3f,n<<2) , q[st=ed=1] = 0;
    for(int i=1;i<=n;i++) {
        while( st < ed && slop(sou,q[st],q[st+1]) <= s[i] ) ++st;
        dst[i] = sou[q[st]] + ( s[i] - s[q[st]] ) * ( s[i] - s[q[st]] );
        while( st < ed && slop(sou,q[ed-1],q[ed]) >= slop(sou,q[ed],i) ) --ed;
        q[++ed] = i;
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",s+i) , s[i] += s[i-1];
    for(int i=0;i<=n;i++) f[cur][i] = s[i] * s[i];
    for(int i=2;i<=m;i++) cur ^= 1 , trans(f[cur],f[cur^1]);
    ans = m * f[cur][n] - s[n] * s[n] , printf("%d\n",ans);
    return 0;
}

