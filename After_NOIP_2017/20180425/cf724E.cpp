#pragma GCC optimize("Ofast")
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef unsigned long long ulli;
const int maxn=1e4+1e2+3;
const ulli inf = 0x3f3f3f3f3f3f3f3fllu;

ulli f[2][maxn],p[maxn],s[maxn],c,ans=inf;
unsigned n,cur;

__inline void trans(const unsigned &i) {
    memset(f[cur],0x3f,sizeof(f[cur])) , f[cur][0] = f[cur^1][0] + p[i];
    for(unsigned j=1;j<=i;j++) f[cur][j] = std::min( f[cur^1][j] + j * c + p[i] , f[cur^1][j-1] + s[i] );
}

int main() {
    scanf("%u%I64u",&n,&c);
    for(unsigned i=1;i<=n;i++) scanf("%I64u",p+i);
    for(unsigned i=1;i<=n;i++) scanf("%I64u",s+i);
    memset(f,0x3f,sizeof(f)) , **f = 0;
    for(unsigned i=1;i<=n;i++) {
        cur ^=1 , trans(i);
    }
    for(unsigned i=0;i<=n;i++) ans = std::min( ans , f[cur][i] );
    printf("%I64u\n",ans);
    return 0;
}

