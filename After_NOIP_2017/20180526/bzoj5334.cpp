#include<cstdio>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

int mod;
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
struct SegmentTree {
    int pi[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void build(int pos,int l,int r) {
        pi[pos] = 1;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r);
    }
    inline void update(int pos,int l,int r,const int &tar,const int &x) {
        if( l == r ) return void( pi[pos] = x );
        const int mid = ( l + r ) >> 1;
        tar <= mid ? update(lson(pos),l,mid,tar,x) : update(rson(pos),mid+1,r,tar,x);
        pi[pos] = mul(pi[lson(pos)],pi[rson(pos)]);
    }
    inline int query() {
        return pi[1];
    }
}sgt;

int main() {
    static int T,n;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&mod) , sgt.build(1,1,n);
        for(int i=1,o,x;i<=n;i++) {
            scanf("%d%d",&o,&x);
            if( o == 1 ) sgt.update(1,1,n,i,x);
            else sgt.update(1,1,n,x,1);
            printf("%d\n",sgt.query());
        }
    }
    return 0;
}
