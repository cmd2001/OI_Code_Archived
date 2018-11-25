#include<cstdio>
#include<cstring>
typedef long long int lli;
const int maxn=1e5+1e2;
const int mod=1e9+7;

lli f[maxn][3];
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int ini[maxn];

inline void addedge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos,int fa) {
    if( ~ ini[pos] ) f[pos][ini[pos]] = 1;
    else f[pos][0] = f[pos][1] = f[pos][2] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
        dfs(t[at],pos);
        f[pos][0] = f[pos][0] * ( f[t[at]][1] + f[t[at]][2] ) % mod ,
        f[pos][1] = f[pos][1] * ( f[t[at]][0] + f[t[at]][2] ) % mod ,
        f[pos][2] = f[pos][2] * ( f[t[at]][0] + f[t[at]][1] ) % mod ;
    }
}

int main() {
    static int n,k;
    scanf("%d%d",&n,&k) , memset(ini,-1,sizeof(ini));
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b) , addedge(b,a);
    for(int i=1,b,c;i<=k;i++) scanf("%d%d",&b,&c) , ini[b] = c - 1;
    dfs(1,-1) , printf("%lld\n",(f[1][0]+f[1][1]+f[1][2])%mod);
    return 0;
}
