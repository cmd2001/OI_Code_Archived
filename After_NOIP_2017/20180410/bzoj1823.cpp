#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2e2+1e1,maxe=1e3+1e2;

int s[maxn],t[maxe<<2],nxt[maxe<<2],cnt;
int dfn[maxn],low[maxn],bel[maxn],stk[maxn],ins[maxn],vis[maxn],iid,top,dd;

inline void addedge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void tarjan(int pos) {
    ins[pos] = vis[stk[++top]=pos] = 1 , low[pos] = dfn[pos] = ++dd;
    for(int at=s[pos];at;at=nxt[at])
        if( !vis[t[at]] ) tarjan(t[at]) , low[pos] = min( low[pos] , low[t[at]] );
        else if( ins[t[at]] ) low[pos] = min( low[pos] , dfn[t[at]] );
    if( low[pos] == dfn[pos] ) {
        ++iid;
        do {
            const int x = stk[top--];
            ins[x] = 0 , bel[x] = iid;
        } while( ins[pos] );
    }
}

inline pair<int,int> explain() {
    static char buf[100];
    static int ret;
    scanf("%s",buf) , sscanf(buf+1,"%d",&ret);
    return make_pair(*buf=='m',ret);
}

inline int cov(int x,int tpe) { // 0 means m , 1 means h .
    return x * 2 - 1 + tpe;
}
inline void reset() {
    memset(s,0,sizeof(s)) , memset(vis,0,sizeof(vis)) ,
    cnt = iid , top = dd = 0;
}

int main() {
    static int T,n,m,ans;
    static pair<int,int> pa,pb;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&m) , reset() , ans = 1;
        for(int i=1;i<=m;i++) {
            pa = explain() , pb = explain();
            addedge(cov(pa.second,pa.first^1),cov(pb.second,pb.first)),
            addedge(cov(pb.second,pb.first^1),cov(pa.second,pa.first));
        }
        for(int i=1;i<=n<<1;i++) if( !vis[i] ) tarjan(i);
        for(int i=1;i<=n;i++) if( bel[cov(i,0)] == bel[cov(i,1)] ) ans = 0;
        puts(ans?"GOOD":"BAD");
    }
    return 0;
}
