#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

struct Node {
    int x,y,id;
    friend bool operator < (const Node &a,const Node &b) {
        return a.y < b.y;
    }
}in[maxn];
inline bool cmp(const Node &a,const Node &b) {
    return a.x < b.x;
}
multiset<Node> ms;

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline bool merge(int x,int y) {
        return x = findfa(x) , y = findfa(y) , x == y ? 0 : fa[x] = y;
    }
    inline void init(int n) {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

int siz[maxn],mx,fs;
int n,c,l;

int main() {
    scanf("%d%d",&n,&c);
    for(int i=1,a,b;i<=n;i++) scanf("%d%d",&a,&b) , in[i] = (Node){a+b,a-b,i};
    sort(in+1,in+1+n,cmp) , ufs.init(fs=n) , ms.insert(in[l=1]);
    for(int i=2;i<=n;i++) {
        while( l < i && (lli) in[i].x - in[l].x > c ) ms.erase(ms.find(in[l++]));
        multiset<Node>::iterator it = ms.lower_bound(in[i]);
        if( it != ms.end() ) {
            if( it->y - in[i].y <= c )fs -= ufs.merge(in[i].id,it->id);
        } if( it != ms.begin() ) {
            --it;
            if( (lli) in[i].y - it->y <= c ) fs -= ufs.merge(in[i].id,it->id);
        }
        ms.insert(in[i]);
    }
    for(int i=1;i<=n;i++) mx = max( mx , ++siz[ufs.findfa(i)] );
    printf("%d %d\n",fs,mx);
    return 0;
}
