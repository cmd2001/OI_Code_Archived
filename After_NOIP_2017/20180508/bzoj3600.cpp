#include<cstdio>
#include<algorithm>
#include<cctype>
const int maxn=1e5+1e2,maxe=6e5+1e2;

int bel[maxn];
double v[maxe];

struct Node {
    int l,r; // it storages id of nodes on the balanced tree .
    friend bool operator < (const Node &a,const Node &b) {
        return a.l != b.l ? v[a.l] < v[b.l] : v[a.r] < v[b.r];
    }
    friend bool operator == (const Node &a,const Node &b) {
        return a.l == b.l && a.r == b.r;
    }
};

struct ScapegoatTree {
    double alpha;
    int lson[maxe],rson[maxe],siz[maxe],root,cnt,fail,failfa;
    int seq[maxe],sql;
    double vfl,vfr;
    Node nv[maxe];
    ScapegoatTree() { alpha = 0.75; }
    inline void upgrade(int pos,double ll,double rr) {
        siz[pos] = siz[lson[pos]] + siz[rson[pos]] + 1;
        if( std::max(siz[lson[pos]],siz[rson[pos]]) > siz[pos] * alpha ) fail = pos , failfa = -1 , vfl = ll , vfr = rr;
        else if( fail == lson[pos] || fail == rson[pos] ) failfa = pos;
    }
    inline void insert(int &pos,double ll,double rr,const Node &p,const int &id) {
        if( !pos ) {
            bel[id] = pos = ++cnt , siz[pos] = 1 , v[pos] = ( ll + rr ) / 2.0 , nv[pos] = p;
            return;
        } else if( nv[pos] == p ) return void(bel[id]=pos);
        const double mid = ( ll + rr ) / 2.0;
        if( p < nv[pos] ) insert(lson[pos],ll,mid,p,id) , upgrade(pos,ll,rr);
        else insert(rson[pos],mid,rr,p,id) , upgrade(pos,ll,rr);
    }
    inline int rebuild(int l,int r,double ll,double rr) {
        const int mid = ( l + r ) >> 1 , pos = seq[mid];
        const double vmid = ( ll + rr ) / 2.0; v[pos] = vmid;
        siz[pos] = r - l + 1 , lson[pos] = rson[pos] = 0;
        if( l < mid ) lson[pos] = rebuild(l,mid-1,ll,vmid);
        if( mid < r ) rson[pos] = rebuild(mid+1,r,vmid,rr);
        return pos;
    }
    inline void dfs(int pos) {
        if(lson[pos]) dfs(lson[pos]);
        seq[++sql] = pos;
        if(rson[pos]) dfs(rson[pos]);
    }
    inline void insert(const Node &p,const int &id) {
        vfl = vfr = fail = 0 , failfa = -1;
        insert(root,0,1,p,id);
        if(fail) {
            sql = 0 , dfs(fail);
            if( ~failfa ) {
                if( fail == lson[failfa] ) lson[failfa] = rebuild(1,sql,vfl,vfr);
                else rson[failfa] =  rebuild(1,sql,vfl,vfr);
            } else root = rebuild(1,sql,0,1);
        }
    }
}sct;

struct SegmentTree {
    int mx[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void upgrade(int pos) {
        if( v[bel[mx[lson(pos)]]] < v[bel[mx[rson(pos)]]] ) mx[pos] = mx[rson(pos)];
        else mx[pos] = mx[lson(pos)];
    }
    inline void build(int pos,int l,int r) {
        if( l == r ) return void(mx[pos]=l);
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r) , upgrade(pos);
    }
    inline void update(int pos,int l,int r,const int &tar) {
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) update(lson(pos),l,mid,tar);
        else update(rson(pos),mid+1,r,tar);
        upgrade(pos);
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return mx[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        const int ql = query(lson(pos),l,mid,ll,rr) , qr = query(rson(pos),mid+1,r,ll,rr);
        return v[bel[ql]] < v[bel[qr]] ? qr : ql;
    }
}sgt;

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

int main() {
    static int n,m;
    n = getint() , m = getint();
    *v = -1, sct.insert((Node){0,0},0) , sgt.build(1,1,n);
    for(int i=1;i<=n;i++) bel[i] = 1;
    for(int i=1,o,l,r,x;i<=m;i++) {
        o = realchar() , l = getint() , r = getint();
        if( o == 'C' ) {
            x = getint() , sct.insert((Node){bel[l],bel[r]},x) , sgt.update(1,1,n,x);
        } else if( o == 'Q' ) printf("%d\n",sgt.query(1,1,n,l,r));
    }
    return 0;
}
