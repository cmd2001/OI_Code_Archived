#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=2e5+1e2;

class SegmentTree {
    private:
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],cnt;
    lli dat[maxn<<3],lazy[maxn<<3];
    public:
    SegmentTree() { cnt = 1; }
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void apply(int pos,lli x) {
        dat[pos] += ( r[pos] - l[pos] + 1 ) * x , lazy[pos] += x;
    }
    inline void push(int pos) {
        apply(lson[pos],lazy[pos]) , apply(rson[pos],lazy[pos]) , lazy[pos] = 0;
    }
    inline void update(int pos,const int &ll,const int &rr,const lli &x) {
        if( rr < l[pos] || r[pos] < ll ) return;
        if( ll <= l[pos] && r[pos] <= rr ) return apply(pos,x);
        push(pos) , update(lson[pos],ll,rr,x) , update(rson[pos],ll,rr,x) , dat[pos] = dat[lson[pos]] + dat[rson[pos]];
    }
    inline lli query(int pos,const int &ll,const int &rr) {
        if( rr < l[pos] || r[pos] < ll ) return 0;
        if( ll <= l[pos] && r[pos] <= rr ) return dat[pos];
        return push(pos) , query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
    }
}pre,sgt;

int in[maxn<<1],n;
lli ans;

int main() {
    scanf("%d",&n) , pre.build(1,1,n) , sgt.build(1,1,n);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , in[i+n] = in[i] , pre.update(1,in[i]+1,n,1) , sgt.update(1,in[i],in[i],pre.query(1,in[i],in[i]));
    for(int i=n,lst=1;i<n<<1;i++,lst++) ans += sgt.query(1,1,in[i]-1) , sgt.update(1,in[lst]+1,n,-1) , sgt.update(1,in[lst],in[lst],in[lst]-1);
    printf("%lld\n",ans);
    return 0;
}
