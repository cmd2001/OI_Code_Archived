#include<cstdio>
#include<cstring>
typedef long long int lli;
const int maxn=1e3+1e2;
 
int prime[maxn],cnt;
lli f[maxn][maxn],ans;
int n;
 
inline void sieve() {
    static char vis[maxn];
    for(int i=2;i<=n;i++) {
        if( !vis[i] ) prime[++cnt] = i;
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++) vis[i*prime[j]] = 1;
    }
}
inline void trans(lli* dst,lli* sou,int p) {
    memcpy(dst,sou,sizeof(lli)*(n+1));
    for(int x=p;x<=n;x*=p) for(int j=x;j<=n;j++) dst[j] += sou[j-x];
}
 
int main() {
    scanf("%d",&n) , sieve();
    **f = 1;
    for(int i=1;i<=cnt;i++) trans(f[i],f[i-1],prime[i]);
    for(int i=0;i<=n;i++) ans += f[cnt][i];
    printf("%lld\n",ans);
    return 0;
}

