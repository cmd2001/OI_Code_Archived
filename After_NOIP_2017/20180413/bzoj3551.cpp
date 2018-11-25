#include<cstdio>
#include<algorithm>
#include<cctype>
const int maxn=1e5+1e2,maxq=5e5+1e2,maxe=7e6+1e2;
const int inf=0x3f3f3f3f;

int in[maxn],srt[maxn],len;
int n,m;

struct SegmentTree {
    int lson[maxe],rson[maxe],sum[maxe],cnt;
    inline void insert(int& pos,int l,int r,const int &tar) {
        if( !pos ) pos = ++cnt; sum[pos] = 1;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],l,mid,tar);
        else insert(rson[pos],mid+1,r,tar);
    }
    inline int merge(int p1,int p2,int l,int r) {
        if( !sum[p1] || !sum[p2] ) return sum[p1] ? p1 : p2;
        const int ret = ++cnt , mid = ( l + r ) >> 1;
        sum[ret] = sum[p1] + sum[p2];
        lson[ret] = merge(lson[p1],lson[p2],l,mid) ,
        rson[ret] = merge(rson[p1],rson[p2],mid+1,r);
        return ret;
    }
    inline int kth(int pos,int l,int r,int k) {
        if( !pos || k > sum[pos] ) return -1;
        if( l == r ) return l;
        const int mid = ( l + r ) >> 1;
        if( k <= sum[rson[pos]] ) return kth(rson[pos],mid+1,r,k);
        else return kth(lson[pos],l,mid,k-sum[rson[pos]]);
    }
}segt;

struct UnionFindSet {
    int fa[maxn<<1];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline void merge(int x,int y) {
        fa[x] = y;
    }
    inline void init() {
        for(int i=1;i<=n<<1;i++) fa[i] = i;
    }
}ufs;

namespace Tree {
    int s[maxn<<1],t[maxn<<1],nxt[maxn<<1];
    int anc[maxn<<1][20],val[maxn<<1],root[maxn<<1],cnt; // val[0] = inf .
    inline void addedge(int from,int to) {
        static int cnt = 0;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void dfs(int pos,int fa) {
        anc[pos][0] = fa;
        for(int at=s[pos];at;at=nxt[at]) dfs(t[at],pos) , root[pos] = segt.merge(root[pos],root[t[at]],1,len);
    }
    inline void initanc() {
        for(int j=1;j<20;j++) for(int i=1;i<=cnt;i++) anc[i][j] = anc[anc[i][j-1]][j-1];
    }
    inline int findmx(int pos,int lim) {
        for(int i=19;~i;i--) if( val[anc[pos][i]] <= lim ) pos = anc[pos][i];
        return pos;
    }
    inline int query(int st,int lim,int k) {
        int mx = findmx(st,lim);
        return segt.kth(root[mx],1,len,k);
    }
}

struct Edge {
    int a,b,l;
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.l < b.l;
    }
}es[maxq];

inline void buildtree() {
    using namespace Tree;
    cnt = n , ufs.init();
    for(int i=1;i<=n;i++) segt.insert(root[i],1,len,in[i]);
    for(int i=1;i<=m;i++) if( ufs.findfa(es[i].a) != ufs.findfa(es[i].b) ) {
        int fa = ufs.findfa(es[i].a) , fb = ufs.findfa(es[i].b);
        val[++cnt] = es[i].l , addedge(cnt,fa) , addedge(cnt,fb);
        ufs.merge(fa,cnt) , ufs.merge(fb,cnt);
    }
    val[0] = inf , dfs(cnt,0) , initanc();
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int q,lastans;
    n = getint() , m = getint() , q = getint();
    for(int i=1;i<=n;i++) srt[i] = in[i] = getint();
    std::sort(srt+1,srt+1+n) , len = std::unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++) in[i] = std::lower_bound(srt+1,srt+1+len,in[i]) - srt;
    for(int i=1;i<=m;i++) es[i].a = getint() , es[i].b = getint() , es[i].l = getint();
    std::sort(es+1,es+1+m) , buildtree();
    for(int i=1,v,x,k;i<=q;i++) {
        v = getint() ^ lastans , x = getint() ^ lastans , k = getint() ^ lastans;
        lastans = Tree::query(v,x,k);
        printf("%d\n",(~lastans)?srt[lastans]:-1) , lastans = (~lastans) ? srt[lastans] : 0;
    }
    return 0;
}

