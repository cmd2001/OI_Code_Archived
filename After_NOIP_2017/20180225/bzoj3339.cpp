#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2e5+1e2;

struct SegmentTree {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],dat[maxn<<3],cnt;
    
    SegmentTree() { memset(dat,0x3f,sizeof(dat)); }
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void update(int pos,int ll,int rr,int val) {
        if( rr < l[pos] || r[pos] < ll ) return;
        if( ll <= l[pos] && r[pos] <= rr ) {
            dat[pos] = min( dat[pos] , val );
            return;
        }
        update(lson[pos],ll,rr,val) , update(rson[pos],ll,rr,val);
    }
    inline int query(int pos,int tar) {
        if( l[pos] == r[pos] ) return dat[pos];
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( tar <= mid ) return min(query(lson[pos],tar),dat[pos]);
        else return min(query(rson[pos],tar),dat[pos]);
    }
}st;

struct QNode {
    int l,r,id;
    friend bool operator < (const QNode &a,const QNode &b) {
        return a.l < b.l;
    }
}ns[maxn];
int in[maxn],nxt[maxn],lst[maxn],ini[maxn],mrk[maxn],ans[maxn];
int n,m;

inline void pre() {
    st.build(st.cnt=1,1,n);
    int now = 0;
    for(int i=1;i<=n;i++) {
        mrk[in[i]] = 1;
        while( mrk[now] ) ++now;
        ini[i] = now;
    }
    for(int i=0;i<=2e5;i++) lst[i] = n + 1;
    for(int i=n;i;i--) nxt[i] = lst[in[i]] , lst[in[i]] = i;
    for(int i=1;i<=n;i++) st.update(1,i,i,ini[i]);
}

inline void getans() {
    int cur = 1;
    for(int i=1;i<=n;i++) {
        while( cur <= m && ns[cur].l == i ) {
            ans[ns[cur].id] = st.query(1,ns[cur].r);
            ++cur;
        }
        st.update(1,i+1,nxt[i]-1,in[i]);
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1;i<=m;i++) scanf("%d%d",&ns[i].l,&ns[i].r) , ns[i].id = i;
    sort(ns+1,ns+1+m);
    pre() , getans();
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}


