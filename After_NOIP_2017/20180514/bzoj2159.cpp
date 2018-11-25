#include<cstdio>
const int maxn=5e4+1e2,maxe=1.5e2+1e1;
const int mod=1e4+7;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int f[maxn][maxe],g[maxn][maxe],s2[maxe][maxe],fac[maxe];
int n,k;

inline void coredge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int from,int to) {
    coredge(from,to) , coredge(to,from);
}
inline void pre(int pos,int fa) {
    f[pos][0] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
        pre(t[at],pos) , f[pos][0] = ( f[pos][0] + f[t[at]][0] ) % mod;
        for(int i=1;i<=k;i++) f[pos][i] = ( f[pos][i] + f[t[at]][i] + f[t[at]][i-1] ) % mod;
    }
}
inline void dfs(int pos,int fa) {
    if( ~fa ) {
        g[pos][0] = ( n - f[pos][0] ) % mod;
        for(int i=1;i<=k;i++) {
            g[pos][i] = ( g[pos][i] + g[fa][i] + g[fa][i-1] ) % mod;
            g[pos][i] = ( g[pos][i] + f[fa][i] + f[fa][i-1] ) % mod;
            g[pos][i] = ( g[pos][i] - f[pos][i] - 2 * f[pos][i-1] + 3 * mod ) % mod;
            if( i >= 2 ) g[pos][i] = ( g[pos][i] - f[pos][i-2] + mod ) % mod;
        }
    }
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) dfs(t[at],pos);
}
inline int calc(int pos) {
    int ret = 0;
    for(int i=1;i<=k;i++) ret = ( ret + s2[k][i] * ( g[pos][i] + f[pos][i] ) % mod * fac[i] % mod ) % mod;
    return ret;
}

inline void input() {
    static int N,K,L,i,now,A,B,Q,tmp;
    scanf("%d%d%d",&N,&K,&L);
    scanf("%d%d%d%d",&now,&A,&B,&Q);
    n = N , k = K;
    for (i = 1; i < N; i ++) {
        now = ( now * A + B ) % Q;
        tmp = ( i < L ) ? i : L;
        doubledge( i - now % tmp , i + 1 );
    }
}


int main() {
    input() , pre(1,-1) , dfs(1,-1);
    **s2 = *fac = 1;
    for(int i=1;i<=k;i++) fac[i] = fac[i-1] * i % mod;
    for(int i=1;i<=k;i++) for(int j=1;j<=i;j++) s2[i][j] = ( s2[i-1][j] * j + s2[i-1][j-1] ) % mod;
    for(int i=1;i<=n;i++) printf("%d\n",calc(i));
    return 0;
}
