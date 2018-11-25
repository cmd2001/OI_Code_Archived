#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=2e4+1e2,maxb=150;

int in[maxn],srt[maxn],len;
struct BinaryIndexTree {
    int dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,int x) {
        while( pos <= len ) dat[pos] += x , pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while( pos ) ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
}bt[maxb];
int st[maxb],ed[maxb],bel[maxn],cnt;
int n,ans;

inline void buildblk(int id) {
    for(int i=st[id];i<=ed[id];i++)
        bt[id].update(in[i],1);
}
inline void modifyblk(int id,int x,int ope) {
    bt[id].update(x,ope);
}
inline int query_full_abo(int id,int x) { // return number of in[i] which > x
    return ed[id] - st[id] + 1 - bt[id].query(x);
}
inline int query_part_abo(int id,int l,int r,int x) {
    int ret = 0;
    l = max( l , st[id] ) , r = min( r , ed[id] );
    for(int i=l;i<=r;i++) ret += ( in[i] > x );
    return ret;
}
inline int query_abo(int l,int r,int x) {
    if( bel[l] == bel[r] ) return query_part_abo(bel[l],l,r,x);
    int ret = 0;
    for(int i=bel[l]+1;i<bel[r];i++) ret += query_full_abo(i,x);
    return ret + query_part_abo(bel[l],l,r,x) + query_part_abo(bel[r],l,r,x);
}
inline int query_full_bel(int id,int x) { // return number of in[i] which < x
    return bt[id].query(x-1);
}
inline int query_part_bel(int id,int l,int r,int x) {
    int ret = 0;
    l = max( l , st[id] ) , r = min( r , ed[id] );
    for(int i=l;i<=r;i++) ret += ( in[i] < x );
    return ret;
}
inline int query_bel(int l,int r,int x) {
    if( bel[l] == bel[r] ) return query_part_bel(bel[l],l,r,x);
    int ret = 0;
    for(int i=bel[l]+1;i<bel[r];i++) ret += query_full_bel(i,x);
    return ret + query_part_bel(bel[l],l,r,x) + query_part_bel(bel[r],l,r,x);
}

inline void swp(int a,int b) {
    if( a > b ) swap(a,b);
    if( a == b ) return;
    if( a + 1 == b ) {
        if( in[a] > in[b] ) --ans;
        else if( in[a] < in[b] ) ++ans;
    } else {
        ans -= query_abo(a+1,b-1,in[b]) + query_bel(a+1,b-1,in[a]);
        ans += query_abo(a+1,b-1,in[a]) + query_bel(a+1,b-1,in[b]);
        if( in[a] > in[b] ) --ans;
        else if( in[a] < in[b] ) ++ans;
    }
    modifyblk(bel[a],in[a],-1) , modifyblk(bel[b],in[b],-1);
    swap(in[a],in[b]);
    modifyblk(bel[a],in[a],+1) , modifyblk(bel[b],in[b],+1);
}
inline void gen() {
    int sq = sqrt(n);
    for(int l=1,r;l<=n;l=r+1) {
        r = min( l + sq - 1 , n ) , ++cnt;
        st[cnt] = l , ed[cnt] = r;
        for(int i=l;i<=r;i++) bel[i] = cnt;
    }
    for(int i=1;i<=cnt;i++) buildblk(i);
}
inline void init() {
    memcpy(srt+1,in+1,sizeof(int)*n);
    sort(srt+1,srt+1+n) , len = unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++) in[i] = lower_bound(srt+1,srt+1+len,in[i]) - srt;
}

int main() {
    static int m;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    init() , gen();
    for(int i=2;i<=n;i++)
        ans += query_abo(1,i-1,in[i]);
    scanf("%d",&m);
    for(int i=1,a,b;i<=m;i++) {
        printf("%d\n",ans);
        scanf("%d%d",&a,&b);
        swp(a,b);
    }
    printf("%d\n",ans);
    return 0;
}
