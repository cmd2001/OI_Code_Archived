#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
typedef long long int lli;
const int maxn=2e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

struct Matrix {
    lli dat[2][2];
    Matrix() { memset(dat,0x3f,sizeof(dat)); }
    lli* operator [] (const int &x) { return dat[x]; }
    const lli* operator [] (const int &x) const { return dat[x]; }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++) ret[i][j] = std::min( ret[i][j] , a[i][k] + b[k][j] );
        return ret;
    }
}trans[maxn],ini;

lli v[maxn],f[maxn],h[maxn];
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],siz[maxn],dep[maxn],son[maxn],top[maxn],id[maxn],rec[maxn],mxd[maxn],iid;
int n;

struct SegmentTree {
    Matrix dat[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void build(int pos,int l,int r) { // Warning :: from right to left .
        if( l == r ) return void(dat[pos]=trans[rec[l]]);
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r) , dat[pos] = dat[rson(pos)] * dat[lson(pos)];
    }
    inline void update(int pos,int l,int r,const int &tar) {
        if( l == r ) return void(dat[pos]=trans[rec[l]]);
        const int mid = ( l + r ) >> 1;
        tar <= mid ? update(lson(pos),l,mid,tar) : update(rson(pos),mid+1,r,tar);
        dat[pos] = dat[rson(pos)] * dat[lson(pos)];
    }
    inline Matrix query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return dat[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        else return query(rson(pos),mid+1,r,ll,rr) * query(lson(pos),l,mid,ll,rr);
    }
}sgt;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from]  , s[from] = cnt;
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos , pre(t[at]) , siz[pos] += siz[t[at]];
        if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
    }
}
inline void dfs(int pos) {
    ++iid , mxd[top[rec[id[pos]=iid]=pos]=pos==son[fa[pos]]?top[fa[pos]]:pos] = iid , h[pos] = f[pos] = inf;
    if( son[pos] ) dfs(son[pos]) , f[pos] = f[son[pos]] , h[pos] = 0; // pos isn't a leaf node .
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] && t[at] != son[pos] ) dfs(t[at]) , h[pos] += f[t[at]];
    f[pos] = std::min( f[pos] + h[pos] , v[pos] );
}

inline lli query(int pos) {
    Matrix ret = sgt.query(1,1,n,id[pos],mxd[top[pos]]);
    ret = ini * ret;
    return ret[0][1];
}

inline void update(int pos) {
    while(pos) {
        trans[pos][0][1] = v[pos] , trans[pos][1][1] = h[pos] ,
        sgt.update(1,1,n,id[pos]) , pos = top[pos];
        if( pos == 1 ) break; // root don't have fa .
        Matrix fs = ini * sgt.query(1,1,n,id[pos],mxd[pos]);
        h[fa[pos]] -= f[pos] , h[fa[pos]] += ( f[pos] = fs[0][1] );
        pos = fa[pos];
    }
}

inline char nxtchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st=buf+BS,*ed=st;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline char realchar() {
    char ret;
    while( !isalpha(ret=nxtchar()) );
    return ret;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nxtchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nxtchar()) );
    return ret;
}
inline int getlli() {
    lli ret = 0 , ch;
    while( !isdigit(ch=nxtchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nxtchar()) );
    return ret;
}

int main() {
    static int m;
    n = getint() , ini[0][0] = ini[0][1] = 0;
    for(int i=1;i<=n;i++) v[i] = getlli();
    for(int i=1,a,b;i<n;i++) a = getint() , b = getint() , addedge(a,b) , addedge(b,a);
    pre(1) , dfs(1);
    for(int i=1;i<=n;i++) trans[i][0][0] = 0 , trans[i][0][1] = v[i] , trans[i][1][0] = inf , trans[i][1][1] = h[i];
    sgt.build(1,1,n);
    m = getint();
    for(int i=1,o,p;i<=m;i++) {
        o = realchar() , p = getint();
        if( o == 'Q' ) printf("%lld\n",query(p));
        else if( o == 'C' ) v[p] += getlli() , update(p);
    }
    return 0;
}

