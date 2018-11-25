#include<iostream>
#include<cstdio>
#define debug cout
using namespace std;
const int maxn=2e3+1e2;

int fa[maxn],rel[maxn],x[maxn],y[maxn],w[maxn];

inline int findfa(int x) {
    if( x == fa[x] ) return x;
    int t = fa[x];
    fa[x] = findfa(fa[x]) , rel[x] += rel[t];
    return fa[x];
}
int main() {
    static int t,n,m,k,ans;
    scanf("%d",&t);
    while( t-- ) {
        scanf("%d%d%d",&n,&m,&k) , ans = 1;
        for(int i=1;i<=n+m;i++) fa[i] = i , rel[i] = 0;
        for(int i=1;i<=k;i++) scanf("%d%d%d",x+i,y+i,w+i) , y[i] += n;
        for(int i=1;i<=k&&ans;i++) {
            int fx = findfa(x[i]) , fy = findfa(y[i]);
            if( fx != fy ) fa[fy] = fx , rel[fy] = rel[x[i]] - rel[y[i]] - w[i];
            else if( rel[x[i]] - rel[y[i]] != w[i] ) ans = 0;
        }
        puts(ans?"Yes":"No");
    }
    return 0;
}
