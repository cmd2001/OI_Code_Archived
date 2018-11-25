#include<cstdio>
#include<cctype>
const int maxn=7e5+1e2;

struct SegmentTree {
    int dat[maxn<<3];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void build(int pos,int l,int r) {
        dat[pos] = r - l + 1;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r);
    }
    inline void update(int pos,int l,int r,const int &tar) {
        --dat[pos];
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) update(lson(pos),l,mid,tar);
        else update(rson(pos),mid+1,r,tar);
    }
    inline int bin(int pos,int l,int r,int k) {
        if( l == r ) return l;
        const int mid = ( l + r ) >> 1;
        if( k <= dat[lson(pos)] ) return bin(lson(pos),l,mid,k);
        else return bin(rson(pos),mid+1,r,k-dat[lson(pos)]);
    }
}segt;

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int n,m,siz,cur,r,ans;
    m = siz = n = getint() , segt.build(1,0,--n);
    while(m--) {
        cur = ( cur + getint() ) % siz , --siz;
        ans = segt.bin(1,0,n,cur+1) , segt.update(1,0,n,ans);
        printf("%d\n",ans+1);
    }
    return 0;
}

