#pragma GCC optimize(3)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<queue>
using namespace std;
const int maxn=1e5+1e2;

set<int> es[maxn];
queue<int> q;
int vis[maxn];

int fa[maxn],siz[maxn];
inline int findfa(int x) {
    return fa[x] == x ? x : fa[x] = findfa(fa[x]);
}
inline void merge(int x,int y) {
    x = findfa(x) , y = findfa(y);
    if( x == y ) return;
    fa[x] = y , siz[y] += siz[x];
}

int main() {
    static int n,m;
    static long long ans;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , es[a].insert(b);
    for(int i=1;i<=n;i++) fa[i] = i , siz[i] = 1;
    for(int i=1;i<=n;i++)
        for(set<int>::iterator it=es[i].begin();it!=es[i].end();++it)
            if( es[*it].find(i) != es[*it].end() )
                merge(i,*it);
    for(int i=1;i<=n;i++)
        if( es[i].size() > 1 ) {
            const set<int>::iterator it = es[i].begin();
            set<int>::iterator now = it;
            for(++now;now!=es[i].end();++now)
                merge(*it,*now);
        }
    for(int i=1;i<=n;i++)
        if( siz[findfa(i)] > 1 )
            q.push(i) , vis[i] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(set<int>::iterator it=es[pos].begin();it!=es[pos].end();++it) {
            merge(*it,pos);
            if( !vis[*it] ) q.push(*it) , vis[*it] = 1;
        }
    }
    for(int i=1;i<=n;i++) if( findfa(i) == i ) {
        if( siz[i] > 1 ) ans += (long long) siz[i] * ( siz[i] - 1 );
        else ans += es[i].size();
    }
    printf("%lld\n",ans);
    return 0;
}