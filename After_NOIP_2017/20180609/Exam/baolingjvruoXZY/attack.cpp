#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<vector>
#include<queue>
#include<cassert>
#define debug cout
using namespace std;
const int maxn=3e4+1e2,maxe=1e5+1e2,maxr=3e6+1e2;
const int inf=0x3f3f3f3f;

struct Node {
    int id,siz;
    friend bool operator < (const Node &a,const Node &b) {
        return a.siz != b.siz ? a.siz < b.siz : a.id < b.id;
    }
};
int n,m;
int u[maxe],v[maxe],f[maxe]; // from u to v , flow is f .
vector<int> rs[maxr];
set<Node> hav[maxn];
int rcnt;

namespace FindRing {
    int s[maxn],t[maxe<<1],nxt[maxe<<1],l[maxe<<1],deg[maxn]; // deg is output degree .
    inline void addedge(int from,int to,int lim) {
        static int cnt = 0;
        //debug<<"from = "<<from<<"to = "<<to<<"lim = "<<lim<<endl;
        t[++cnt] = to , l[cnt] = lim , nxt[cnt] = s[from] , s[from] = cnt , deg[from] += lim;
    }
    inline bool dfs(int pos,int st,int dep) {
        if( pos == st && dep ) {
            ++rcnt;
            return 1;
        }
        for(int &at=s[pos];at;at=nxt[at]) if( l[at] ) {
            --l[at];
            /*if( dfs(t[at],st,dep+1) ) {
                rs[rcnt].push_back(pos);
                --deg[pos];
                return 1;
            } else ++l[at];*/
            assert(dfs(t[at],st,dep+1));
            rs[rcnt].push_back(pos) , --deg[pos];
            return 1;
        }
        return 0;
    }
    inline void find_all() {
        for(int i=1;i<=n;i++) while(deg[i]) {
            //debug<<"i = "<<i<<endl;
            assert(dfs(i,i,0)); // what are you doing ?
            for(unsigned j=0;j<rs[rcnt].size();j++) hav[rs[rcnt][j]].insert((Node){rcnt,(int)rs[rcnt].size()});
            reverse(rs[rcnt].begin(),rs[rcnt].end());
        }
    }
    inline void merge_ring(int ra,int rb,int cent) {
        static int dat[maxr],cnt;
        unsigned fa , fb;
        cnt = 0;
        for(unsigned i=0;i<rs[ra].size();i++) if( rs[ra][i] == cent ) { fa = i; break; }
        for(unsigned i=0;i<rs[rb].size();i++) if( rs[rb][i] == cent ) { fb = i; break; }
        for(unsigned i=0;i<fa;i++) dat[++cnt] = rs[ra][i];
        dat[++cnt] = cent;
        for(unsigned j=fb+1;j<rs[rb].size();j++) dat[++cnt] = rs[rb][j];
        for(unsigned j=0;j<fb;j++) dat[++cnt] = rs[rb][j];
        dat[++cnt] = cent;
        for(unsigned i=fa+1;i<rs[ra].size();i++) dat[++cnt] = rs[ra][i];
        rs[ra].clear() , rs[rb].clear();
        for(int i=1;i<=cnt;i++) rs[ra].push_back(dat[i]);
    }
    inline void merge_all() {
        for(int i=1;i<=n;i++) while(hav[i].size()>=2) {
            set<Node>::iterator it = hav[i].begin();
            const Node a = *it , b = *++it;
            for(unsigned j=0;j<rs[a.id].size();j++) if( hav[rs[a.id][j]].find(a) != hav[rs[a.id][j]].end() ) hav[rs[a.id][j]].erase(a);
            for(unsigned j=0;j<rs[b.id].size();j++) if( hav[rs[b.id][j]].find(b) != hav[rs[b.id][j]].end() ) hav[rs[b.id][j]].erase(b);
            merge_ring(a.id,b.id,i); // avoid erasing null iterator .
            for(unsigned j=0;j<rs[a.id].size();j++) hav[rs[a.id][j]].insert((Node){a.id,(int)rs[a.id].size()});
        }
    }
}

namespace NetworkFlow {
    int s[maxn],t[maxe<<1],nxt[maxe<<1],f[maxe<<1];
    int dep[maxn],st,ed;
    inline void coredge(int from,int to,int flow) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow) {
        coredge(from,to,flow) , coredge(to,from,0);
    }
    inline bool bfs() {
        memset(dep,-1,sizeof(dep)) , dep[st] = 0;
        queue<int> q; q.push(st);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int at=s[pos];at;at=nxt[at]) if( f[at] && !~dep[t[at]] ) dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
        }
        return ~dep[ed];
    }
    inline int dfs(int pos,int flow) {
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at]) if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(flow,f[at])) , ret += now , flow -= now , f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline int dinic() {
        int ret = 0;
        while( bfs() ) ret += dfs(st,inf);
        return ret;
    }
}

namespace Graph {
    int s[maxn],t[maxe<<1],nxt[maxe<<1],f[maxe<<1],su;
    inline void addedge(int from,int to,int flow) {
        static int cnt = 0;
        t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
        if( from == 1 ) su += flow;
    }
    inline void print_ring(int id,int cent) {
        unsigned fd;
        for(unsigned i=0;i<rs[id].size();i++) if( rs[id][i] == cent ) { fd = i; break; }
        printf("%d ",cent);
        for(unsigned i=fd+1;i<rs[id].size();i++) printf("%d ",rs[id][i]);
        for(unsigned i=0;i<fd;i++) printf("%d ",rs[id][i]);
        printf("%d ",cent);
    }
    inline void dfs(int pos) {
        if( hav[pos].size() ) {
            print_ring(hav[pos].begin()->id,pos);
            const Node a = *hav[pos].begin();
            for(unsigned j=0;j<rs[a.id].size();j++) if( hav[rs[a.id][j]].find(a) != hav[rs[a.id][j]].end() ) hav[rs[a.id][j]].erase(a);
        } else printf("%d ",pos);
        if( pos == n ) return void(putchar('\n'));
        for(int &at=s[pos];at;at=nxt[at]) if( f[at] ) { dfs(t[at]) , --f[at]; return; }
    }
    inline void getans() {
        while(su--) dfs(1);
    }
}

inline void re_copy() {
    for(int i=1;i<=m;i++) {
        FindRing::addedge(u[i],v[i],NetworkFlow::f[i<<1]);
        Graph::addedge(u[i],v[i],f[i]-NetworkFlow::f[i<<1]);
    }
}

int main() {
    freopen("attack.in","r",stdin);
    freopen("attack.out","w",stdout);
    scanf("%d%d",&n,&m) , NetworkFlow::st = 1 , NetworkFlow::ed = n;
    for(int i=1;i<=m;i++) scanf("%d%d%d",u+i,v+i,f+i) , NetworkFlow::singledge(u[i],v[i],f[i]);
    NetworkFlow::dinic() , re_copy();
    FindRing::find_all() , FindRing::merge_all() , Graph::getans();
    return fclose(stdout);
}
