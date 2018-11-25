#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=5e5+1e2;
const double eps=1e-8;

int in[maxn],srt[maxn],siz[maxn],len;
int ans[maxn],fa[maxn],ts[maxn],vis[maxn];
int n;

struct SegmentTree {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],lazy[maxn<<3],mi[maxn<<3],cnt;
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void apply(int pos,int delta) {
        mi[pos] += delta , lazy[pos] += delta;
    }
    inline void push(int pos) {
        if( !lazy[pos] || l[pos] == r[pos] ) return;
        apply(lson[pos],lazy[pos]) , apply(rson[pos],lazy[pos]) , lazy[pos] = 0;
    }
    inline void maintain(int pos) {
        if( l[pos] == r[pos] ) return;
        mi[pos] = min( mi[lson[pos]] , mi[rson[pos]] );
    }
    inline void update(int pos,int ll,int rr,int delta) {
        if( r[pos] < ll || rr < l[pos] ) return;
        if( ll <= l[pos] && r[pos] <= rr ) return apply(pos,delta);
        push(pos);
        update(lson[pos],ll,rr,delta) , update(rson[pos],ll,rr,delta);
        maintain(pos);
    }
    inline int query(int pos,int lim) {
        if( l[pos] == r[pos] ) return mi[pos] >= lim ? l[pos]  : l[pos] - 1;
        push(pos);
        if( mi[lson[pos]] >= lim ) return query(rson[pos],lim);
        else return query(lson[pos],lim);
    }
}segt;

inline void getseq() {
    sort(in+1,in+1+n);
    srt[len=1] = in[1] , siz[1] = 1;
    for(int i=2;i<=n;i++) {
        if( in[i] != in[i-1] ) srt[++len] = in[i];
        ++siz[len];
    }
    segt.build(segt.cnt=1,1,len);
    for(int i=1;i<=len;i++) segt.update(1,1,i,siz[i]);
}

inline void calcpoint(int x) {
    if( fa[x] && !vis[fa[x]] ) segt.update(1,1,ans[fa[x]],ts[fa[x]]-1) , vis[fa[x]] = 1;
    int fd = segt.query(1,ts[x]); ans[x] = fd;
    segt.update(1,1,fd,-ts[x]);
}

int main() {
    static double k;
    scanf("%d%lf",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , fa[i] = (int) ( (double) i / k + eps ) , ts[i] = 1;
    getseq();
    for(int i=n;i;i--) if( fa[i] ) ts[fa[i]] += ts[i];
    for(int i=1;i<=n;i++) calcpoint(i);
    for(int i=1;i<=n;i++) printf("%d%c",srt[ans[i]],i!=n?' ':'\n');
    return 0;
}

