#include<cstdio>
#include<algorithm>
#include<cctype>
#define lli long long int
using namespace std;
const int maxn=1e6+1e2;

struct SegmenTree {
    lli dat[maxn<<2],lazy[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) ((pos<<1)|1)
    
    inline void fill(int pos,lli x) {
        dat[pos] += x , lazy[pos] += x;
    }
    inline void push(int pos) { // assert l[pos] != r[pos] .
        if( !lazy[pos] ) return;
        fill(lson(pos),lazy[pos]) ,
        fill(rson(pos),lazy[pos]) ,
        lazy[pos] = 0;
    }
    inline void update(int pos,int l,int r,int ll,int rr,lli x) {
        if( ll <= l && r <= rr ) {
            fill(pos,x);
            return;
        } push(pos);
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) update(lson(pos),l,mid,ll,rr,x);
        else if( ll > mid ) update(rson(pos),mid+1,r,ll,rr,x);
        else {
            update(lson(pos),l,mid,ll,rr,x) ,
            update(rson(pos),mid+1,r,ll,rr,x);
        }
        dat[pos] = std::max( dat[lson(pos)] , dat[rson(pos)] );
    }
    inline lli query(int pos,int l,int r,int ll,int rr) {
        if( ll <= l && r <= rr ) return dat[pos];
        push(pos);
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        return max( query(lson(pos),l,mid,ll,rr) , query(rson(pos),mid+1,r,ll,rr) );
    }
}segt;

int in[maxn],w[maxn],lst[maxn],nxt[maxn];
int n,m;
lli ans;

inline void pre() {
    for(int i=1;i<=m;i++) lst[i] = n + 1;
    for(int i=n;i;i--) nxt[i] = lst[in[i]] , lst[in[i]] = i;
}
inline void getans() {
    for(int i=1;i<=m;i++)
        if( lst[i] != n + 1 ) {
            segt.update(1,1,n,lst[i],nxt[lst[i]]-1,w[i]);
        }
    for(int i=1,t;i<=n;i++) {
        ans = max( ans , segt.query(1,1,n,1,n) ) , t = nxt[i];
        if( t ) segt.update(1,1,n,i,t-1,-w[in[i]]);
        if( nxt[t] ) segt.update(1,1,n,t,nxt[t]-1,w[in[i]]);
    }
}

inline char nextchar() {
    const int bs = 1 << 22;
    static char buf[bs],*st=buf+bs,*ed=buf+bs;
    if( st == ed ) ed = buf + fread(st=buf,1,bs,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) in[i] = getint();
    for(int i=1;i<=m;i++) w[i] = getint();
    pre() , getans();
    printf("%lld\n",ans);
    return 0;
}


