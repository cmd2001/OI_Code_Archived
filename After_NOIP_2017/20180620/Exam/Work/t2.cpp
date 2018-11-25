#pragma GCC optimize("Ofast")
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cctype>
typedef long long int lli;
const int maxn=1e5+1e2,lim=1e5;
const lli mod = ( 1ll << 32 );

struct Edge { int tar,lcm; };
struct Node { int u,v,w; } ns[maxn*21];
int mu[maxn];
lli fa[maxn],fb[maxn],fc[maxn],ans;
int deg[maxn],mem[maxn];
int a,b,c,n,m,ecnt;
std::vector<Edge> es[maxn];

inline int gcd(int x,int y) {
    register int t;
    while( t = x % y ) x = y , y = t;
    return y;
}
inline void sieve() {
    static int prime[maxn/10],cnt;
    static bool vis[maxn];
    mu[1] = 1;
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i , mu[i] = -1;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
            const int tar = i * prime[j];
            vis[tar] = 1;
            if( i % prime[j] ) mu[tar] = -mu[i];
            else break;
        }
    }
}
 
inline void getf(lli* dst,int lim) {
    for(int i=1;i<=lim;i++) for(int j=i;j<=lim;j+=i) dst[i] += lim / j;
}
inline void calc_single_point() {
    for(int i=1;i<=m;i++) if( mu[i] ) ans += mu[i] * mu[i] * mu[i] * fa[i] * fb[i] * fc[i];
}
inline void pre_ring() {
    for(int g=1;g<=n;g++) for(int i=1;i*g<=n;i++) if( mu[i*g] ) for(int j=i+1;(lli)i*j*g<=n;j++) if( mu[j*g] && gcd(i,j) == 1 ) {
        const int u = i * g , v = j * g , w = i * j * g , pi = mu[u] * mu[u] * mu[v] , qi = mu[u] * mu[v] * mu[v];
        if( w > n ) continue;
        ans += pi * ( fa[u] * fb[w] * fc[w] + fa[w] * fb[u] * fc[w] + fa[w] * fb[w] * fc[u] );
        ans += qi * ( fa[v] * fb[w] * fc[w] + fa[w] * fb[v] * fc[w] + fa[w] * fb[w] * fc[v] );
        ++deg[u] , ++deg[v] , ns[++ecnt] = (Node){u,v,w};
    }
    for(int i=1;i<=ecnt;i++) {
        if( deg[ns[i].u] < deg[ns[i].v] || ( deg[ns[i].u] == deg[ns[i].v] && ns[i].u < ns[i].v ) ) es[ns[i].u].push_back((Edge){ns[i].v,ns[i].w});
        else es[ns[i].v].push_back((Edge){ns[i].u,ns[i].w});
    }
}
inline void calc_ring() {
    for(int i=1;i<=n;i++) {
        for(unsigned J=0;J<es[i].size();J++) mem[es[i][J].tar] = es[i][J].lcm;
        for(unsigned J=0;J<es[i].size();J++) {
            const int j = es[i][J].tar;
            for(unsigned K=0;K<es[j].size();K++) {
                const int k = es[j][K].tar , pi = mu[i] * mu[j] * mu[k];
                const int lij = es[i][J].lcm , ljk = es[j][K].lcm , lki = mem[k];
                if( !lki ) continue; // lcm(i,k) > n so i didn't record k .
                ans += pi * ( fa[lij] * fb[ljk] * fc[lki] + fa[lij] * fb[lki] * fc[ljk] + fa[ljk] * fb[lij] * fc[lki] + 
                              fa[ljk] * fb[lki] * fc[lij] + fa[lki] * fb[lij] * fc[ljk] + fa[lki] * fb[ljk] * fc[lij] );
            }
        }
        for(unsigned J=0;J<es[i].size();J++) mem[es[i][J].tar] = 0;
    }
}
 
inline void init() {
    n = std::max( a , std::max( b , c ) ) , m = std::min( a , std::min( b , c ) ) , ans = 0;
}
 
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}
 
int main() {
    static int T;
    a = getint() , b = getint() , c = getint() , init() , sieve() , getf(fa,a) , getf(fb,b) , getf(fc,c);
    calc_single_point() , pre_ring() , calc_ring() , printf("%lld\n",ans%mod);
    return 0;
}
