#pragma GCC optimize("Ofast")
#include<cstdio>
#include<cstring>
#include<tr1/unordered_map>
#include<vector>
typedef long long int lli;
using namespace std;
using namespace tr1;
const int maxn=17;
const int mod=1e9+7;

inline void adde(int& dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}

int n;

struct Node {
    int dat[maxn];
    Node() { memset(dat,0,sizeof(dat)); }
    int& operator [] (const int &x) { return dat[x]; }
    const int& operator [] (const int &x) const { return dat[x]; }
    friend bool operator == (const Node &a,const Node &b) {
        for(int i=n-1;~i;i--) if( a[i] != b[i] ) return 0;
        return 1;
    }
};
struct Hash_Node {
    size_t operator () (const Node &x) const {
        static const lli Hash_Mod = ( 1ll << 20 ) - 1;
        lli ret = 0;
        for(int i=n-1,mul=1;~i;i--,mul++) ret *= mul , ret += x[i];
        return ret & Hash_Mod;
    }
};

unordered_map<Node,int,Hash_Node> f[2];
vector<int> in[maxn];
bool vis[maxn];
int cur,ans;

inline int calc_Mex() {
    for(int i=0;i<n;i++) if( !vis[i] ) return i;
    return n;
}
inline Node solve_Statement(int x,const unsigned &sta,const Node &cur) {
    memset(vis,0,sizeof(vis));
    for(unsigned i=0;i<in[x].size();i++) if( sta & ( 1 << i ) ) vis[cur[in[x][i]]] = 1;
    Node ret = cur; ret[x] = calc_Mex();
    return ret;
}
inline void solve_Point(unordered_map<Node,int,Hash_Node> &dst,int x,const Node &cur,const int &val) {
    const unsigned fs = 1 << in[x].size();
    for(unsigned i=0;i<fs;i++) adde(dst[solve_Statement(x,i,cur)],val);
}
inline void trans(int p) {
    cur ^= 1 , f[cur].clear();
    for(unordered_map<Node,int,Hash_Node>::iterator it=f[cur^1].begin();it!=f[cur^1].end();++it) // Why no C++11 .
        solve_Point(f[cur],p,it->first,it->second);
}
inline void getans() {
    for(unordered_map<Node,int,Hash_Node>::iterator it=f[cur].begin();it!=f[cur].end();++it) { // Why no C++11 .
        const Node &t = it->first;
        if( t[0] ^ t[1] ) adde(ans,it->second);
    }
}
inline void init() {
    Node t;
    t[n-1] = 0 , f[cur][t] = 1;
}

int main() {
    static int m;
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , in[--a].push_back(--b);
    init(); for(int i=n-2;~i;i--) trans(i);
    getans() , printf("%d\n",ans);
    fclose(stdout);
    return 0;
}

