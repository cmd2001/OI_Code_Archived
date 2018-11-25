#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using std::max;
const int maxn=1e5+1e2;
const int minf=0xefefefef;

int in[maxn];
struct SegmentTree {
    int cov[maxn<<2],add[maxn<<2],mx[maxn<<2],_cov[maxn<<2],_add[maxn<<2],_mx[maxn<<2];
    SegmentTree() { memset(cov,0xef,sizeof(cov)) , memset(_cov,0xef,sizeof(_cov)); }
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void build(int pos,int l,int r) {
        if( l == r ) return void( _mx[pos] = mx[pos] = in[l] );
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r) ,
        mx[pos] = max( mx[lson(pos)] , mx[rson(pos)] ) , _mx[pos] = max( _mx[lson(pos)] , _mx[rson(pos)] );
    }
    __inline void apply__add(int pos,int x) {
        _mx[pos] = max( _mx[pos] , mx[pos] + x );
        if( _cov[pos] != minf ) _cov[pos] = max( _cov[pos] , cov[pos] + x );
        else _add[pos] = max( _add[pos] , add[pos] + x );
    }
    __inline void apply__cov(int pos,int x) {
        _mx[pos] = max( _mx[pos] , x ) , _cov[pos] = max( _cov[pos] , x );
    }
    __inline void apply_add(int pos,int x) {
        mx[pos] += x , _mx[pos] = max( _mx[pos] , mx[pos] );
        if( cov[pos] != minf ) cov[pos] += x , _cov[pos] = max( _cov[pos] , cov[pos] );
        else add[pos] += x , _add[pos] = max( _add[pos] , add[pos] );
    }
    __inline void apply_cov(int pos,int x) {
        mx[pos] = cov[pos] = x , _mx[pos] = max( _mx[pos] , mx[pos] ) , _cov[pos] = max( _cov[pos] , cov[pos] );
    }
    __inline void push(int pos) {
        if( _add[pos] ) apply__add(lson(pos),_add[pos]) , apply__add(rson(pos),_add[pos]) , _add[pos] = 0;
        if( _cov[pos] != minf ) apply__cov(lson(pos),_cov[pos]) , apply__cov(rson(pos),_cov[pos]) , _cov[pos] = minf;
        if( add[pos] ) apply_add(lson(pos),add[pos]) , apply_add(rson(pos),add[pos]) , add[pos] = 0;
        if( cov[pos] != minf ) apply_cov(lson(pos),cov[pos]) , apply_cov(rson(pos),cov[pos]) , cov[pos] = minf;
    }
    inline void update_add(int pos,int l,int r,const int &ll,const int &rr,const int &x) {
        if( ll <= l && r <= rr ) return apply_add(pos,x);
        push(pos); const int mid = ( l + r ) >> 1;
        if( rr <= mid ) update_add(lson(pos),l,mid,ll,rr,x);
        else if( ll > mid ) update_add(rson(pos),mid+1,r,ll,rr,x);
        else update_add(lson(pos),l,mid,ll,rr,x) , update_add(rson(pos),mid+1,r,ll,rr,x);
        mx[pos] = max( mx[lson(pos)] , mx[rson(pos)] ) , _mx[pos] = max( _mx[lson(pos)] , _mx[rson(pos)] );
    }
    inline void update_cov(int pos,int l,int r,const int &ll,const int &rr,const int &x) {
        if( ll <= l && r <= rr ) return apply_cov(pos,x);
        push(pos); const int mid = ( l + r ) >> 1;
        if( rr <= mid ) update_cov(lson(pos),l,mid,ll,rr,x);
        else if( ll > mid ) update_cov(rson(pos),mid+1,r,ll,rr,x);
        else update_cov(lson(pos),l,mid,ll,rr,x) , update_cov(rson(pos),mid+1,r,ll,rr,x);
        mx[pos] = max( mx[lson(pos)] , mx[rson(pos)] ) , _mx[pos] = max( _mx[lson(pos)] , _mx[rson(pos)] );
    }
    inline int query_mx(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return mx[pos];
        push(pos); const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query_mx(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query_mx(rson(pos),mid+1,r,ll,rr);
        else return max( query_mx(lson(pos),l,mid,ll,rr) , query_mx(rson(pos),mid+1,r,ll,rr) );
    }
    inline int query__mx(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return _mx[pos];
        push(pos); const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query__mx(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query__mx(rson(pos),mid+1,r,ll,rr);
        else return max( query__mx(lson(pos),l,mid,ll,rr) , query__mx(rson(pos),mid+1,r,ll,rr) );
    }
}sgt;

__inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st=buf+BS,*ed=st;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
__inline int getint() {
    int ret = 0 , fix = 1 , ch;
    while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret * fix;
}
__inline char realchar() {
    char ret;
    while( !isalpha(ret=nextchar()) );
    return ret;
}

int main() {
    static int n,m;
    n = getint();
    for(register int i=1;i<=n;++i) in[i] = getint();
    sgt.build(1,1,n) , m = getint();
    for(register int i=1,o,l,r;i<=m;++i) {
        o = realchar() , l = getint() , r = getint();
        if( o == 'Q' ) printf("%d\n",sgt.query_mx(1,1,n,l,r));
        else if( o == 'A' ) printf("%d\n",sgt.query__mx(1,1,n,l,r));
        else if( o == 'P' ) sgt.update_add(1,1,n,l,r,getint());
        else if( o == 'C' ) sgt.update_cov(1,1,n,l,r,getint());
    }
    return 0;
}
