#include<cstdio>
const int maxn=1e4+1e2,maxe=2e4+1e2;

int n;

struct UnionFindSet {
    int fa[maxn],rel[maxn];
    inline int findfa(int x) {
        if( fa[x] == x ) return x;
        const int f = fa[x]; fa[x] = findfa(fa[x]);
        return rel[x] ^= rel[f] , fa[x];
    }
    inline bool merge(int x,int y) {
        int fx = findfa(x) , fy = findfa(y);
        if( fx != fy ) return fa[fx] = fy , rel[fx] = rel[x] ^ rel[y] ^ 1 , 1;
        else return rel[x] ^ rel[y];
    }
    inline void reset() {
        for(int i=1;i<=n;i++) fa[i] = i , rel[i] = 0;
    }
}ufs;

int main() {
    static int T,m,ans;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&m) , ans = 1 , ufs.reset();
        for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , ans &= ufs.merge(a,b);
        puts(m<n+2&&ans?"YES":"NO");
    }
    return 0;
}
