#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<tr1/unordered_set>
#define debug cerr
typedef long long int lli;
using namespace std;

int n,m;

namespace SubTask1 {
    const int maxn=5e3+1e2;
    const lli inf=0x3f3f3f3f3f3f3f3fll;
    lli in[maxn];
    tr1::unordered_set<lli> ban;
    
    inline void initban() {
        lli cur = 23;
        for(int i=1;i<=17;i++) cur = cur * 10 + 3 , ban.insert(cur);
    }
    inline void apply_add(int l,int r,const lli &x) {
        for(int i=l;i<=r;i++) in[i] += x;
    }
    inline void apply_fil(int l,int r,const lli &x) {
        for(int i=l;i<=r;i++) in[i] = x;
    }
    inline lli query_sum(int l,int r) {
        lli ret = 0;
        for(int i=l;i<=r;i++) ret += in[i];
        return ret;
    }
    inline lli query_mi(int l,int r) {
        lli ret = inf;
        for(int i=l;i<=r;i++) ret = min( ret , in[i] );
        return ret;
    }
    inline lli query_mx(int l,int r) {
        lli ret = -inf;
        for(int i=l;i<=r;i++) ret = max( ret , in[i] );
        return ret;
    }
    inline bool judge_ban(int l,int r) {
        for(int i=l;i<=r;i++) if( ban.find(in[i]) != ban.end() ) return 1;
        return 0;
    }
    void main() {
        initban();
        for(int i=1;i<=n;i++) scanf("%lld",in+i);
        for(int i=1,o,l,r,x;i<=m;i++) {
            scanf("%d",&o);
            if( o == 1 ) scanf("%d",&x) , printf("%lld\n",query_sum(x,x));
            else {
                scanf("%d%d",&l,&r);
                if( o == 2 || o == 3 ) {
                    scanf("%d",&x);
                    if( o == 2 ) apply_fil(l,r,x);
                    else if( o == 3 ) apply_add(l,r,x);
                } else {
                    lli val;
                    if( o == 4 ) val = query_mi(l,r);
                    else if( o == 5 ) val = query_mx(l,r);
                    else if( o == 6 ) val = query_sum(l,r) / ( r - l + 1 );
                    apply_fil(l,r,val);
                }
                if( o == 2 || o == 3 || o == 6 ) while( judge_ban(l,r) ) apply_add(l,r,1);
            }
        }
    }
}

namespace SubTask2 {
    const int maxn=1e5+1e2;
    int in[maxn];
    struct SegmentTree {
        int l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2],cnt;
        lli lazy_add[maxn<<2],lazy_fil[maxn<<2],sum[maxn<<2],mi[maxn<<2],mx[maxn<<2];
        SegmentTree() { memset(lazy_fil,-1,sizeof(lazy_fil)) , cnt = 1; }
        inline void apply_add(int pos,const lli &x) {
            mi[pos] += x , mx[pos] += x , sum[pos] += x * ( r[pos] - l[pos] + 1 );
            if( ~lazy_fil[pos] ) lazy_fil[pos] += x;
            else lazy_add[pos] += x;
        }
        inline void apply_fil(int pos,const lli &x) {
            mi[pos] = mx[pos] = lazy_fil[pos] = x , sum[pos] = x * ( r[pos] - l[pos] + 1 );
            lazy_add[pos] = 0;
        }
        inline void push(int pos) { // two marks will not appear at the same time .
            if( ~lazy_fil[pos] ) apply_fil(lson[pos],lazy_fil[pos]) , apply_fil(rson[pos],lazy_fil[pos]) , lazy_fil[pos] = -1;
            if( lazy_add[pos] ) apply_add(lson[pos],lazy_add[pos]) , apply_add(rson[pos],lazy_add[pos]) , lazy_add[pos] = 0;
        }
        inline void maintain(int pos) {
            sum[pos] = sum[lson[pos]] + sum[rson[pos]] , mi[pos] = min( mi[lson[pos]] , mi[rson[pos]] ) , mx[pos] = max( mx[lson[pos]] , mx[rson[pos]] );
        }
        inline void build(int pos,int ll,int rr) {
            if( ( l[pos] = ll ) == ( r[pos] =  rr ) ) return void(sum[pos] = mi[pos] = mx[pos] = in[ll]);
            const int mid = ( ll + rr ) >> 1;
            build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr) , maintain(pos);
        }
        inline void update_fil(int pos,const int &ll,const int &rr,const lli &x) {
            if( rr < l[pos] || r[pos] < ll ) return;
            if( ll <= l[pos] && r[pos] <= rr ) return apply_fil(pos,x);
            push(pos) , update_fil(lson[pos],ll,rr,x) , update_fil(rson[pos],ll,rr,x) , maintain(pos);
        }
        inline void update_add(int pos,const int &ll,const int &rr,const lli &x) {
            if( rr < l[pos] || r[pos] < ll ) return;
            if( ll <= l[pos] && r[pos] <= rr ) return apply_add(pos,x);
            push(pos) , update_add(lson[pos],ll,rr,x) , update_add(rson[pos],ll,rr,x) , maintain(pos);
        }
        inline lli query_mi(int pos,const int &ll,const int &rr) {
            if( ll <= l[pos] && r[pos] <= rr ) return mi[pos];
            push(pos); const int mid = ( l[pos] + r[pos] ) >> 1;
            if( rr <= mid ) return query_mi(lson[pos],ll,rr);
            else if( ll > mid ) return query_mi(rson[pos],ll,rr);
            else return min( query_mi(lson[pos],ll,rr) , query_mi(rson[pos],ll,rr) );
        }
        inline lli query_mx(int pos,const int &ll,const int &rr) {
            if( ll <= l[pos] && r[pos] <= rr ) return mx[pos];
            push(pos); const int mid = ( l[pos] + r[pos] ) >> 1;
            if( rr <= mid ) return query_mx(lson[pos],ll,rr);
            else if( ll > mid ) return query_mx(rson[pos],ll,rr);
            else return max( query_mx(lson[pos],ll,rr) , query_mx(rson[pos],ll,rr) );
        }
        inline lli query_sum(int pos,const int &ll,const int &rr) {
            if( ll <= l[pos] && r[pos] <= rr ) return sum[pos];
            push(pos); const int mid = ( l[pos] + r[pos] ) >> 1;
            if( rr <= mid ) return query_sum(lson[pos],ll,rr);
            else if( ll > mid ) return query_sum(rson[pos],ll,rr);
            else return query_sum(lson[pos],ll,rr) + query_sum(rson[pos],ll,rr);
        }
    }sgt;
    void main() {
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        sgt.build(1,1,n);
        for(int i=1,o,l,r,x;i<=m;i++) {
            scanf("%d",&o);
            if( o == 1 ) scanf("%d",&x) , printf("%lld\n",sgt.query_sum(1,x,x));
            else {
                scanf("%d%d",&l,&r);
                if( o == 2 || o == 3 ) {
                    scanf("%d",&x);
                    if( o == 2 ) sgt.update_fil(1,l,r,x);
                    else sgt.update_add(1,l,r,x);
                } else {
                    lli val;
                    if( o == 4 ) val = sgt.query_mi(1,l,r);
                    else if( o == 5 ) val = sgt.query_mx(1,l,r);
                    else if( o == 6 ) val = sgt.query_sum(1,l,r) / ( r - l + 1 );
                    sgt.update_fil(1,l,r,val);
                }
            }
        }
    }
}

int main() {
    freopen("eee.in","r",stdin);
    freopen("eee.out","w",stdout);
    scanf("%d%d",&n,&m);
    if( n <= 4000 && m <= 4000 ) SubTask1::main();
    else SubTask2::main();
    fclose(stdout);
    return 0;
}
