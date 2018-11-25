#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=2e3+1e1;

int n,su;
lli ans;

struct Edge {
    int a,b;
    lli val;
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.val < b.val;
    }
}es[maxn*maxn>>1];

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
        for(int i=1;i<=n+1;i++) fa[i] = i;
    }
}ufs;

int main() {
    scanf("%d",&n) , ufs.init();
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++) {
            scanf("%lld",&es[++su].val) , es[su].a = i , es[su].b = j + 1;
        }
    sort(es+1,es+1+su);
    for(int i=1;i<=su;i++) if( ufs.merge(es[i].a,es[i].b) ) ans += es[i].val;
    printf("%lld\n",ans);
    return 0;
}

