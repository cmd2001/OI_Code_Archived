#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#define debug cout
using namespace std;
const int maxn=6e2+1e1,maxe=1e5+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxe<<2],nxt[maxe<<2],l[maxe<<2];
int dis[maxn],bel[maxn],dfn[maxn],low[maxn],iid;
bool vis[maxn],ins[maxn],inq[maxn];
unsigned vct[maxn];
stack<int> stk;
int n;

inline void addedge(int from,int to,int len) {
    //debug<<"from = "<<from<<"to = "<<to<<"len = "<<len<<endl;
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void tarjan(int pos) {
    static int cnt = 0;
    vis[pos] = 1;
    low[pos] = dfn[pos] = ++cnt;
    stk.push(pos) , ins[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( !vis[t[at]] ) {
            tarjan(t[at]);
            low[pos] = min( low[pos] , low[t[at]] );
        } else if( ins[t[at]] ) low[pos] = min( low[pos] , dfn[t[at]] );
    if( low[pos] == dfn[pos] ) {
        ++iid;
        do {
            const int x = stk.top(); stk.pop();
            bel[x] = iid , ins[x] = 0;
        } while( ins[pos] );
    }
}
inline int calc(int id) {
    vector<int> ls;
    for(int i=1;i<=n;i++) if( bel[i] == id ) ls.push_back(i);
    int ret = 0;
    for(unsigned i=0;i<ls.size();i++) {
        for(unsigned j=0;j<ls.size();j++) dis[ls[j]] = inf , vct[ls[j]] = 0;
        const int now = ls[i]; dis[now] = 0;
        queue<int> q; q.push(now) , inq[now] = 1;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , inq[pos] = 0;
            if( ++vct[pos] > ( ls.size()<<1 ) ) return -1; // no solution
            for(int at=s[pos];at;at=nxt[at]) {
                if( bel[t[at]] != id ) continue;
                if( dis[t[at]] > dis[pos] + l[at] ) {
                    dis[t[at]] = dis[pos] + l[at];
                    if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
                }
            }
        }
        for(unsigned j=0;j<ls.size();j++) ret = max( ret , dis[ls[j]] );
    }
    return ++ret;
}
inline int getans() {
    int ret = 0 , now = 0;
    for(int i=1;i<=iid;i++) {
        now = calc(i);
        if( !~now ) return -1;
        ret += now;
    }
    return ret;
}
inline void pre() {
    for(int i=1;i<=n;i++) if( !vis[i] ) tarjan(i);
}

int main() {
    static int m1,m2,ans;
    scanf("%d%d%d",&n,&m1,&m2);
    for(int i=1,a,b;i<=m1;i++) {
        scanf("%d%d",&a,&b);
        addedge(a,b,1) , addedge(b,a,-1);
    }
    for(int i=1,a,b;i<=m2;i++) {
        scanf("%d%d",&a,&b);
        addedge(b,a,0);
    }
    pre();
    ans = getans();
    if( !~ans ) puts("NIE");
    else printf("%d\n",ans);
    return 0;
}
