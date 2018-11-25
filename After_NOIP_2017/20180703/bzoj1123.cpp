#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2,maxe=5e5+1e2;

int s[maxn],t[maxe<<1],nxt[maxe<<1];
int dfn[maxn],low[maxn],siz[maxn],n;
lli ans[maxn];

inline void coredge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}
inline void dfs(int pos,int fa) {
    static int dd; int su = 0; low[pos] = dfn[pos] = ++dd , siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
        if( !dfn[t[at]] ) {
            dfs(t[at],pos) , low[pos] = min( low[pos] , low[t[at]] ) , siz[pos] += siz[t[at]];
            if( low[t[at]] >= dfn[pos] ) ans[pos] += (lli) su * siz[t[at]] , su += siz[t[at]];
        } else low[pos] = min( low[pos] , dfn[t[at]] );
    }
    ans[pos] += (lli) su * ( n - su - 1 ) + n - 1 ,  ans[pos] <<= 1;
}

int main() {
    static int m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , addedge(a,b);
    dfs(1,-1);
    for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
    return 0;
}

