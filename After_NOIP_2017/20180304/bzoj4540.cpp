#include<cstdio>
#include<algorithm>
#include<cmath>
#define lli long long int
using std::sort;
using std::reverse;
using std::min;
const int maxn=1e5+1e2,maxl=20;

int in[maxn],mi[maxn][maxl],Log[maxn],bel[maxn];
lli fl[maxn],fr[maxn],ans[maxn],now;
int l,r,n;

struct Node {
    int l,r,id;
    friend bool operator < (const Node &a,const Node &b) {
        return bel[a.l] != bel[b.l] ? bel[a.l] < bel[b.l] : a.r < b.r;
    }
}ns[maxn];

inline void pre() {
    for(int i=2;i<=n;i++) Log[i] = Log[i>>1] + 1;
    for(int i=1;i<=n;i++) *mi[i] = i;
    for(int L=1;L<=Log[n];L++)
        for(int p=1;p+(1<<L)-1<=n;p++) {
            const int nxt = p + ( 1 << (L-1) );
            mi[p][L] = in[mi[p][L-1]] < in[mi[nxt][L-1]] ? mi[p][L-1] : mi[nxt][L-1];
        }
}
inline int query(int l,int r) {
    const int L = Log[r-l+1];
    return in[mi[l][L]] < in[mi[r-(1<<L)+1][L]] ? mi[l][L] : mi[r-(1<<L)+1][L];
}
inline void dp(lli* dst) {
    static int stk[maxn],top;
    stk[top=1] = 0;
    for(int i=1;i<=n;i++) {
        while( top && in[stk[top]] > in[i] ) --top;
        dst[i] = dst[stk[top]] + (lli) ( i - stk[top] ) * in[i];
        stk[++top] = i;
    }
}
inline void mover(int o) {
    const int p = query(l,r+1);
    now += o * ( (lli) in[p] * (p-l+1) + fl[r+1] - fl[p] );
}
inline void movel(int o) {
    int p = query(l-1,r);
    now += o * ( (lli) in[p] * (r-p+1) + fr[l-1] - fr[p] );
}
inline void getblk() {
    const int blksiz = sqrt(n);
    int cnt = 0;
    for(int l=1,r;l<=n;l=r+1) {
        r = min( l + blksiz - 1 , n ) , ++cnt;
        for(int k=l;k<=r;k++) bel[k] = cnt;
    }
}

int main() {
    static int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1;i<=m;i++) scanf("%d%d",&ns[i].l,&ns[i].r) , ns[i].id = i;
    pre() , getblk() , sort(ns+1,ns+1+m);
    dp(fl) , reverse(in+1,in+1+n) ,
    dp(fr) , reverse(in+1,in+1+n)  , reverse(fr+1,fr+1+n);
    now = in[l=r=1];
    for(int i=1;i<=m;i++) {
        while( r < ns[i].r ) mover(1) , ++r ;
        while( ns[i].l < l ) movel(1) , --l;
        while( ns[i].r < r ) --r , mover(-1);
        while( l < ns[i].l ) ++l , movel(-1);
        ans[ns[i].id] = now;
    }
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}
