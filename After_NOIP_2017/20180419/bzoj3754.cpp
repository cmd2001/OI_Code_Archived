#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define bool unsigned char
#define debug cout
using namespace std;
const int maxn=1e2+1e1,maxe=2e3+1e2;
const int inf=0x3f3f3f3f;

int n,m,lim;

struct Node {
    int u,v,c;
    friend bool operator < (const Node &a,const Node &b) {
        return a.c < b.c;
    }
}es[maxe];

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return x == fa[x] ? x : fa[x] = findfa(fa[x]);
    }
    inline bool merge(int x,int y) {
        x = findfa(x) , y = findfa(y);
        return x == y ? 0 : fa[x] = y;
    }
    inline void reset() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

bool used[maxe];

inline double calcway(double per,int p) {
    memset(used+1,0,sizeof(bool)*m) , ufs.reset();
    int l = p - 1 , r = p, cur;
    double su = 0 , ret = 0;
    while( l || r <= m ) {
        if( r > m ) cur = l--;
        else if( !l ) cur = r++;
        else if( per - es[l].c < es[r].c - per ) cur = l--;
        else cur = r++;
        if( ufs.merge(es[cur].u,es[cur].v) ) su += es[cur].c , used[cur] = 1;
    }
    su /= n - 1;
    #define sq(x) (x)*(x)
    for(int i=1;i<=m;i++) if( used[i] ) ret += sq( es[i].c - su );
    return ret;
}

int main() {
    static double per = 0 , ans = inf;
    scanf("%d%d",&n,&m) , lim = ( n - 1 ) * 100;
    for(int i=1;i<=m;i++) scanf("%d%d%d",&es[i].u,&es[i].v,&es[i].c);
    sort(es+1,es+1+m);
    for(int i=1,p=1;i<=lim;i++) {
        per = (double) i / ( n - 1 );
        while( p <= m && es[p].c <= per ) ++p;
        ans = min( ans , calcway(per,p) );
    }
    printf("%0.4lf\n",sqrt(ans/(n-1)));
    return 0;
}
