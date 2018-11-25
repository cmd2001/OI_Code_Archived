#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxq=5e5+1e2,maxe=5e6+1e2;

int in[maxn],srt[maxn],len;
int root[maxn],ans[maxq],n;

struct SegmentTree {
    int lson[maxe],rson[maxe],sum[maxe],cnt;
    inline void insert(int& pos,int l,int r,const int &tar) {
        if( !pos ) pos = ++cnt; sum[pos] = 1;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],l,mid,tar);
        else insert(rson[pos],mid+1,r,tar);
    }
    inline int merge(int p1,int p2,int l,int r) {
        if( !sum[p1] || !sum[p2] ) return sum[p1] ? p1 : p2;
        const int ret = ++cnt , mid = ( l + r ) >> 1;
        sum[ret] = sum[p1] + sum[p2];
        lson[ret] = merge(lson[p1],lson[p2],l,mid) ,
        rson[ret] = merge(rson[p1],rson[p2],mid+1,r);
        return ret;
    }
    inline int kth(int pos,int l,int r,int k) {
        if( !pos || k > sum[pos] ) return -1;
        if( l == r ) return l;
        const int mid = ( l + r ) >> 1;
        if( k <= sum[rson[pos]] ) return kth(rson[pos],mid+1,r,k);
        else return kth(lson[pos],l,mid,k-sum[rson[pos]]);
    }
}segt;

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline void merge(int x,int y) {
        fa[x] = y;
    }
    inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

struct Edge {
    int a,b,l;
    friend bool operator < (const Edge &a,const Edge &b) {
        return a.l < b.l;
    }
}es[maxq];

struct Query {
    int st,lim,k,id;
    friend bool operator < (const Query &a,const Query &b) {
        return a.lim < b.lim;
    }
}qs[maxq];

int main() {
    static int m,q,cur=1;
    scanf("%d%d%d",&n,&m,&q) , ufs.init();
    for(int i=1;i<=n;i++) scanf("%d",in+i) , srt[i] = in[i];
    sort(srt+1,srt+1+n) , len = unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++) in[i] = lower_bound(srt+1,srt+1+len,in[i]) - srt;
    for(int i=1;i<=m;i++) scanf("%d%d%d",&es[i].a,&es[i].b,&es[i].l);
    for(int i=1;i<=q;i++) scanf("%d%d%d",&qs[i].st,&qs[i].lim,&qs[i].k) , qs[i].id = i;
    sort(es+1,es+1+m) , sort(qs+1,qs+1+q);
    for(int i=1;i<=n;i++) segt.insert(root[i],1,len,in[i]);
    for(int i=1;i<=m;i++) {
        while( cur <= q && qs[cur].lim < es[i].l ) {
            int frt = root[ufs.findfa(qs[cur].st)];
            ans[qs[cur].id] = segt.kth(frt,1,len,qs[cur].k) , ++cur;
        }
        if( ufs.findfa(es[i].a) != ufs.findfa(es[i].b) ) {
            int fa = ufs.findfa(es[i].a) , fb = ufs.findfa(es[i].b);
            root[fb] = segt.merge(root[fa],root[fb],1,len) , ufs.merge(fa,fb);
        }
    }
    while( cur <= q ) {
        ans[qs[cur].id] = segt.kth(root[ufs.findfa(qs[cur].st)],1,len,qs[cur].k) , ++cur;
    }
    for(int i=1;i<=q;i++) printf("%d\n",(~ans[i])?srt[ans[i]]:-1);
    return 0;
}
