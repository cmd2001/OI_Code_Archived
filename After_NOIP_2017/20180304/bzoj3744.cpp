#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=5e4+1e2,maxs=250,maxe=2e6;

int n,len;
struct BinaryIndexTree {
    int dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos) {
        while( pos <= len ) ++dat[pos] , pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while(pos) ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
    inline void reset() { memset(dat+1,0,sizeof(int)*(len)); }
}bit;

struct ChairManTree {
    int lson[maxe],rson[maxe],sum[maxe],cnt;
    inline void build(int pos,int ll,int rr) {
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void insert(int pos,int pre,int l,int r,int tar) {
        lson[pos] = lson[pre] , rson[pos] = rson[pre] , sum[pos] = sum[pre] + 1;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos]=++cnt,lson[pre],l,mid,tar);
        else insert(rson[pos]=++cnt,rson[pre],mid+1,r,tar);
    }
    inline int query(int pos,int pre,int l,int r,const int &ll,const int &rr) {
        if( sum[pos] == sum[pre] ) return 0;
        if( ll <= l && r <= rr ) return sum[pos] - sum[pre];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson[pos],lson[pre],l,mid,ll,rr);
        else if( ll > mid ) return query(rson[pos],rson[pre],mid+1,r,ll,rr);
        return query(lson[pos],lson[pre],l,mid,ll,rr) + query(rson[pos],rson[pre],mid+1,r,ll,rr);
    }
}cmt;

int in[maxn],srt[maxn],bel[maxn],st[maxs],ed[maxs],cnt;
int pre[maxs][maxn];
int roots[maxn];

inline void getpre() {
    for(int i=1;i<=cnt;i++) {
        bit.reset();
        for(int j=st[i];j<=n;j++) {
            pre[i][j] = pre[i][j-1] + bit.query(len-in[j]);
            bit.update(len-in[j]+1);
        }
    }
}
inline int forceblk(int st,int ed,int rtpos) { // [st,ed] [full blocks] .
    int ret = 0;
    for(int i=st;i<=ed;i++)
        if( in[i] - 1 ) {
            ret += cmt.query(rtpos,roots[i],1,len,1,in[i]-1);
        }
    return ret;
}
inline int query(int l,int r) {
    int ret = 0;
    if( bel[l] == bel[r] ) ret = forceblk(l,r,roots[r]);
    else {
        ret = forceblk(l,ed[bel[l]],roots[r]);
        ret += pre[bel[l]+1][r];
    }
    return ret;
}
inline void init() {
    const int blksiz = sqrt(n);
    for(int l=1,r;l<=n;l=r+1) {
        r = min( l + blksiz - 1 , n ) , st[++cnt] = l , ed[cnt] = r;
        for(int k=l;k<=r;k++) bel[k] = cnt;
    }
    memcpy(srt+1,in+1,sizeof(int)*n);
    sort(srt+1,srt+1+n) , len = unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++) in[i] = lower_bound(srt+1,srt+1+len,in[i]) - srt;
    cmt.build(roots[0]=cmt.cnt=1,1,len);
    for(int i=1;i<=n;i++) cmt.insert(roots[i]=++cmt.cnt,roots[i-1],1,len,in[i]);
}

int main() {
    static int m;
    static int l,r,ans;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    init() , getpre();
    scanf("%d",&m);
    for(int i=1;i<=m;i++) {
        scanf("%d%d",&l,&r) , l ^= ans , r ^= ans;
        ans = query(l,r);
        printf("%d\n",ans);
    }
    return 0;
}
