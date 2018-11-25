#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=2e5+1e2;

struct SegmentTree {
    int lson[maxn<<3],rson[maxn<<3],l[maxn<<3],r[maxn<<3],fil[maxn<<3],sum[maxn<<3],cnt;
    struct Node {
        int sl,mx,sr,len;
        inline void fil(int t) {
            t ?  sl = mx = sr = len : sl = mx = sr = 0;
        }
        friend Node operator + (const Node &l,const Node &r) {
            Node ret = (Node){l.sl,std::max(l.mx,r.mx),r.sr,l.len+r.len};
            ret.mx = std::max( ret.mx , l.sr + r.sl );
            if( l.len == l.sr ) ret.sl = l.len + r.sl;
            if( r.sl == r.len ) ret.sr = l.sr + r.len;
            return ret;
        }
    }ns[maxn<<3];
    SegmentTree() { memset(fil,-1,sizeof(fil)) , cnt = 1; }
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return void(ns[pos] = (Node){0,0,0,1});
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr) , ns[pos] = ns[lson[pos]] + ns[rson[pos]];
    }
    inline void apply(int pos,const int &t) {
        if( !pos ) return;
        ns[pos].fil(fil[pos]=t) , sum[pos] = t * ( r[pos] - l[pos] + 1 );
    }
    inline void push(int pos) {
        if( ~fil[pos] ) apply(lson[pos],fil[pos]) , apply(rson[pos],fil[pos]) , fil[pos] = -1;
    }
    inline void update(int pos,const int &ll,const int &rr,const int &t) {
        if( rr < l[pos] || r[pos] < ll ) return;
        if( ll <= l[pos] && r[pos] <= rr ) return apply(pos,t);
        push(pos) , update(lson[pos],ll,rr,t) , update(rson[pos],ll,rr,t) ,
        ns[pos] = ns[lson[pos]] + ns[rson[pos]] , sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline int querysum(int pos,const int &ll,const int &rr) {
        if( rr < l[pos] || r[pos] < ll ) return 0;
        if( ll <= l[pos] && r[pos] <= rr ) return sum[pos];
        return push(pos) , querysum(lson[pos],ll,rr) + querysum(rson[pos],ll,rr);
    }
    inline Node queryseg(int pos,const int &ll,const int &rr) {
        if( ll <= l[pos] && r[pos] <= rr ) return ns[pos];
        push(pos); const int mid = ( l[pos] + r[pos] ) >> 1;
        if( rr <= mid ) return queryseg(lson[pos],ll,rr);
        else if( ll > mid ) return queryseg(rson[pos],ll,rr);
        else return queryseg(lson[pos],ll,rr) + queryseg(rson[pos],ll,rr);
    }
    inline int kth(int pos,int k) {
        if( !k ) return 0;
        if( l[pos] == r[pos] ) return l[pos];
        push(pos);
        if( k <= sum[lson[pos]] ) return kth(lson[pos],k);
        else return kth(rson[pos],k-sum[lson[pos]]);
    }
}sgt;

inline void printall(int n) {
    for(int i=1;i<=n;i++) printf("%d%c",sgt.querysum(1,i,i),i!=n?' ':'\n');
}
inline bool crs(int x,int y,int xx,int yy) {
    return xx <= y && x <= yy;
}
int main() {
    static int n,m;
    scanf("%d%d",&n,&m) , sgt.build(1,1,n);
    for(int i=1,o,a,b,l,r,rem,lft,tar,ned;i<=m;i++) {
        scanf("%d%d%d",&o,&l,&r);
        if( o == 0 ) sgt.update(1,l,r,1);
        else if( o == 1 ) {
            scanf("%d%d",&a,&b);
            rem = r - l + 1 - sgt.querysum(1,l,r); sgt.update(1,l,r,1);
            ned = sgt.querysum(1,a,b);
            if( !rem ) continue;
            if( rem >= ned ) sgt.update(1,a,b,0);
            else lft = sgt.querysum(1,1,a-1) , tar = sgt.kth(1,lft+rem) , sgt.update(1,a,tar,0);
        } else if( o == 2 ) {
            int ans = sgt.queryseg(1,l,r).mx;
            printf("%d\n",ans);
        }
    }
    return 0;
}

