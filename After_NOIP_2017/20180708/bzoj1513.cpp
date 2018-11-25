#include<cstdio>
#include<algorithm>
using namespace std;
const int maxe=3e3+1e2;

int D,S;

struct SquaredSegmentTree {
    struct SegmentTree {
        int mx[maxe],lazy[maxe];
        #define lson(pos) (pos<<1)
        #define rson(pos) (pos<<1|1)
        inline void update(int pos,int l,int r,const int &ll,const int &rr,const int &x) {
            mx[pos] = max( mx[pos] , x );
            if( ll <= l && r <= rr ) return void( lazy[pos] = max( lazy[pos] , x ) );
            const int mid = ( l + r ) >> 1;
            if( ll <= mid ) update(lson(pos),l,mid,ll,rr,x);
            if( mid < rr ) update(rson(pos),mid+1,r,ll,rr,x);
        }
        inline int query(int pos,int l,int r,const int &ll,const int &rr) {
            if( ll <= l && r <= rr ) return mx[pos];
            int ret = lazy[pos]; const int mid = ( l + r ) >> 1;
            if( ll <= mid ) ret = max( ret , query(lson(pos),l,mid,ll,rr) );
            if( mid < rr ) ret = max( ret , query(rson(pos),mid+1,r,ll,rr) );
            return ret;
        }
    }mx[maxe],lazy[maxe];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void update(int pos,int l,int r,const int &ll,const int &rr,const int &lll,const int &rrr,const int &x) {
        mx[pos].update(1,1,S,lll,rrr,x);
        if( ll <= l && r <= rr ) return lazy[pos].update(1,1,S,lll,rrr,x);
        const int mid = ( l + r ) >> 1;
        if( ll <= mid ) update(lson(pos),l,mid,ll,rr,lll,rrr,x);
        if( mid < rr ) update(rson(pos),mid+1,r,ll,rr,lll,rrr,x);
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr,const int &lll,const int &rrr) {
        if( ll <= l && r <= rr ) return mx[pos].query(1,1,S,lll,rrr);
        int ret = lazy[pos].query(1,1,S,lll,rrr); const int mid = ( l + r ) >> 1;
        if( ll <= mid ) ret = max( ret , query(lson(pos),l,mid,ll,rr,lll,rrr) );
        if( mid < rr ) ret = max( ret , query(rson(pos),mid+1,r,ll,rr,lll,rrr) );
        return ret;
    }
}sgt;

int main() {
    static int n,d,s,w,sx,sy,tx,ty,mx;
    scanf("%d%d%d",&D,&S,&n) , ++D , ++S;
    while(n--) {
        scanf("%d%d%d%d%d",&d,&s,&w,&sx,&sy) , tx = (++sx) + d - 1 , ty = (++sy) + s - 1;
        mx = sgt.query(1,1,D,sx,tx,sy,ty) + w , sgt.update(1,1,D,sx,tx,sy,ty,mx);
    }
    printf("%d\n",sgt.query(1,1,D,1,D,1,S));
    return 0;
}

