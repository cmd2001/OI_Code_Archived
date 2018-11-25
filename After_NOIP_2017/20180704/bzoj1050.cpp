#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long double ldb;
using namespace std;
const int maxn=5e2+1e1,maxe=5e3+1e2;
const int inf=0x3f3f3f3f;

int n,m;

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline void merge(int x,int y) {
        if( ( x = findfa(x) ) != ( y = findfa(y) ) ) fa[x] = y;
    }
    inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

struct Edge {
    int u,v,l;
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.l < b.l;
    }
}es[maxe];

ldb ans;
int x,y,u,v;

inline int gcd(int x,int y) {
    int t;
    while( t = x % y ) x = y , y = t;
    return y;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&es[i].u,&es[i].v,&es[i].l);
    scanf("%d%d",&u,&v) , sort(es+1,es+1+m) , ans = inf;
    if( u == v ) return puts("0"),0;
    for(int i=1;i<=m;i++) {
        ufs.init();
        for(int j=i;j<=m;j++) {
            ufs.merge(es[j].u,es[j].v);
            if( ufs.findfa(u) == ufs.findfa(v) ) {
                if( (ldb) es[j].l / es[i].l < ans ) x = es[i].l , y = es[j].l , ans = (ldb) es[j].l / es[i].l;
                break;
            }
        }
    }
    if( ans == inf ) puts("IMPOSSIBLE");
    else {
        int g = gcd(x,y);
        x /= g , y /= g;
        if( x == 1 ) printf("%d\n",y);
        else printf("%d/%d\n",y,x);
    }
    return 0;
}
