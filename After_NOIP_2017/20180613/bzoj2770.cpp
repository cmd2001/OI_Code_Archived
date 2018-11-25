#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;
const int inf=0x7fffffff;

int srt[maxn],len;
int o[maxn],a[maxn],b[maxn];
int n,m;


struct SegmentTree {
    struct Node {
        int p,k;
        friend bool operator < (const Node &a,const Node &b) {
            return a.p < b.p;
        }
    }dat[maxn<<3];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void build(int pos,int l,int r) {
        dat[pos] = (Node){inf,-1};
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r);
    }
    inline void update(int pos,int l,int r,const int &tar,const Node &x) {
        if( l == r ) return void( dat[pos] = x );
        const int mid = ( l + r ) >> 1;
        tar <= mid ? update(lson(pos),l,mid,tar,x) : update(rson(pos),mid+1,r,tar,x);
        dat[pos] = min( dat[lson(pos)] , dat[rson(pos)] );
    }
    inline Node query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return dat[pos];
        const int mid = ( l + r ) >> 1;
        Node ret = (Node){inf,-1};
        if( ll <= mid ) ret = min( ret , query(lson(pos),l,mid,ll,rr) );
        if( mid < rr ) ret = min( ret , query(rson(pos),mid+1,r,ll,rr) );
        return ret;
    }
}sgt;
typedef SegmentTree::Node Node;

inline int gid(int t) {
    return lower_bound(srt+1,srt+1+len,t) - srt;
}

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline void getstr(char* s) {
    char ch;
    while( !isalpha(ch=nextchar()) );
    do *s++ = ch; while( isalpha(ch=nextchar()) );
}
inline int getint() {
    int ret = 0 , fix = 1 , ch;
    while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret * fix;
}

int main() {
    static char oo[10];
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) srt[++len] = a[i] = getint();
    for(int i=1;i<=n;i++) b[i] = getint();
    for(int i=n+1;i<=n+m;i++) {
        getstr(oo) , srt[++len] = a[i] = getint();
        if( *oo == 'Q' ) o[i] = 3 , srt[++len] = b[i] = getint();
        else if( *oo == 'I' ) o[i] = 1 , b[i] = getint();
        else if( *oo == 'D' ) o[i] = 2;
    }
    sort(srt+1,srt+1+len) , len = unique(srt+1,srt+1+len) - srt - 1;
    sgt.build(1,1,len);
    for(int i=1;i<=n;i++) sgt.update(1,1,len,gid(a[i]),(Node){b[i],a[i]});
    for(int i=n+1;i<=n+m;i++) {
        if( o[i] == 1 ) sgt.update(1,1,len,gid(a[i]),(Node){b[i],a[i]});
        else if( o[i] == 2 ) sgt.update(1,1,len,gid(a[i]),(Node){inf,-1});
        else if( o[i] == 3 ) printf("%d\n",sgt.query(1,1,len,gid(min(a[i],b[i])),gid(max(a[i],b[i]))).k);
    }
    return 0;
}
