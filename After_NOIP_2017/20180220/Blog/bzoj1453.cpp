#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2e2+1e1,maxl=8e2+1e1;
 
int in[maxn][maxn],tp[maxl];
int n;
 
struct UnionFindSet {
    int fa[maxl];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline void merge(int x,int y) {
        x = findfa(x) , y = findfa(y);
        if( x != y ) fa[x] = y;
    }
    inline void resfa(int k) {
        for(int i=1;i<=k;i++) fa[i] = i;
    }
}ufs;
 
struct Node {
    int fal[maxn],far[maxn],sta[maxn<<1],l,r,inb,inw; // sta means a number's appear place .
    Node() {
        memset(fal,0,sizeof(fal));
        memset(far,0,sizeof(far));
        memset(sta,0,sizeof(sta));
        l = r = inb = inw = 0;
    }
    inline void rebuild() {
        static int cov[maxl] , cnt;
        memset(cov,0,sizeof(cov)) , cnt = 0;
        for(int i=1;i<=n;i++) if( !cov[fal[i]] ) cov[fal[i]] = ++cnt;
        for(int i=1;i<=n;i++) if( !cov[far[i]] ) cov[far[i]] = ++cnt;
        for(int i=1;i<=n;i++) fal[i] = cov[fal[i]] , sta[fal[i]] |= 1; // 1 means appeared on left .
        for(int i=1;i<=n;i++) far[i] = cov[far[i]] , sta[far[i]] |= 2; // 2 means appeared on right .
    }
    inline void getfa() {
        for(int i=1;i<=n;i++) fal[i] = ufs.findfa(fal[i]) , far[i] = ufs.findfa(far[i]);
    }
    friend Node operator + (const Node &a,const Node &fakeb) { // we have to operate b.
        Node ret,b=fakeb;
        ret.l = a.l , ret.r = b.r , ret.inb = a.inb + b.inb , ret.inw = a.inw + b.inw;
        int mil = a.r , mir = b.l;
        ufs.resfa(n<<2) , memset(tp,0,sizeof(tp));
        for(int i=1;i<=n;i++)
            b.fal[i] += n<<1 , b.far[i] += n<<1;
        memcpy(ret.fal,a.fal,sizeof(a.fal)) , memcpy(ret.far,b.far,sizeof(b.far));
        for(int i=1;i<=n;i++)
            if( in[i][mil] == in[i][mir] ) ufs.merge(a.far[i],b.fal[i]);
        for(int i=1;i<=n;i++)
            tp[ufs.findfa(ret.fal[i])] |= 1 , tp[ufs.findfa(ret.far[i])] |= 2;
        for(int i=1;i<=n;i++) {
            if( !tp[ufs.findfa(a.far[i])] ) {
                tp[ufs.findfa(a.far[i])] = 4;
                if( in[i][mil] == 0 ) ++ret.inw;
                else ++ret.inb;
            }
            if( !tp[ufs.findfa(b.fal[i])] ) {
                tp[ufs.findfa(b.fal[i])] = 4;
                if( in[i][mir] == 0 ) ++ret.inw;
                else ++ret.inb;
            }
        }
        ret.getfa() , ret.rebuild();
        return ret;       
    }
    inline void set(int p) {
        l = r = p , inb = inw = 0;
        int c = 0;
        for(int i=1;i<=n;i++) {
            if( i == 1 || in[i][p] != in[i-1][p] ) fal[i] = far[i] = ++c , sta[c] = 3;
            else fal[i] = far[i] = fal[i-1];
        }
    }
    inline void count(int& retb,int& retw) {
        static bool vis[maxn<<1];
        memset(vis,0,sizeof(vis));
        retb = inb , retw = inw;
        for(int i=1;i<=n;i++)
            if( !vis[fal[i]] ) {
                vis[fal[i]] = 1;
                if( in[i][l] == 0 ) ++retw;
                else ++retb;
            }
        for(int i=1;i<=n;i++)
            if( !vis[far[i]] ) {
                vis[far[i]] = 1;
                if( in[i][r] == 0 ) ++retw;
                else ++retb;
            }
    }
}ns[maxn<<3];
 
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],cnt;
 
inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) {
        ns[pos].set(ll);
        return;
    } const int mid = ( ll + rr ) >> 1;
    build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
    ns[pos] = ns[lson[pos]] + ns[rson[pos]];
}
inline void update(int pos,int tar) {
    if( tar < l[pos] || r[pos] < tar ) return;
    if( l[pos] == r[pos] ) {
        ns[pos].set(l[pos]);
        return;
    }
    update(lson[pos],tar) , update(rson[pos],tar);
    ns[pos] = ns[lson[pos]] + ns[rson[pos]];
}
 
inline void printans() {
    static int ab,aw;
    ns[1].count(ab,aw);
    printf("%d %d\n",ab,aw);
}
int main() {
    static int m;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",in[i]+j);
    build(cnt=1,1,n);
    scanf("%d",&m);
    for(int i=1,x,y;i<=m;i++) {
        scanf("%d%d",&x,&y);
        in[x][y] = !in[x][y];
        update(1,y);
        printans();
    }
    return 0;
}
