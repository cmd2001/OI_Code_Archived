#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
const int maxn=2e3+1e2,maxe=1e5+1e2;

struct Node {
    int id,lim;
    friend bool operator < (const Node &a,const Node &b) {
        return a.lim < b.lim;
    }
}ns[maxn];
int s[maxn],t[maxe<<1],nxt[maxe<<1];
int lim[maxn],deg[maxn],tp[maxn],seq[maxn],cnt;
int n;

inline void addedge(int from,int to) {
    static int cnt = 0;
    ++deg[t[++cnt]=to] , nxt[cnt] = s[from] , s[from] = cnt;
}

inline void topo(int ban) {
    memcpy(deg,tp,sizeof(tp)) , cnt = 0;
    std::queue<int> q;
    for(int i=1,cur=1;i<=n;i++) {
        while( cur <= n && ns[cur].lim <= i ) {
            if( !deg[ns[cur].id] && ns[cur].id != ban ) q.push(ns[cur].id);
            ++cur;
        }
        if( q.size() ) {
            const int pos = q.front(); seq[++cnt] = pos , q.pop();
            for(int at=s[pos];at;at=nxt[at]) if( !--deg[t[at]] && lim[t[at]] <= i && t[at] != ban ) q.push(t[at]);
        } else break;
    }
}

int main() {
    static int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",lim+i) , ns[i] = (Node){i,lim[i]=n-lim[i]+1};
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , addedge(b,a);
    std::sort(ns+1,ns+1+n) , memcpy(tp,deg,sizeof(tp));
    for(int i=1;i<=n;i++) topo(i) , printf("%d%c",n-cnt,i!=n?' ':'\n');
    return 0;
}
