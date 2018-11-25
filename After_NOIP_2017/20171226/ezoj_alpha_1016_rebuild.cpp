#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e5+1e2;
//New operation learnt from RYC.

struct SegmentTree {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3];
    lli mxv[maxn<<3],miv[maxn<<3],sum[maxn<<3],lazy[maxn<<3];
    int cnt;
    
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr )
            return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid);
        build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void set(int pos,lli x) {
        mxv[pos] = miv[pos] = lazy[pos] = x;
        sum[pos] = x * ( r[pos] - l[pos] + 1 );
    }
    inline void push(int pos) {
        if( lazy[pos] ) {
            if( lson[pos] )
                set(lson[pos],lazy[pos]);
            if( rson[pos] )
                set(rson[pos],lazy[pos]);
            lazy[pos] = 0;
        }
    }
    inline void up(int pos) {
        sum[pos] = sum[lson[pos]] + sum[rson[pos]];
        mxv[pos] = max( mxv[lson[pos]] , mxv[rson[pos]] );
        miv[pos] = min( miv[lson[pos]] , miv[rson[pos]] );
    }
    inline void update(int pos,int ll,int rr,lli x) {
        //debug<<"pos = "<<pos<<endl;
        if( rr < l[pos] || r[pos] < ll || x <= miv[pos] )
            return;
        if( ll <= l[pos] && r[pos] <= rr && x >= mxv[pos] ) {
            set(pos,x);
            return;
        }
        push(pos);
        update(lson[pos],ll,rr,x);
        update(rson[pos],ll,rr,x);
        up(pos);
    }
    inline lli full() {
        return sum[1];
    }
    inline lli query(int pos,int ll,int rr) {
    	if( rr < l[pos] || r[pos] < ll )
    		return 0;
    	if( ll <= l[pos] && r[pos] <= rr )
    		return sum[pos];
    	push(pos);
    	return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
    }
}st;

struct Node {
    int zz,xx,yy;
    friend bool operator < (const Node &a,const Node &b) {
        return a.zz < b.zz;
    }
}ns[maxn];

lli zz,xx,yy,ans;
int n;

inline void init() {
    sort(ns+1,ns+1+n);
    st.build(st.cnt=1,1,xx);
}

inline void getans() {
    for(int i=1;i<=n;i++)
        st.update(1,1,ns[i].xx,ns[i].yy);
    /*for(int i=1;i<=xx;i++)
        	debug<<st.query(1,i,i)<<" ";debug<<endl;*/
    for(int i=zz,j=n;i;i--) {
        while( ns[j].zz == i ) {
            st.update(1,1,xx,ns[j].yy);
            st.update(1,1,ns[j].xx,yy);
            j--;
        }
        ans += xx * yy - st.query(1,1,xx);
        /*debug<<"i = "<<i<<"+="<<( xx * yy - st.full())<<endl;
        for(int i=1;i<=xx;i++)
        	debug<<st.query(1,i,i)<<" ";debug<<endl;*/
    }
}

int main() {
    scanf("%d%lld%lld%lld",&n,&zz,&xx,&yy);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&ns[i].zz,&ns[i].xx,&ns[i].yy);
    
    init();
    getans();
    
    printf("%lld\n",ans);
    
    return 0;
}
