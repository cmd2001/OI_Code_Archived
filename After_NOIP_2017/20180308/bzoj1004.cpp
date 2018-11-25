#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=6e1+5e0;

int in[maxn],vis[maxn],rs[maxn],rcnt;
int f[maxn][maxn][maxn];
int r,g,b,n,m,mod,ans;

inline void dfs(int pos,int siz) {
    if( vis[pos] ) {
        rs[++rcnt] = siz;
        return;
    } vis[pos] = 1;
    dfs(in[pos],siz+1);
}
inline int dp() {
    memset(f,0,sizeof(f)) , ***f = 1;
    for(int i=1;i<=rcnt;i++) {
        const int p = rs[i];
        for(int rr=r;~rr;rr--)
            for(int gg=g;~gg;gg--)
                for(int bb=b;~bb;bb--) {
                    if( rr >= p ) ( f[rr][gg][bb] += f[rr-p][gg][bb] ) %= mod;
                    if( gg >= p ) ( f[rr][gg][bb] += f[rr][gg-p][bb] ) %= mod;
                    if( bb >= p ) ( f[rr][gg][bb] += f[rr][gg][bb-p] ) %= mod;
                }
    }
    return f[r][g][b];
}
inline int calc() {
    memset(vis,0,sizeof(vis)) , rcnt = 0;
    for(int i=1;i<=n;i++) if( !vis[i] ) dfs(i,0);
    return dp();
}
inline int fastpow(int base,int tim) {
    int ret = 1;
    while( tim ) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1)  base = base * base % mod;
    }
    return ret %= mod;
}

int main() {
    scanf("%d%d%d%d%d",&r,&g,&b,&m,&mod) , n = r + g + b;
    for(int i=1;i<=m+1;i++) {
        if( i <= m ) for(int j=1;j<=n;j++) scanf("%d",in+j);
        else for(int j=1;j<=n;j++) in[j] = j;
        ans = ( ans + calc() ) % mod;
    }
    ans = ans * fastpow(m+1,mod-2) % mod;
    printf("%d\n",ans);
    return 0;
}
