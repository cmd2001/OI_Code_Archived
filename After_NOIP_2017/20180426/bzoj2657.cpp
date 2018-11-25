#pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
#include<map>
const int maxn=2e5+1e2;

int mx;
namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    __inline void addedge(int from,int to) {
        static int cnt;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline int dfs(int pos,int fa) {
        int ret = 0;
        for(int at=s[pos],son;at;at=nxt[at]) if( t[at] != fa )
                mx = std::max( mx , ret + ( son = dfs(t[at],pos) + 1 ) ) , ret = std::max( ret , son );
        return ret;
    }
}

namespace Build {
    struct Edge {
        int u,v;
        Edge(int uu,int vv) { u = std::min(uu,vv) , v = std::max(uu,vv); }
        friend bool operator < (const Edge &a,const Edge &b) {
            return a.u != b.u ? a.u < b.u : a.v < b.v;
        }
    };
    std::map<Edge,int> mp;
    int lft[maxn<<2],rit[maxn<<2],eid;
    __inline int gid(const Edge &e) {
        return mp.find(e) != mp.end() ? mp[e] : mp[e] = ++eid;
    }
    __inline void pushid(int cur,int id) {
        lft[cur] ? rit[cur] = id : lft[cur] = id;
    }
    __inline void insert(int a,int b,int c,int id) {
        pushid(gid(Edge(a,b)),id) , pushid(gid(Edge(b,c)),id) , pushid(gid(Edge(a,c)),id);
    }
    __inline void build() {
        for(int i=1;i<=eid;i++) if( lft[i] && rit[i] ) Tree::addedge(lft[i],rit[i]) , Tree::addedge(rit[i],lft[i]);
    }
}

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1,a,b,c;i<=n-2;i++) scanf("%d%d%d",&a,&b,&c) , Build::insert(a,b,c,i);
    Build::build() , Tree::dfs(1,-1) , printf("%d\n",mx+1);
    return 0;
}
