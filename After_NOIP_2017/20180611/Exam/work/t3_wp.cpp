#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2,lim=1e5;
const int inf = 0x3f3f3f3f , minf = 0xefefefef;
const lli lli_inf = 0x3f3f3f3f3f3f3f3fll;


int in[maxn],n,k;
lli ans;

namespace DisLessK {
    multiset<int> ms;
    inline void solve() {
        ms.clear();
        for(int i=1;i<=k;i++) ms.insert(in[i]);
        for(int i=1;i<=n;i++) {
            ms.erase(ms.find(in[i]));
            if( ms.find(in[i]) != ms.end() ) ans = 0;
            else {
                multiset<int>::iterator it = ms.lower_bound(in[i]);
                if( it != ms.end() ) ans = std::min( ans , (lli) ( *it - in[i] ) * k );
                if( it != ms.begin() ) ans = std::min( ans , (lli) ( in[i] - *--it) * k );
            }
            if( i + k <= n ) ms.insert(in[i+k]);
        }
    }
    inline void work() {
        reverse(in+1,in+1+n) , solve();
        reverse(in+1,in+1+n) , solve();
    }
}

namespace DisMoreK {
    struct SemgnetTree_Min {
        int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],dat[maxn<<3],cnt;
        inline void build(int pos,int ll,int rr) {
            l[pos] = ll , r[pos] = rr , dat[pos] = inf;
            if( ll == rr ) return;
            const int mid = ( ll + rr ) >> 1;
            build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
        }
        inline void update(int pos,const int &tar,const int &x) {
            if( l[pos] == r[pos] ) return void( dat[pos] = x );
            const int mid = ( l[pos] + r[pos] ) >> 1;
            tar <= mid ? update(lson[pos],tar,x) : update(rson[pos],tar,x) , dat[pos] = min( dat[lson[pos]] , dat[rson[pos]] );
        }
        inline int query(int pos,const int &ll,const int &rr) {
            if( ll <= l[pos] && r[pos] <= rr ) return dat[pos];
            const int mid = ( l[pos] + r[pos] ) >> 1;
            if( rr <= mid ) return query(lson[pos],ll,rr);
            else if( ll > mid ) return query(rson[pos],ll,rr);
            return min( query(lson[pos],ll,rr) , query(rson[pos],ll,rr) );
        }
        inline void reset() { cnt = 1; }
    }sgtmi;
    struct SemgnetTree_Max {
        int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],dat[maxn<<3],cnt;
        inline void build(int pos,int ll,int rr) {
            l[pos] = ll , r[pos] = rr , dat[pos] = minf;
            if( ll == rr ) return;
            const int mid = ( ll + rr ) >> 1;
            build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
        }
        inline void update(int pos,const int &tar,const int &x) {
            if( l[pos] == r[pos] ) return void( dat[pos] = x );
            const int mid = ( l[pos] + r[pos] ) >> 1;
            tar <= mid ? update(lson[pos],tar,x) : update(rson[pos],tar,x) , dat[pos] = max( dat[lson[pos]] , dat[rson[pos]] );
        }
        inline int query(int pos,const int &ll,const int &rr) {
            if( ll <= l[pos] && r[pos] <= rr ) return dat[pos];
            const int mid = ( l[pos] + r[pos] ) >> 1;
            if( rr <= mid ) return query(lson[pos],ll,rr);
            else if( ll > mid ) return query(rson[pos],ll,rr);
            return max( query(lson[pos],ll,rr) , query(rson[pos],ll,rr) );
        }
        inline void reset() { cnt = 1; }
    }sgtmx;

    inline lli calc(int pos,int val,int lim) {
        int dis = min( pos - sgtmx.query(1,val-lim,val+lim) , sgtmi.query(1,val-lim,val+lim) - pos ) + 1;
        return (lli) lim * dis;
    }
    inline lli tri(int pos,int val) {
        int l = 0 , r = lim + 1 , lmid , rmid;
        lli cl , cr , ret = lli_inf;
        while( r > l + 2 ) {
            lmid = ( l + l + r ) / 3 , rmid = ( l + r + r ) / 3;
            cl = calc(pos,val,lmid) , cr = calc(pos,val,rmid);
            if( cl > cr ) l = lmid;
            else r = rmid;
        }
        for(int i=l;i<=r;i++) ret = min( ret , calc(pos,val,i) );
        return ret;
    }
    inline void work() {
        sgtmi.reset() , sgtmx.reset() , sgtmi.build(1,1,lim) , sgtmx.build(1,1,lim);
        for(int i=k+1;i<=n;i++) sgtmi.update(1,in[i],i);
        for(int i=1;i<=n;i++) {
            ans = min( ans , tri(i,in[i]) );
            if( i + k <= n ) sgtmi.update(1,in[i+k],inf);
            if( i - k > 0 ) sgtmx.update(1,in[i-k],i-k);
        }
    }
}

int main() {
    static int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n) , ans = lli_inf;
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        DisLessK::work() , DisMoreK::work() , printf("%lld\n",ans);
    }
    return 0;
}
