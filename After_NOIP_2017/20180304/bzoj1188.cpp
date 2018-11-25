#include<cstdio>
#include<cstring>
const int maxn=30,maxl=1e3+1e2;

int in[maxn],sg[maxn];
int n;

inline int g(int p) {
    if( ~sg[p] ) return sg[p];
    if( p == n ) return sg[p] = 0;
    static char vis[maxl];
    memset(vis,0,sizeof(vis));
    for(int i=p+1;i<=n;i++) for(int j=i;j<=n;j++) vis[g(i)^g(j)] = 1;
    for(int i=1;i<=maxl;i++) if( !vis[i] ) return sg[p] = i;
}

int main() {
    static int T,ans,cnt;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n) , cnt = ans = 0;
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        memset(sg,-1,sizeof(sg));
        for(int i=1;i<=n;i++) if( in[i] & 1 ) ans ^= g(i);
        for(int i=1;i<=n;i++)
            if( in[i] )
                for(int j=i+1;j<=n;j++) for(int k=j;k<=n;k++)
                    if( !( ans ^ g(i) ^ g(j) ^ g(k) ) && !cnt++ ) printf("%d %d %d\n",i-1,j-1,k-1);
        if( !cnt ) puts("-1 -1 -1");
        printf("%d\n",cnt);
    }
    return 0;
}
