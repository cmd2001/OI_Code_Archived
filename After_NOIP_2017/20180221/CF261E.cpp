#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=4e6+1e2,maxm=1e2+1e1,lim=1e2;

int prime[maxm],f[maxn],tar[maxn],cnt,pcn;
bool vis[maxm],can[maxn];
int l,r,p,ans;

inline void dfs(int now,int step) {
    tar[++cnt] = now;
    for(int i=step;i<=pcn;i++) {
        if( (long long) now * prime[i] > r ) break;
        dfs(now*prime[i],i);
    }
}
inline void sieve() {
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++pcn] = i;
        for(int j=1;j<=pcn&&i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            if( ! ( i % prime[j] ) ) break;
        }
    }
}
inline void getans() {
    dfs(1,1);
    std::sort(tar+1,tar+1+cnt);
    memset(f,0x3f,sizeof(f)) , f[1] = 0;
    for(int i=2;i<p;i++)
        for(int j=1,lst=1;j<=cnt;j++)
            if( ! ( tar[j] % i ) ) {
                while( tar[lst] * i < tar[j] ) ++lst;
                f[j] = std::min( f[j] , f[lst] + 1 );
                if( f[j] + i <= p ) can[j] = 1;
            }
    for(int i=1;i<=cnt;i++) ans += ( tar[i] >= l && can[i] );
}

int main() {
    scanf("%d%d%d",&l,&r,&p);
    sieve();
    getans();
    printf("%d\n",ans);
    return 0;
}
