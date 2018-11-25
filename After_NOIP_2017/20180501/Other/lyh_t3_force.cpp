#include<bits/stdc++.h>
using namespace std;

namespace Force {
    const int maxn=1e3+1e2,maxe=1e6+1e2;
    struct Edge {
        int u,v,l;
        friend bool operator < (const Edge &a,const Edge &b) {
            return a.l < b.l;
        }
    }es[maxe];
    int n,cnt,ans;
    struct UnionFindSet {
        int fa[maxn];
        inline int findfa(int x) {
            return x == fa[x] ? x : fa[x] = findfa(fa[x]);
        }
        inline bool merge(int x,int y) {
            return ( x = findfa(x) ) != ( y = findfa(y) ) ? fa[x] = y , 1 : 0;
        }
        inline void init() {
            for(int i=1;i<=n;i++) fa[i] = i;
        }
    }ufs;
    int tim[maxn],bit[maxn];
    inline void addbit(int t) {
        for(int i=0;i<31;i++) if( t & ( 1 << i ) ) ++bit[i];
    }
    void main() {
        scanf("%d",&n) , ufs.init();
        for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) es[++cnt] = (Edge){i,j,i^j};
        sort(es+1,es+1+cnt);
        for(int i=1;i<=cnt;i++) if( ufs.merge(es[i].u,es[i].v) ) ans ^= es[i].l , ++tim[es[i].u] , ++tim[es[i].v] , addbit(es[i].l);
        printf("%d\n",ans);
        for(int i=0;i<n;i++) printf("%d%c",tim[i],i!=n-1?' ':'\n');
        for(int i=0;i<16;i++) printf("%3d%c",bit[i],i!=15?' ':'\n');
        --n;
        for(int i=0;i<16;i++) printf("%3d%c",(n>>i)&1,i!=15?' ':'\n');
    }
}

int main() {
    Force::main();
    return 0;
}
