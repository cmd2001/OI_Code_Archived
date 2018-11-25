#include<bits/stdc++.h>
#define debug cerr
typedef long long int lli;
using namespace std;
const int maxn=1e6+1e2;

map<lli,int> app;
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int dfn[maxn],low[maxn],stk[maxn],ins[maxn],vis[maxn],ban[maxn],top; // ban will be 1 if bridge .
lli val[maxn],col[maxn],su,cv=0x3f3f3f3f3f3f3f3f;
int n,m,ans;

inline void coredge(int from,int to) {
    static int cnt = 1;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}

inline void dfs(int pos,int fae) {
    static int dd;
    vis[pos] = 1 , low[pos] = dfn[pos] = ++dd;
    for(int at=s[pos];at;at=nxt[at]) if( at != ( fae ^ 1 ) ) {
        if( !vis[t[at]] ) {
            dfs(t[at],at) , low[pos] = min( low[pos] , low[t[at]] );
            if( low[t[at]] > dfn[pos] ) ban[at>>1] = 1;
        } else low[pos] = min( low[pos] , dfn[t[at]] );
    }
}

inline lli calc(int edg) {
    lli cs = app.size() - ( app[col[edg]] == 1 );
    return ( su - val[edg] ) * cs;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d%lld%d",&a,&b,val+i,col+i) , addedge(a,b) , ++app[col[i]] , su += val[i];
    dfs(1,0);
    for(int i=1;i<=m;i++) {
        if( !ban[i] && calc(i) <= cv ) cv =  calc(i) , ans = i;
    }
    for(int i=1;i<=m;i++) if( i != ans ) printf("%d\n",i);
    return 0;
}

