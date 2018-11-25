#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define lli long long int
using namespace std;
const int maxn=5e4+1e2;

int in[maxn],bel[maxn],cnt[maxn],n,m,ll,rr;
lli ans[maxn],now;
struct Node {
    int l,r,id;
    friend bool operator < (const Node &a,const Node &b) {
        return bel[a.l] != bel[b.l] ? bel[a.l] < bel[b.l] : a.r < b.r;
    }
}ns[maxn];

inline void add(int pos) {
    now += 2 * cnt[pos] + 1 , ++cnt[pos];
}
inline void mins(int pos) {
    now -= 2 * cnt[pos] - 1 , --cnt[pos];
}
inline void move(int tarl,int tarr) {
    while( ll < tarl ) mins(in[ll++]);
    while( tarl < ll ) add(in[--ll]);
    while( tarr < rr ) mins(in[rr--]);
    while( rr < tarr ) add(in[++rr]);
}
inline void getans() {
    cnt[in[ll=rr=1]] = 1 , now = 1;
    for(int i=1;i<=m;i++) {
        move(ns[i].l,ns[i].r);
        ans[ns[i].id] = now;
    }
}
inline void gen() {
    const int bs = sqrt(n);
    int cnt = 0;
    for(int l=1,r;l<=n;l=r+1) {
        r = min( l + bs - 1 , n ) , ++cnt;
        for(int i=l;i<=r;i++) bel[i] = cnt;
    }
}

int main() {
    scanf("%d%d%*d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1;i<=m;i++) scanf("%d%d",&ns[i].l,&ns[i].r) , ns[i].id = i;
    gen(),sort(ns+1,ns+1+m),getans();
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}
