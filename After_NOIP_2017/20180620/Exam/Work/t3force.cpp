#include<bits/stdc++.h>
using namespace std;
const int maxn=10;

int ans[maxn],n,fs;
struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline void merge(int x,int y) {
        x = findfa(x) , y = findfa(y);
        if( x != y ) fa[x] = y; 
    }
    inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

inline int calc(int sta) {
    int ret = 0; ufs.init();
    for(int i=1;i<=n;i++) for(int j=1;j<i;j++) {
        if( sta & 1 ) ufs.merge(i,j);
        sta >>= 1;
    }
    for(int i=1;i<=n;i++) if( ufs.findfa(i) == i ) ++ret;
    return ret;
}

int main() {
    scanf("%d",&n) , fs = 1 << ( n*(n-1)>>1 );
    for(int i=0;i<fs;i++) ++ans[calc(i)];
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    puts("");
    return 0;
}