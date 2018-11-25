#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=8e4+1e2,maxl=20;

struct ChairmanTree {
    int l[maxn*200],r[maxn*200],lson[maxn*200],rson[maxn*200],sum[maxn*200],cnt;
    inline int NewNode() {
        return ++cnt;
    }
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=NewNode(),ll,mid);
        build(rson[pos]=NewNode(),mid+1,rr);
    }
    inline void insert(int pos,int pre,int x) {
        l[pos] = l[pre] , r[pos] = r[pre] ,
        lson[pos] = lson[pre] , rson[pos] = rson[pre];
        if( l[pos] == r[pos] ) {
            sum[pos] = sum[pre] + 1;
            return;
        } const int mid = ( l[pos] + r[pos] ) >> 1;
        if( x <= mid ) insert(lson[pos]=NewNode(),lson[pre],x);
        else insert(rson[pos]=NewNode(),rson[pre],x);
        sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline int cl(int a1,int a2,int b1,int b2) {
        return sum[lson[a1]] + sum[lson[a2]] - sum[lson[b1]] - sum[lson[b2]];
    }
    inline int query(int a1,int a2,int b1,int b2,int k) {
        if( l[a1] == r[a1] ) return l[a1];
        int sl = cl(a1,a2,b1,b2);
        if( k <= sl ) return query(lson[a1],lson[a2],lson[b1],lson[b2],k);
        return query(rson[a1],rson[a2],rson[b1],rson[b2],k-sl);
    }
}tr;
struct UnionFindSet {
    int fa[maxn],siz[maxn];
    inline int findfa(int x) {
        if( fa[x] == x ) return x;
        siz[fa[x]] += siz[x] , siz[x] = 0;
        return fa[x] = findfa(fa[x]);
    }
    inline int getsiz(int x) {
        return siz[findfa(x)];
    }
    inline void merge(int x,int y) {
        x = findfa(x) , y = findfa(y);
        siz[x] += siz[y] , siz[y] = 0;
        fa[y] = x;
    }
    inline void init(int n) {
        for(int i=1;i<=n;i++) fa[i] = i , siz[i] = 1;
    }
}ufs;

int in[maxn],srt[maxn],slen;
int s[maxn],t[maxn<<2],nxt[maxn<<2],cnt;
int fa[maxn][maxl],root[maxn],dep[maxn];
int n;

inline void addedge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void recycle(int pos) {
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos][0] )
            recycle(t[at]);
    memset(fa[pos],0,sizeof(fa[pos]));
}
inline void build(int pos) {
    root[pos] = tr.NewNode();
    tr.insert(root[pos],root[fa[pos][0]],in[pos]);
    for(int i=1;i<maxl;i++) fa[pos][i] = fa[fa[pos][i-1]][i-1];
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos][0] ) {
            fa[t[at]][0] = pos , dep[t[at]] = dep[pos] + 1;
            build(t[at]);
        }
}
inline int lca(int x,int y) {
    if( dep[x] < dep[y] ) swap(x,y);
    for(int i=maxl-1;~i;i--)
        if( dep[x] - dep[y] >= ( 1 << i ) )
            x = fa[x][i];
    if( x == y ) return x;
    for(int i=maxl-1;~i;i--)
        if( fa[x][i] != fa[y][i] )
            x = fa[x][i] , y = fa[y][i];
    return fa[x][0];
}
inline int getroot(int x) {
    for(int i=maxl-1;~i;i--)
        if( fa[x][i] )
            x = fa[x][i];
    return x;
}
inline int kth(int x,int y,int k) {
    int l = lca(x,y) , f = fa[l][0];
    return tr.query(root[x],root[y],root[l],root[f],k);
}
inline void merge(int x,int y) {
    int sx = ufs.getsiz(x) , sy = ufs.getsiz(y);
    if( sx < sy ) swap(x,y);
    recycle(getroot(y));
    ufs.merge(x,y);
    addedge(x,y) , addedge(y,x);
    fa[y][0] = x , dep[y] = dep[x] + 1;
    build(y);
}

inline void init() {
    memcpy(srt+1,in+1,sizeof(int)*n);
    sort(srt+1,srt+1+n) , slen = unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++) in[i] = lower_bound(srt+1,srt+1+slen,in[i]) - srt;
    root[0] = tr.NewNode();
    tr.build(root[0],1,slen);
    ufs.init(n);
    for(int i=1;i<=n;i++)
        if( !root[i] ) build(i);
    for(int i=1;i<=n;i++)
        if( fa[i][0] ) ufs.merge(fa[i][0],i);
}

int main() {
    static int m,os,la;
    static char o[10];
    scanf("%*d%d%d%d",&n,&m,&os) , la = 0;
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d",&a,&b);
        addedge(a,b) , addedge(b,a);
    }
    init();
    for(int i=1,x,y,k;i<=os;i++) {
        scanf("%s%d%d",o,&x,&y) , x ^= la , y ^= la;
        if( *o == 'Q' ) {
            scanf("%d",&k) , k ^= la;
            la = kth(x,y,k);
            la = srt[la];
            printf("%d\n",la);
        } else {
            merge(x,y);
        }
    }
    return 0;
}
