#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1.6e3+1e2,maxt=43,maxe=1e3+1e2;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

int col[maxt][maxt],id[maxt][maxt],n,m;

namespace Graph {
    int s[maxn],t[maxn<<2],nxt[maxn<<2],fa[maxn],vis[maxn],cnt,tim;
    bool ban[maxn];
    inline void addedge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline bool dfs(int pos) {
        for(int at=s[pos];at;at=nxt[at]) if( vis[t[at]] != tim && !ban[t[at]] ) {
            vis[t[at]] = tim;
            if( !fa[t[at]] || dfs(fa[t[at]]) ) return fa[t[at]] = pos , 1;
        }
        return 0;
    }
    inline void pir() { // col of blk is 1 .
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( !col[i][j] ) ++tim , dfs(id[i][j]);
    }
    inline bool must(int blk) {
        pir();
        if( !fa[blk] ) return 0;
        ban[blk] = 1 , ++tim;
        return !dfs(fa[blk]);
    }
    inline void reset() {
        memset(s,0,sizeof(s)) , memset(ban,0,sizeof(ban)) , memset(fa,0,sizeof(fa)) , memset(vis,0,sizeof(vis)) , cnt = tim = 0;
    }
}

char in[maxt][maxt];

inline void build(const char &nxt) {
    int tmp = -1; Graph::reset();
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( in[i][j] == '.' ) tmp = ( i + j ) & 1;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) col[i][j] = ( ( i + j ) & 1 ) == tmp;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( !col[i][j] && in[i][j] == nxt ) {
        for(int k=0;k<4;k++) {
            const int tx = i + dx[k] , ty = j + dy[k];
            if( 0 < tx && tx <= n && 0 < ty && ty <= m && in[tx][ty] != nxt ) Graph::addedge(id[i][j],id[tx][ty]);
        }
    }
}
inline void modify(int x,int y) {
    for(int i=0;i<4;i++) {
        const int tx = x + dx[i] , ty = y + dy[i];
        if( 0 < tx && tx <= n && 0 < ty && ty <= m && in[tx][ty] == '.' ) {
            swap(in[x][y],in[tx][ty]);
            break;
        }
    }
}
inline int findblk() {
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if( in[i][j] == '.' ) return id[i][j];
    throw "No blank";
}

bool tpe[maxe<<1];
int ox[maxe<<1],oy[maxe<<1],t,ans[maxe],anslen;

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1,tmp=0;i<=n;i++) {
        scanf("%s",in[i]+1);
        for(int j=1;j<=m;j++) id[i][j] = ++tmp;
    }
    scanf("%d",&t) , t <<= 1;
    for(int i=1;i<=t;i++) scanf("%d%d",ox+i,oy+i);
    for(int i=1;i<=t;i++) {
        bool before,after;
        if( i & 1 ) {
            build('O') , before = Graph::must(findblk());
            modify(ox[i],oy[i]) , build('X') , after = Graph::must(findblk());
            if( before && after ) ans[++anslen] = ( i + 1 ) >> 1;
        } else modify(ox[i],oy[i]);
    }
    printf("%d\n",anslen);
    for(int i=1;i<=anslen;i++) printf("%d\n",ans[i]);
    return 0;
}
