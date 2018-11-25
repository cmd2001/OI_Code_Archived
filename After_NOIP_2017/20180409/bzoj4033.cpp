#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=2e3+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int siz[maxn];
lli l[maxn<<1];
lli f[maxn][maxn],tp[maxn];
int n,k;

inline void coredge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int from,int to,int len) {
    coredge(from,to,len) , coredge(to,from,len);
}

inline void dfs(int pos,int fa,lli lat) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
        dfs(t[at],pos,l[at]);
        memset(tp,0,sizeof(lli)*(siz[pos]+siz[t[at]]+1));
        for(int i=0;i<=siz[pos];i++)
            for(int j=0;j<=siz[t[at]];j++)
                tp[i+j] = max( tp[i+j] , f[pos][i] + f[t[at]][j] );
        memcpy(f[pos],tp,sizeof(lli)*(siz[pos]+siz[t[at]]+1))  , siz[pos] += siz[t[at]];
    }
    for(int i=0;i<=siz[pos];i++)
        f[pos][i] += lat * ( i * ( k - i ) + ( siz[pos] - i ) * ( ( n - k ) - (siz[pos] - i ) ) ); 
}

int main() {
    scanf("%d%d",&n,&k);
    for(int i=1,a,b,l;i<n;i++) scanf("%d%d%d",&a,&b,&l) , doubledge(a,b,l);
    dfs(1,-1,0);
    printf("%lld\n",f[1][k]);
    return 0;
}