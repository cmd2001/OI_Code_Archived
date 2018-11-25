#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e5+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
lli f[maxn],g[maxn],in[maxn],l[maxn<<1];
int srt[maxn],cnt;

bool cmp(int a,int b) {
    return g[a] - f[a] > g[b] - f[b];
}

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;    
}

inline void dfs(int pos,int fa) {
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa )
            dfs(t[at],pos);
    cnt = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa ) {
            f[t[at]] += ( l[at] << 1 );
            g[t[at]] = max( g[t[at]] + 1 , f[t[at]] );
            srt[++cnt] = t[at];
        }
    lli su = 0 , mx = in[pos];
    sort(srt+1,srt+1+cnt,cmp);
    for(int i=1;i<=cnt;i++) {
        mx = max( mx , su + g[srt[i]] );
        su += f[srt[i]];
    }
    f[pos] = su , g[pos] = mx;
}

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",in+i);
    for(int i=1,a,b;i<n;i++) {
        scanf("%d%d",&a,&b);
        addedge(a,b,1) , addedge(b,a,1);
    }
    dfs(1,-1);
    printf("%lld\n",max( g[1] , f[1] + in[1] ) );
    return 0;
}
