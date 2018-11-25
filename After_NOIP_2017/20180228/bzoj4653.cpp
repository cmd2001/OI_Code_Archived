#include<cstdio>
#include<algorithm>
#include<cctype>
const int maxn=5e5+1e2,maxl=1e6+1e2;
const int inf=0x3f3f3f3f;

struct SegmentTree {
    int dat[maxl<<2],lazy[maxl<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) ((pos<<1)|1)
    inline void fill(const int &pos,const int &x) {
        dat[pos] += x , lazy[pos] += x;
    }
    inline void push(const int &pos) {
        if( !lazy[pos] ) return;
        fill(lson(pos),lazy[pos]) , fill(rson(pos),lazy[pos]) ,
        lazy[pos] = 0;
    }
    inline void update(int pos,int l,int r,const int &ll,const int &rr,const int &x) {
        if( ll <= l && r <= rr ) return fill(pos,x);
        push(pos);
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) update(lson(pos),l,mid,ll,rr,x);
        else if( ll > mid ) update(rson(pos),mid+1,r,ll,rr,x);
        else update(lson(pos),l,mid,ll,rr,x) , update(rson(pos),mid+1,r,ll,rr,x);
        dat[pos] = std::max( dat[lson(pos)] , dat[rson(pos)] );
    }
    inline int query() {
        return dat[1];
    }
}segt;

struct Segment {
    int l,len;
    friend bool operator < (const Segment &a,const Segment &b) {
        return a.len != b.len ? a.len < b.len : a.l < b.l;
    }
}s[maxn];
int pts[maxl],cnt;

inline int find(const int &x) {
    return std::lower_bound(pts+1,pts+1+cnt,x) - pts;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int n,m,ans=inf;
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) {
        pts[++cnt] = s[i].l = getint() ,
        pts[++cnt] = s[i].len = getint();
    }
    std::sort(pts+1,pts+1+cnt) , cnt = std::unique(pts+1,pts+1+cnt) - pts - 1;
    for(int i=1;i<=n;i++) s[i].len -= s[i].l;
    std::sort(s+1,s+1+n);
    for(int i=1,l=1;i<=n;i++) {
        segt.update(1,1,cnt,find(s[i].l),find(s[i].l+s[i].len),1);
        while( l <= i && segt.query() >= m ) {
            ans = std::min( ans , s[i].len - s[l].len );
            segt.update(1,1,cnt,find(s[l].l),find(s[l].l+s[l].len),-1);
            ++l;
        }
    }
    if( ans != inf ) printf("%d\n",ans);
    else puts("-1");
    return 0;
}

