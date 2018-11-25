#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
const int maxn=5e4+1e2,maxe=1.4e7+1e2;
const int mod=1e9+7;

int in[maxn],seq[maxn],n;

struct SegmentTree {
    int lson[maxe],rson[maxe],sum[maxe],siz[maxe],cnt;
    inline void insert(int &pos,int l,int r,const int &tar,const int &x,const int &d) {
        if( !pos ) pos = ++cnt;
        sum[pos] = ( sum[pos] + x ) % mod , siz[pos] += d;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],l,mid,tar,x,d);
        else insert(rson[pos],mid+1,r,tar,x,d);
    }
    inline int querysum(int pos,int l,int r,const int &ll,const int &rr) {
        if( !pos || ( ll <= l && r <= rr ) ) return sum[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return querysum(lson[pos],l,mid,ll,rr);
        else if( ll > mid ) return querysum(rson[pos],mid+1,r,ll,rr);
        return ( querysum(lson[pos],l,mid,ll,rr) + querysum(rson[pos],mid+1,r,ll,rr) ) % mod;
    }
    inline int querysiz(int pos,int l,int r,const int &ll,const int &rr) {
        if( !pos || ( ll <= l && r <= rr ) ) return siz[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return querysiz(lson[pos],l,mid,ll,rr);
        else if( ll > mid ) return querysiz(rson[pos],mid+1,r,ll,rr);
        return ( querysiz(lson[pos],l,mid,ll,rr) + querysiz(rson[pos],mid+1,r,ll,rr) ) % mod;
    }
}sgt;

struct BinaryIndexTree {
    int root[maxn],id;
    #define lowbit(x) (x&-x)
    inline void update(int x,const int &y,const int &val,const int &vs) {
        while( x <= n ) sgt.insert(root[x],1,n,y,val,vs) , x += lowbit(x);
    }
    inline int querysum(int x,const int &ll,const int &rr) {
        int ret = 0;
        while(x) ret = ( ret + sgt.querysum(root[x],1,n,ll,rr) ) % mod , x -= lowbit(x);
        return ret;
    }
    inline int querysiz(int x,const int &ll,const int &rr) {
        int ret = 0;
        while(x) ret = ( ret + sgt.querysiz(root[x],1,n,ll,rr) ) % mod , x -= lowbit(x);
        return ret;
    }
}bit;

inline int segsum(const int &l,const int &r,const int &ll,const int &rr) {
    return ( bit.querysum(r,ll,rr) - bit.querysum(l-1,ll,rr) + mod ) % mod;
}
inline int segsiz(const int &l,const int &r,const int &ll,const int &rr) {
    return ( bit.querysiz(r,ll,rr) - bit.querysiz(l-1,ll,rr) + mod ) % mod;
}


int main() {
    static int m;
    static lli now;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",seq+i) , scanf("%d",in+seq[i]);
    for(int i=1;i<=n;i++) {
        now = ( now + bit.querysum(i,seq[i]+1,n) ) % mod , now = ( now + (lli) bit.querysiz(i,seq[i]+1,n) * in[seq[i]] % mod ) % mod;
        bit.update(i,seq[i],in[seq[i]],1);
    }
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d",&a,&b);
        if( a > b ) std::swap(a,b);
        if( a == b ) {
            printf("%lld\n",now);
            continue;
        }
        now -= segsum(1,a-1,seq[a]+1,n) + segsum(a+1,n,1,seq[a]-1) , now -= (lli) in[seq[a]] * ( segsiz(1,a-1,seq[a]+1,n) + segsiz(a+1,n,1,seq[a]-1) ) % mod , now = ( now % mod + mod ) % mod;
        now -= segsum(1,b-1,seq[b]+1,n) + segsum(b+1,n,1,seq[b]-1) , now -= (lli) in[seq[b]] * ( segsiz(1,b-1,seq[b]+1,n) + segsiz(b+1,n,1,seq[b]-1) ) % mod , now = ( now % mod + mod ) % mod;
        bit.update(b,seq[b],mod-in[seq[b]],-1) , bit.update(a,seq[a],mod-in[seq[a]],-1);
        if( seq[a] > seq[b] ) now = ( now + in[seq[a]] + in[seq[b]] ) % mod; // it have been subed two times .
        std::swap(seq[a],seq[b]);
        bit.update(a,seq[a],in[seq[a]],1) , bit.update(b,seq[b],in[seq[b]],1);
        now += segsum(1,a-1,seq[a]+1,n) + segsum(a+1,n,1,seq[a]-1) , now += (lli) in[seq[a]] * ( segsiz(1,a-1,seq[a]+1,n) + segsiz(a+1,n,1,seq[a]-1) ) % mod , now = ( now % mod + mod ) % mod;
        now += segsum(1,b-1,seq[b]+1,n) + segsum(b+1,n,1,seq[b]-1) , now += (lli) in[seq[b]] * ( segsiz(1,b-1,seq[b]+1,n) + segsiz(b+1,n,1,seq[b]-1) ) % mod , now = ( now % mod + mod ) % mod;
        if( seq[a] > seq[b] ) now = ( now - in[seq[a]] - in[seq[b]] + mod ) % mod; // it have been added two times .
        printf("%lld\n",now);
    }
    return 0;
}

