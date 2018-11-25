#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=5e4+1e2;

int in[maxn],srt[maxn],cnt;
struct BinaryIndexTree {
    int dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,int x) {
        while( pos <= cnt ) dat[pos] += x , pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while(pos) ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
}bit;

int ans[maxn],bel[maxn],ll,rr,now;
struct Node {
    int l,r,id;
    friend bool operator < (const Node &a,const Node &b) {
        return bel[a.l] != bel[b.l] ? bel[a.l] < bel[b.l] : a.r < b.r;
    }
}ns[maxn];

inline void move(int l,int r) {
    while( rr < r ) bit.update(in[++rr],1) , now += bit.query(cnt) - bit.query(in[rr]);
    while( r < rr ) now -= bit.query(cnt) - bit.query(in[rr]) , bit.update(in[rr--],-1);
    while( l < ll ) bit.update(in[--ll],1) , now += bit.query(in[ll]-1);
    while( ll < l ) now -= bit.query(in[ll]-1) , bit.update(in[ll++],-1);
}

inline void initblk(int n) {
    const int sq = sqrt(n);
    int cnt = 0;
    for(int l=1,r;l<=n;l=r+1) {
        r = min( n , l + sq - 1 ) , ++cnt;
        for(int i=l;i<=r;i++) bel[i] = cnt;
    }
}

int main() {
    static int n,m;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , srt[i] = in[i];
    sort(srt+1,srt+1+n) , cnt = unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++) in[i] = lower_bound(srt+1,srt+1+cnt,in[i]) - srt;
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d%d",&ns[i].l,&ns[i].r) , ns[i].id = i;
    initblk(n) , sort(ns+1,ns+1+m) , bit.update(in[ll=rr=1],1);
    for(int i=1;i<=m;i++) move(ns[i].l,ns[i].r) , ans[ns[i].id] = now;
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}