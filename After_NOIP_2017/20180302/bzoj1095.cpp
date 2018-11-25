#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1e5+1e2;
const int inf=0x3f3f3f3f;

struct Heap {
    priority_queue<int> rem,del;
    inline void clear() {
        while( del.size() && rem.top() == del.top() ) rem.pop() , del.pop();
    }
    inline void pop() {
        clear() , rem.pop();
    }
    inline int top() {
        clear();
        return rem.top();
    }
    inline void push(int x) {
        rem.push(x);
    }
    inline void erase(int x) {
        del.push(x);
    }
    inline int dual() {
        int x = top(); pop();
        int y = top(); push(x);
        return x + y;
    }
    inline int size() {
        return rem.size() - del.size();
    }
}full,ns[maxn],ss[maxn]; // ns :: dis to all nodes , ss :: max dis of sons .

int s[maxn],t[maxn<<1],nxt[maxn<<1],sta[maxn]; // sta == 0 means off , 1 means on .

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
namespace TCDC {
    int siz[maxn],dep[maxn],fa[maxn],son[maxn],top[maxn];
    inline void pre(int pos) {
        siz[pos] = 1;
        for(int at=s[pos];at;at=nxt[at])
            if( t[at] != fa[pos] ) {
                fa[t[at]] = pos ,dep[t[at]] = dep[pos] + 1;
                pre(t[at]) , siz[pos] += siz[t[at]];
                if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
            }
    }
    inline void dfs(int pos) {
        top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
        for(int at=s[pos];at;at=nxt[at])
            if( t[at] != fa[pos] )
                dfs(t[at]);
    }
    inline int lca(int x,int y) {
        while( top[x] != top[y] )
            if( dep[top[x]] > dep[top[y]] ) x = fa[top[x]];
            else y = fa[top[y]];
        return dep[x] < dep[y] ? x : y;
    }
    inline int dis(int x,int y) {
        return dep[x] + dep[y] - (dep[lca(x,y)]<<1);
    }
}

namespace DPDC {
    int dfa[maxn];
    int blksiz[maxn],siz[maxn],cal[maxn],dis[maxn],ban[maxn];
    
    inline void getrt(int pos,int fa,int fs,int& rt) {
        cal[pos] = 0 , siz[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) {
            if( ban[t[at]] || t[at] == fa ) continue;
            getrt(t[at],pos,fs,rt) ,
            siz[pos] += siz[t[at]] ,
            cal[pos] = max( cal[pos] , siz[t[at]] );
        }
        cal[pos] = max( cal[pos] , fs - siz[pos] );
        if( cal[pos] < cal[rt] ) rt = pos;
    }
    inline void build(int pos,int bs,int fa) {
        if( bs == 1 ) {
            dfa[pos] = fa;
            return;
        }
        int rt = 0 ; *cal = inf;
        getrt(pos,-1,bs,rt);
        dfa[rt] = fa , ban[rt] = 1;
        for(int at=s[rt];at;at=nxt[at])
            if( !ban[t[at]] )blksiz[t[at]] = siz[rt] > siz[t[at]] ? siz[t[at]] : bs - siz[rt];
        for(int at=s[rt];at;at=nxt[at])
            if( !ban[t[at]]) build(t[at],blksiz[t[at]],rt);
    }
    inline void erase(Heap &h) {
        if( h.size() < 2 ) return;
        const int t = h.dual();
        full.erase(t);
    }
    inline void push(Heap &h) {
        if( h.size() < 2 ) return;
        const int t = h.dual();
        full.push(t);
    }
    inline void black(int x) {
        erase(ss[x]);
        ss[x].push(0);
        push(ss[x]);
        for(int i=x;dfa[i];i=dfa[i]) {
            erase(ss[dfa[i]]);
            if(ns[i].size()) ss[dfa[i]].erase(ns[i].top());
            ns[i].push(TCDC::dis(x,dfa[i]));
            if(ns[i].size()) ss[dfa[i]].push(ns[i].top());
            push(ss[dfa[i]]);
        }
    }
    inline void white(int x) {
        erase(ss[x]);
        ss[x].erase(0);
        push(ss[x]);
        for(int i=x;dfa[i];i=dfa[i]) {
            erase(ss[dfa[i]]);
            if(ns[i].size()) ss[dfa[i]].erase(ns[i].top());
            ns[i].erase(TCDC::dis(x,dfa[i]));
            if(ns[i].size()) ss[dfa[i]].push(ns[i].top());
            push(ss[dfa[i]]);
        }
    }
}

int main() {
    static int n,m,siz;
    static char o[10];
    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++) {
        scanf("%d%d",&a,&b) ,
        addedge(a,b) , addedge(b,a);
    }
    TCDC::pre(1) , TCDC::dfs(1);
    DPDC::build(1,n,0);
    for(int i=1;i<=n;i++) DPDC::black(i);
    siz = n;
    scanf("%d",&m);
    for(int i=1,x;i<=m;i++) {
        scanf("%s",o);
        if( *o == 'G' ) {
            if( siz <= 1 ) printf("%d\n",siz-1);
            else printf("%d\n",full.top());
        } else if( *o == 'C' ) {
            scanf("%d",&x);
            if( !sta[x] ) DPDC::white(x) , --siz;
            else DPDC::black(x) , ++siz;
            sta[x] ^= 1;
        }
    }
    return 0;
}
