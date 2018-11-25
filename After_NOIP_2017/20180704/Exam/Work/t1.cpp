#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
typedef long long int lli;
using namespace std;
const int maxn=2.5e5+1e2;
const int inf=0x3f3f3f3f;

int cmp;
struct Point {
    int d[2],id;
    friend bool operator < (const Point &a,const Point &b) {
        return a.d[cmp] < b.d[cmp];
    }
}mem[maxn],ps[maxn];

int rec[maxn],root;
lli ans;

struct KDTree {
    int lson[maxn],rson[maxn],fa[maxn],mi[maxn][2],mx[maxn][2],cnt;
    bool act[maxn],hav[maxn];
    Point nv[maxn];
    inline void maintain(int pos) {
        if( act[pos] ) for(int i=0;i<2;i++) mx[pos][i] = mi[pos][i] = nv[pos].d[i];
        else for(int i=0;i<2;i++) mx[pos][i] = -inf , mi[pos][i] = inf;
        if( lson[pos] && hav[lson[pos]] ) for(int i=0;i<2;i++) mi[pos][i] = min( mi[pos][i] , mi[lson[pos]][i] ) , mx[pos][i] = max( mx[pos][i] , mx[lson[pos]][i] );
        if( rson[pos] && hav[rson[pos]] ) for(int i=0;i<2;i++) mi[pos][i] = min( mi[pos][i] , mi[rson[pos]][i] ) , mx[pos][i] = max( mx[pos][i] , mx[rson[pos]][i] );
        hav[pos] = 1;
    }
    inline int build(int &pos,int dir,int ll,int rr) {
        const int mid = ( ll + rr ) >> 1;
        cmp = dir , nth_element(ps+ll,ps+mid,ps+rr+1) , nv[rec[ps[mid].id]=pos=++cnt] = ps[mid];
        if( ll < mid ) fa[build(lson[pos],dir^1,ll,mid-1)] = pos;
        if( mid < rr ) fa[build(rson[pos],dir^1,mid+1,rr)] = pos;
        return pos;
    }
    inline void update_chain(int pos) {
        act[pos] = 1;
        while(pos) maintain(pos) , pos = fa[pos];
    }
    inline lli sq(const int &x) {
        return (lli) x * x;
    }
    inline lli h(int pos,const Point &p) {
        if( !pos || !hav[pos] ) return -1;
        lli ret = 0;
        for(int i=0;i<2;i++) ret += max( sq(p.d[i]-mi[pos][i]) , sq(p.d[i]-mx[pos][i]) );
        return ret;
    }
    inline lli calc(const Point &p,const Point &t) {
        lli ret = 0;
        for(int i=0;i<2;i++) ret += sq( p.d[i] - t.d[i] );
        return ret;
    }
    inline void query(int pos,const Point &p) {
        if( act[pos] ) ans = max( ans , calc( nv[pos] , p ) );
        lli hl = h(lson[pos],p) , hr = h(rson[pos],p);
        if( hl > hr ) {
            if( hl > ans ) query(lson[pos],p);
            if( hr > ans ) query(rson[pos],p);
        } else {
            if( hr > ans ) query(rson[pos],p);
            if( hl > ans ) query(lson[pos],p);
        }
    }
}kdt;

struct Node {
    int id,col;
    friend bool operator < (const Node &a,const Node &b) {
        return a.col < b.col;
    }
}in[maxn];

inline int getint() {
    int ret = 0 , fix = 1; char ch;
    while( !isdigit(ch=getchar()) ) fix = ch == '-' ? -fix : fix;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret * fix;
}

int main() {
    static int n;
    n = getint();
    for(int i=1;i<=n;i++) {
        for(int j=0;j<2;j++) mem[i].d[j] = ps[i].d[j] = getint();
        in[i].col = getint() , ps[i].id = in[i].id = i;
    }
    kdt.build(root,0,1,n) , sort(in+1,in+1+n);
    for(int l=1,r;l<=n;l=r+1) {
        for(r=l;r<n&&in[r+1].col==in[l].col;r++) ;
        for(int i=l;i<=r;i++) kdt.query(root,mem[in[i].id]);
        for(int i=l;i<=r;i++) kdt.update_chain(rec[in[i].id]);
    }
    printf("%lld\n",ans);
    return 0;
}

