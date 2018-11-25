#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2,base=233,mod[2]={1000000009,1000000007};

struct Node {
    lli h,t;
    Node(lli hh=0,lli tt=0) {
        h = hh , t = tt;
    }
    lli id() const {
        return h / 10000;
    }
    friend bool operator < (const Node &a,const Node &b) {
        return a.h != b.h ? a.h < b.h : a.t < b.t;
    }
};
map<Node,int> cov[maxn];
lli hsh[maxn][2],pows[maxn][2];
int dis[maxn],deg[maxn],nxt[maxn][27],vis[maxn];
char in[maxn];
int ed[maxn];
int n,k,ans,cnt;

inline void gen(int len) {
    pows[0][0] = pows[0][1] = 1;
    hsh[0][0] = hsh[0][1] = 0;
    for(int i=1;i<=len;i++)
        for(int j=0;j<2;j++) {
            hsh[i][j] = ( hsh[i-1][j] * base + in[i] - 'a' + 1) % mod[j];
            pows[i][j] = pows[i-1][j] * base % mod[j];
        }
    /*for(int i=1;i<=len;i++)
        debug<<pows[i][0]<<" ";debug<<endl;*/
}

inline Node SegmentHsh(int st,int ed) { // returning hash Node in range [st,ed]
    --st;
    lli h = ( ( hsh[ed][0] - hsh[st][0] * pows[ed-st][0] ) % mod[0] + mod[0] ) % mod[0];
    lli t = ( ( hsh[ed][1] - hsh[st][1] * pows[ed-st][1] ) % mod[1] + mod[1] ) % mod[1];
    return Node(h,t);
}
inline Node SegmentWord(int st,int ed,int x) { // returning Segment [st,ed] + x
    Node Seg = SegmentHsh(st,ed);
    Seg.h = ( Seg.h * base + x ) % mod[0],
    Seg.t = ( Seg.t * base + x ) % mod[1];
    return Seg;
}

inline int query(const Node &a) {
    int iid = a.id();
    return cov[iid].find(a) == cov[iid].end() ? 0 : cov[iid][a];
}
inline void insert(const Node &a) {
    int iid = a.id();
    if( cov[iid].find(a) != cov[iid].end() )
        return;
    //debug<<"inserting "<<a.t<<" "<<a.h<<endl;
    cov[iid][a] = ++cnt;
}

inline void insert_all() {
    for(int i=1;i<=n;i++) {
        for(int j=ed[i-1]+k-1;j<ed[i];j++) {
            /*debug<<"j = "<<j<<endl;*/
            //debug<<"st = "<<j-k+1<<"ed = "<<j<<endl;
            insert(SegmentHsh(j-k+1,j));
        }
    }
}

inline void find_next() {
    for(int i=1;i<=n;i++)
        for(int j=ed[i-1]+k-1;j<ed[i];j++) {
            Node now = SegmentHsh(j-k+1,j);
            int id = query(now);
            if( vis[id] )
                continue;
            vis[id] = 1;
            for(int w=1;w<=26;w++) {
                //debug<<"st = "<<j-k+2<<"ed = "<<j<<endl;
                Node nw = SegmentWord(j-k+2,j,w);
                //debug<<nw.h<<" "<<nw.t<<endl;
                int nid = query(nw);
                if( nid ) {
                    ++deg[nid];
                    nxt[id][w] = nid;
                }
            }
        }
}

inline void topo() {
    int full = 0;
    queue<int> q;
    for(int i=1;i<=cnt;i++)
        if( !deg[i] ) {
            dis[i] = 1 ,
            q.push(i);
        }
    while( q.size() ) {
        const int pos = q.front(); q.pop(); ++full;
        //debug<<"pos = "<<pos<<endl;
        ans = max( ans , dis[pos] );
        for(int i=1;i<=26;i++)
            if( nxt[pos][i] ) {
                dis[nxt[pos][i]] = max( dis[nxt[pos][i]] , dis[pos] + 1 );
                if( !--deg[nxt[pos][i]] )
                    q.push(nxt[pos][i]);
            }
    }
    //debug<<"full = "<<full<<endl;
    if( full < cnt )
        puts("INF");
    else
        printf("%d\n",ans+k-1);
}

inline void getin() {
    ed[0] = 1;
    for(int i=1;i<=n;i++) {
        scanf("%s",in+ed[i-1]);
        ed[i] = ed[i-1] + strlen(in+ed[i-1]);
    }
}

inline void init() {
    for(int i=0;i<maxn;i++)
        cov[i].clear();
    memset(hsh,0,sizeof(hsh));
    memset(pows,0,sizeof(pows));
    memset(dis,0,sizeof(dis));
    memset(deg,0,sizeof(deg));
    memset(nxt,0,sizeof(nxt));
    memset(vis,0,sizeof(vis));
    memset(ed,0,sizeof(ed));
    memset(in,0,sizeof(in));
    ans = cnt = 0;
}

int main() {
    while( scanf("%d%d",&n,&k) == 2 ) {
        //debug<<"new"<<endl;
        //debug<<"n = "<<n<<"k = "<<k<<endl;
        init();
        getin();
        gen(ed[n]-1);
        insert_all();
        find_next();
        //debug<<"cnt = "<<cnt<<endl;
        topo();
    }
}