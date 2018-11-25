#pragma GCC optimize(3)
#include<cstdio>
#include<cstdlib>
#include<cctype>
#define lson(pos) (pos<<1)
#define rson(pos) (pos<<1|1)
const int maxn=1e5+1e2;

int in[maxn];
unsigned char dat[maxn<<3];

inline void build(int pos,int l,int r) {
    if( l == r ) return void (dat[pos] = ( abs(in[l+1]-in[l]) <= 1 ) );
    const int mid = ( l + r ) >> 1;
    build(lson(pos),l,mid) , build(rson(pos),mid+1,r);
    dat[pos] = dat[lson(pos)] & dat[rson(pos)];
}
inline unsigned char query(int pos,int l,int r,const int &ll,const int &rr) {
    if( ll <= l && r <= rr ) return dat[pos];
    const int mid = ( l + r ) >> 1;
    if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
    else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
    return query(lson(pos),l,mid,ll,rr) & query(rson(pos),mid+1,r,ll,rr);
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    static int n,m;
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) in[i] = getint();
    if( n != 1 ) build(1,1,n-1);
    for(int i=1,a,b;i<=m;i++) {
        a = getint() , b = getint();
        puts(a==b||query(1,1,n-1,a,b-1)?"YES":"NO");
    }
    return 0;
}

