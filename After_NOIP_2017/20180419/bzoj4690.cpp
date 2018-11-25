#include<cstdio>
typedef long long int lli;
const int maxn=1e5+1e2;

struct UnionFindSet {
    int fa[maxn];
    lli rel[maxn];
    inline int findfa(int x) {
        if( fa[x] == x ) return x;
        int f = fa[x] ; fa[x] = findfa(fa[x]);
        rel[x] = rel[x] + rel[f];
        return fa[x];
    }
    inline void merge(int x,int y,lli r) {
        findfa(x) , findfa(y) , r += rel[y] - rel[x];
        x = findfa(x) , y = findfa(y) , fa[x] = y , rel[x] = r;
    }
    inline void init(int n) {
        for(int i=1;i<=n;i++) fa[i] = i , rel[i] = 0;
    }
}ufs;

int main() {
    static int n,m;
    static char o[10];
    while( scanf("%d%d",&n,&m) && ( n || m ) ) {
        ufs.init(n);
        for(int i=1,x,y,r;i<=m;i++) {
            scanf("%s%d%d",o,&x,&y);
            if( *o == '!' ) scanf("%d",&r) , ufs.merge(x,y,-r);
            else if( *o == '?' ) {
                if( ufs.findfa(x) == ufs.findfa(y) ) printf("%lld\n",ufs.rel[y]-ufs.rel[x]);
                else puts("UNKNOWN");
            }
        }
    }
    return 0;
}