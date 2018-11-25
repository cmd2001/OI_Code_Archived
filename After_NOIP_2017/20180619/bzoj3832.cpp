#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=5e5+1e2,maxe=1e6+1e2;
const int inf=0x3f3f3f3f;

int seq[maxn],sql,n;
bool vis[maxn];

struct Graph {
    int s[maxn],t[maxe],nxt[maxe],deg[maxn],f[maxn],cnt;
    const int& operator [] (const int &x) const { return f[x]; }
    inline void addedge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt , ++deg[to];
    }
    inline void topo(bool me) {
        queue<int> q;
        for(int i=1;i<=n;i++) if( !deg[i] ) q.push(i);
        while( q.size() ) {
            const int pos = q.front(); q.pop() , f[pos] = max( f[pos] , 1 );
            if(me) seq[++sql] = pos;
            for(int at=s[pos];at;at=nxt[at]) {
                f[t[at]] = max( f[t[at]] , f[pos] + 1 );
                if( !--deg[t[at]] ) q.push(t[at]);
            }
        }
    }
}f,g;

struct Heap {
    priority_queue<int> pq,del;
    inline void fix() {
        while( del.size() && pq.top() == del.top() ) pq.pop() , del.pop();
    }
    inline void insert(int x) {
        fix() , pq.push(x);
    }
    inline void remove(int x) {
        fix() , del.push(x);
    }
    inline int top() {
        return fix() , pq.top();
    }
}hp;

inline char nextchar() {
    const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    static int m,ans,len=inf;
    n = getint() , m = getint();
    for(int i=1,a,b;i<=m;i++) a = getint() , b = getint() , f.addedge(a,b) , g.addedge(b,a);
    f.topo(1) , g.topo(0) , hp.insert(0);
    for(int i=1;i<=n;i++) hp.insert(g[i]);
    for(int i=1;i<=sql;i++) {
        const int pos = seq[i];
        for(int at=g.s[pos];at;at=g.nxt[at]) if( !vis[g.t[at]] ) hp.remove(f[g.t[at]]+g[pos]) , vis[g.t[at]] = 1;
        for(int at=g.s[pos];at;at=g.nxt[at]) vis[g.t[at]] = 0;
        hp.remove(g[pos]);
        if( hp.top() < len ) ans = pos , len = hp.top();
        for(int at=f.s[pos];at;at=f.nxt[at]) if( !vis[f.t[at]] ) hp.insert(f[pos]+g[f.t[at]]) , vis[f.t[at]] = 1;
        for(int at=f.s[pos];at;at=f.nxt[at]) vis[f.t[at]] = 0;
        hp.insert(f[pos]);
    }
    printf("%d %d\n",ans,len-1);
    return 0;
}

