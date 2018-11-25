#include<bits/stdc++.h>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2,maxe=1e6+1e2;

int n,m;
lli ans;

struct Edge {
    int u,v,id;
    lli w;
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.w < b.w;
    }
}es[maxe];

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline bool merge(int x,int y) {
        x = findfa(x) , y = findfa(y);
        return x == y ? 0 : fa[x] = y;
    }
    inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

int main() {
    scanf("%d%d",&n,&m) , ufs.init();
    for(int i=1;i<=m;i++) scanf("%d%d%lld%*d",&es[i].u,&es[i].v,&es[i].w) , es[i].id = i;
    sort(es+1,es+1+m);
    for(int i=1;i<=m;i++) if( ufs.merge(es[i].u,es[i].v) ) ans += es[i].w , printf("%d\n",es[i].id);
    return 0;
}

