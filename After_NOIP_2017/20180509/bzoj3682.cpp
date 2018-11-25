#include<cstdio>
#include<algorithm>
#include<cctype>
const int maxe=1e6+1e2;
const double alpha = 0.85;

char in[maxe];
int at[maxe]; // suffix i's node .
double v[maxe];

struct SuffixBalancedTree { // we should insert 0 as the minimal suffix .
    int lson[maxe],rson[maxe],siz[maxe],sf[maxe],root,cnt;
    int seq[maxe],sql;
    int fail,failfa;
    double vfl,vfr;
    
    inline bool cmp(int x,int y) {
        if( !x || !y ) return !x;
        if( in[x] != in[y] ) return in[x] < in[y];
        else return v[at[x-1]] < v[at[y-1]];
    }
    inline void upgrade(int pos,double l,double r) {
        siz[pos] = siz[lson[pos]] + siz[rson[pos]] + 1;
        if( std::max( siz[lson[pos]] , siz[rson[pos]] ) > siz[pos] * alpha ) fail = pos , failfa = -1 , vfl = l , vfr = r;
        else if( fail == lson[pos] || fail == rson[pos] ) failfa = pos;
    }
    inline void insert(int &pos,double l,double r,const int &id) {
        if( !pos ) {
            v[at[id]=pos=++cnt]= ( l + r ) / 2.0 , siz[pos] = 1 , sf[pos] = id;
            return;
        } const double vmid = ( l + r ) / 2.0;
        if( cmp(sf[pos],id) ) insert(rson[pos],vmid,r,id) , upgrade(pos,l,r); // id > sf[pos] .
        else insert(lson[pos],l,vmid,id) , upgrade(pos,l,r);
    }
    inline int rebuild(int ll,int rr,double l,double r) {
        const int mid = ( ll + rr ) >> 1 , pos = seq[mid];
        const double vmid = ( l + r ) / 2.0; v[pos] = vmid , siz[pos] = rr - ll + 1;
        if( ll < mid ) lson[pos] = rebuild(ll,mid-1,l,vmid);
        if( mid < rr ) rson[pos] = rebuild(mid+1,rr,vmid,r);
        return pos;
    }
    inline void dfs(int pos) {
        if(lson[pos]) dfs(lson[pos]);
        seq[++sql] = pos;
        if(rson[pos]) dfs(rson[pos]);
        lson[pos] = rson[pos] = siz[pos] = 0;
    }
    inline void insert(const int &id) {
        fail = 0 , failfa = -1 , insert(root,0,1,id);
        if(fail) {
            sql = 0 , dfs(fail);
            if( ~failfa ) {
                if( fail == lson[failfa] ) lson[failfa] = rebuild(1,sql,vfl,vfr);
                else rson[failfa] = rebuild(1,sql,vfl,vfr);
            } else root = rebuild(1,sql,0,1);
        }
    }
}sbt;

int cov[maxe>>1];

struct SegmentTree {
    int mx[maxe<<1];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline bool cmp(int a,int b) {
        if( cov[a] == cov[b] ) return a < b;
        return v[at[cov[a]]] < v[at[cov[b]]];
    }
    inline void upgrade(int pos) {
        mx[pos] = cmp(mx[lson(pos)],mx[rson(pos)]) ? mx[lson(pos)] : mx[rson(pos)];
    }
    inline void build(int pos,int l,int r) {
        if( l == r ) return void( mx[pos] = l );
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r) , upgrade(pos);
    }
    inline void update(int pos,int l,int r,const int &tar) {
        if( l == r ) return; // nothing to update .
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
        return cmp(ql,qr) ? ql : qr;
    }
}sgt;

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st=buf+BS,*ed=st;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline void getstr(char* s) {
    char c;
    while( !isalpha(c=nextchar()) );
    do *s++=c; while( isalpha(c=nextchar()) );
}
inline char realchar() {
    char c;
    while( !isalpha(c=nextchar()) );
    return c;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    static int n,m,len,tpe,lastans;
    n = getint() , m = getint() , len = getint() , tpe = getint() , getstr(in+1) , std::reverse(in+1,in+1+len);
    for(int i=0;i<=len;i++) in[i] -= 'a' , sbt.insert(i);
    for(int i=1;i<=n;i++) cov[i] = getint();
    sgt.build(1,1,n);
    for(int i=1,o,c,x,l,r;i<=m;i++) {
        o = realchar();
        if( o == 'I' ) {
            c = getint();
            if( tpe ) c ^= lastans;
            in[++len] = c , sbt.insert(len);
        } else if( o == 'C' ) x = getint() , cov[x] = getint() , sgt.update(1,1,n,x);
        else if( o == 'Q' ) l = getint() , r = getint() , printf("%d\n",lastans=sgt.query(1,1,n,l,r));
    }
    return 0;
}
