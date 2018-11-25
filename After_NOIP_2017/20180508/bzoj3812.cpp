#include<cstdio>
typedef long long int lli;
const int maxs=1<<15,maxe=1<<15;
const int mod=1e9+7;

int in[maxe],out[maxe],n,m,full;
lli f[maxe],g[maxe],h[maxe],w[maxe],bit[maxe],pw[maxe];

__inline int lowbit(int x) { return x & -x ; }

int main() {
    scanf("%d%d",&n,&m) , full = 1 << n , *pw = 1;
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , a=(1<<(a-1)) , b=(1<<(b-1)) , out[a] |= b , in[b] |= a;
    for(int i=1;i<maxs;i++) pw[i] = pw[i-1] * 2 % mod;
    for(int i=1;i<maxs;i++) bit[i] = bit[i>>1] + ( i & 1 );
    for(int s=1;s<full;s++) {
        int lb = lowbit(s) , ss = s ^ lb;
        for(int sss=ss;sss;sss=(sss-1)&ss) g[s] = ( g[s] - f[s^sss] * g[sss] % mod + mod ) % mod;
        h[s] = h[ss] + bit[in[lb]&ss] + bit[out[lb]&ss];
        f[s] = pw[h[s]];
        for(int sss=s;sss;sss=(sss-1)&s) {
            int lb = lowbit(sss^s);
            if( sss == s ) w[sss] = 0;
            else w[sss] = w[sss^lb] - bit[out[lb]&(s^sss)] + bit[in[lb]&sss];
            f[s] = ( f[s] - g[sss] * pw[w[sss]+h[s^sss]] % mod + mod ) % mod;
        }
        f[s] = ( f[s] + mod ) % mod , g[s] = ( g[s] + f[s] ) % mod;
    }
    printf("%lld\n",f[full-1]);
}
