#include<bits/stdc++.h>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2,maxe=1e6+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int n,m;
lli ans=inf;
set<int> cs;
int way[maxe],mem[maxe];

struct Edge {
    int u,v,col,id;
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

inline int getsiz(int x) {
    int ret = 0;
    while(x) ++ret , x -= (x&-x);
    return ret;
}
inline lli calc(int sta) {
    lli ret = 0 , sel = 0; ufs.init();
    for(int i=1;i<=m;i++) if( ( es[i].col & sta ) && ufs.merge(es[i].u,es[i].v) ) ret += es[i].w , way[++sel]=i;
    return sel == n - 1 ? ret * getsiz(sta) : inf;
}


int main() {
    scanf("%d%d",&n,&m) , ufs.init();
    for(int i=1;i<=m;i++) scanf("%d%d%lld%d",&es[i].u,&es[i].v,&es[i].w,&es[i].col) , es[i].col = 1 << ( es[i].col - 1 ) , cs.insert(es[i].col) , es[i].id = i;
    sort(es+1,es+1+m);
    int ss = 1 << cs.size();
    cerr<<"inf = "<<inf<<endl;
    for(int i=1;i<=m;i++) if( es[i].col >= ss ) cerr<<"color size error!"<<endl , exit(0);
    for(int i=0;i<ss;i++) {
        lli cal = calc(i);
        if( cal < ans ) ans = cal , memcpy(mem,way,sizeof(int)*n) , cerr<<"copy i = "<<i<<endl;
    }
    for(int i=1;i<n;i++) printf("%d\n",es[mem[i]].id);
    return 0;
}

