#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2,lim=1e5;
const int inf=0x3f3f3f3f , minf = -inf;
const lli lli_inf = 0x3f3f3f3f3f3f3f3fll;

int in[maxn],n,k;

namespace Force {
    const int maxn=2e3+1e2;
    int f[maxn][maxn];
    multiset<int> ms;
    inline void work() {
        lli ans = -lli_inf;
        for(int i=1;i<=n;i++) {
            ms.clear() , ms.insert(in[i]) , f[i][i] = inf;
            for(int j=i+1;j<=n;j++) {
                f[i][j] = f[i][j-1];
                if( ms.find(in[j]) != ms.end() ) { f[i][j] = 0; continue; }
                multiset<int>::iterator it = ms.lower_bound(in[j]);
                if( it != ms.end() ) f[i][j] = min( f[i][j] , *it - in[j] );
                if( it != ms.begin() ) f[i][j] = min( f[i][j] , in[j] - *--it );
                if( j - i + 1 >= k ) ans = max( ans , (lli) f[i][j] * ( j - i ) );
                ms.insert(in[j]);
            }
        }
        printf("%lld\n",ans);
    }
}
namespace Sol {
    int Log[maxn],mxl;

    struct RMQ_Min {
        int dat[maxn][20];
        int& operator [] (const int &x) { return *dat[x]; }
        inline void rebuild() {
            for(int j=1;j<=mxl;j++) for(int i=1;i<=n;i++) dat[i][j] = min( dat[i][j-1] , dat[i+(1<<(j-1))][j-1] );
        }
        inline int query(int l,int r) {
            int L = Log[r-l+1];
            return min( dat[l][L] , dat[r-(1<<L)+1][L] );
        }
    }rmqmi;

    struct RMQ_Max {
        int dat[maxn][20];
        int& operator [] (const int &x) { return *dat[x]; }
        inline void rebuild() {
            for(int j=1;j<=mxl;j++) for(int i=1;i<=n;i++) dat[i][j] = max( dat[i][j-1] , dat[i+(1<<(j-1))][j-1] );
        }
        inline int query(int l,int r) {
            int L = Log[r-l+1];
            return max( dat[l][L] , dat[r-(1<<L)+1][L] );
        }
    }rmqmx;

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

    int liml[maxn],limr[maxn];

    inline bool judge(int l,int r) {
        int ll = rmqmx.query(l,r) , rr = rmqmi.query(l,r);
        return ll <= l && r <= rr;
    }
    inline int binrit(int curl,int l,int r) {
        if( judge(curl,r) ) return r;
        int mid;
        while( r > l + 1 ) {
            mid = ( l + r ) >> 1;
            if( judge(curl,mid) ) l = mid;
            else r = mid;
        }
        return l;
    }
    inline int triseg(int pos) { // if same move l .
        int l = liml[pos] , r = pos , lmid , rmid , tpl;
        int cl , cr , ret = -inf;
        while( r > l + 2 ) {
            lmid = ( l + l + r ) / 3 , rmid = ( l + r + r ) / 3;

            tpl = rmqmi.query(lmid,pos);
            if( tpl < pos ) cl = -inf;
            else cl = binrit(lmid,pos,limr[pos]) - lmid;

            tpl = rmqmi.query(rmid,pos);
            if( tpl < pos ) cr = -inf;
            else cr = binrit(rmid,pos,limr[pos]) - rmid;

            if( cl <= cr ) l = lmid;
            else r = rmid;
        }
        for(int i=l;i<=r;i++) {
            tpl = rmqmi.query(i,pos);
            if( tpl < pos ) continue;
            ret = max( ret , binrit(i,pos,limr[pos]) - i );
        }
        return ret;
    }
    inline int getmxseg(int lim) {
        int ret = -inf;
        sgtmi.reset() , sgtmi.build(1,1,1e5);
        for(int i=n;i;i--) limr[i] = rmqmi[i] = min(sgtmi.query(1,in[i]-lim+1,in[i]+lim-1)-1,n) , sgtmi.update(1,in[i],i);
        sgtmx.reset() , sgtmx.build(1,1,1e5);
        for(int i=1;i<=n;i++) liml[i] = rmqmx[i] = max(sgtmx.query(1,in[i]-lim+1,in[i]+lim-1)+1,1) , sgtmx.update(1,in[i],i);
        rmqmi.rebuild() , rmqmx.rebuild();
        for(int i=1;i<=n;i++) {
            ret = max( ret , triseg(i) );
        }
        return ret >= k ? ret : -inf;
    }
    inline lli tri1() { // WAWAWA
        int l = 1 , r = lim , lmid , rmid;
        lli cl , cr , ret = -lli_inf;
        while( r > l + 2 ) {
            lmid = ( l + l + r ) / 3 , rmid = ( l + r + r ) / 3;
            cl = (lli) lmid * getmxseg(lmid) , cr = (lli) rmid * getmxseg(rmid);
            if( cl <= cr ) l = lmid;
            else r = rmid;
        }
        for(int i=l;i<=r;i++) ret = max( ret , (lli) i * getmxseg(i) );
        return ret;
    }
    inline lli tri2() { // WAWAWA
        int l = 1 , r = lim , lmid , rmid;
        lli cl , cr , ret = -lli_inf;
        while( r > l + 2 ) {
            lmid = ( l + l + r ) / 3 , rmid = ( l + r + r ) / 3;
            cl = (lli) lmid * getmxseg(lmid) , cr = (lli) rmid * getmxseg(rmid);
            if( cl < cr ) l = lmid;
            else r = rmid;
        }
        for(int i=l;i<=r;i++) ret = max( ret , (lli) i * getmxseg(i) );
        return ret;
    }

    inline void getlog() {
        for(int i=2;i<=n;i++) Log[i] = Log[i>>1] + 1;
        mxl = Log[n];
    }

    inline void work() {
        --k , getlog() , printf("%lld\n",max(tri1(),tri2()));
    }
}

int main() {
    freopen("gap.in","r",stdin);
    freopen("gap.out","w",stdout);
    static int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        if( n <= 3e3 ) Force::work();
        else Sol::work();
    }
    return fclose(stdout);
}
