#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
typedef long long int lli;
const int maxn=3e4+1e2,maxe=6e4+1e2;
const int inf=0x3f3f3f3f,minf=0xefefefef;

int n,k,mxlen,cont;
lli tar;

namespace SP {
    int s[maxn],t[maxe<<1],nxt[maxe<<1],l[maxe<<1],dis[maxn];

    struct Node {
        int d,p;
        friend bool operator < (const Node &a,const Node &b) {
            return a.d > b.d;
        }
    };
    std::priority_queue<Node> q;
    
    inline void coredge(int from,int to,int len) {
        static int cnt;
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b,int l) {
        coredge(a,b,l) , coredge(b,a,l);
    }
    inline void work() {
        memset(dis,0x3f,sizeof(dis)) , dis[1] = 0;
        q.push((Node){0,1});
        while( q.size() ) {
            const Node cur = q.top(); q.pop();
            if( cur.d != dis[cur.p] ) continue;
            const int pos = cur.p;
            for(int at=s[pos];at;at=nxt[at]) if( dis[t[at]] > dis[pos] + l[at] ) q.push((Node){dis[t[at]]=dis[pos]+l[at],t[at]});
        }
    }
}

namespace PDAC {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
    int siz[maxn],mxs[maxn];
    bool ban[maxn];
    
    inline void coredge(int from,int to,int len) {
        static int cnt;
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b,int l) {
        coredge(a,b,l) , coredge(b,a,l);
    }
    
    inline void findrt(int pos,int fa,const int &fs,int &rt) {
        siz[pos] = 1 , mxs[pos] = 0;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) findrt(t[at],pos,fs,rt) , siz[pos] += siz[t[at]] , mxs[pos] = std::max( mxs[pos] , siz[t[at]] );
        if( ( mxs[pos] = std::max( mxs[pos] , fs - siz[pos] ) ) < mxs[rt] ) rt = pos;
    }

    namespace Solve1 {
        int f[maxn],g[maxn]; // f is cur , g is prefix sum .
        inline int dfs(int pos,int fa,int dep,int dis) {
            int ret = 1;
            f[dep] = std::max( f[dep] , dis );
            for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) ret = std::max( ret , dfs(t[at],pos,dep+1,dis+l[at]) + 1 );
            return ret;
        }
        inline void solve(int pos,int fs) {
            if( fs == 1 ) return;
            int rt = 0 , mxd = 0 , ths = 0;
            *mxs = inf , findrt(pos,-1,fs,rt) , ban[rt] = 1 , g[0] = 0;
            for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) {
                for(int i=0;i<=ths;i++) f[i] = minf;
                mxd = std::max( mxd , ths = dfs(t[at],rt,1,l[at]) );
                for(int i=0;i<=ths&&i+1<=k;i++) mxlen = std::max( mxlen , f[i] + g[k-i-1] );
                for(int i=0;i<=ths;i++) g[i] = std::max( g[i] , f[i] );
            }
            for(int i=0;i<=mxd;i++) f[i] = g[i] = minf;
            for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) solve(t[at],siz[t[at]]<siz[rt]?siz[t[at]]:fs-siz[rt]);
        }
    }
    namespace Solve2 {
        std::map<lli,int> f,g;
        inline void dfs(int pos,int fa,int dep,int dis) {
            ++f[(lli)dep*inf+dis];
            for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) dfs(t[at],pos,dep+1,dis+l[at]);
        }
        inline void solve(int pos,int fs) {
            if( fs == 1 ) return;
            int rt = 0;
            *mxs = inf , findrt(pos,-1,fs,rt) , ban[rt] = 1 , g.clear() , g[0] = 1;
            for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) {
                f.clear() , dfs(t[at],rt,1,l[at]);
                for(std::map<lli,int>::iterator it=f.begin();it!=f.end();it++) {
                    const lli ned = tar - it->first - inf;
                    if( ned >= 0 && g.find(ned) != g.end() ) cont += it->second * g[ned];
                }
                for(std::map<lli,int>::iterator it=f.begin();it!=f.end();it++) g[it->first] += it->second;
            }
            for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) solve(t[at],siz[t[at]]<siz[rt]?siz[t[at]]:fs-siz[rt]);
        }
    }
    inline void work() {
        memset(Solve1::f,0xef,sizeof(Solve1::f)) , memset(Solve1::g,0xef,sizeof(Solve1::g));
        Solve1::solve(1,n) , memset(ban,0,sizeof(ban)) , tar = (lli) k * inf + mxlen , Solve2::solve(1,n);
    }
}

namespace Build {
    using SP::dis;
    struct Edge {
        int tar,len;
        friend bool operator < (const Edge &a,const Edge &b) {
            return a.tar < b.tar;
        }
    };
    std::vector<Edge> es[maxn];
    bool vis[maxn];
    
    inline void dfs(int pos) {
        vis[pos] = 1;
        if(es[pos].size()) std::sort(es[pos].begin(),es[pos].end());
        for(unsigned i=0;i<es[pos].size();i++) if( !vis[es[pos][i].tar] ) PDAC::addedge(pos,es[pos][i].tar,es[pos][i].len) , dfs(es[pos][i].tar);
    }
    inline void work() {
        using namespace SP;
        for(int pos=1;pos<=n;pos++) for(int at=s[pos];at;at=nxt[at]) if( dis[t[at]] == dis[pos] + l[at] ) es[pos].push_back((Edge){t[at],l[at]});
        dfs(1);
    }
}

int main() {
    static int m;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1,a,b,l;i<=m;i++) scanf("%d%d%d",&a,&b,&l) , SP::addedge(a,b,l);
    SP::work() , Build::work() , PDAC::work() , printf("%d %d\n",mxlen,cont);
    return 0;
}
