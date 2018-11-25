#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2e5+1e2,maxe=2e7+1e2;

struct PersistentSegmentTree {
    int lson[maxe],rson[maxe],mx[maxe],cnt;
    inline void insert(int &pos,int l,int r,const int &tar,const int &x) {
        if( !pos ) pos = ++cnt;
        if( l == r ) return void(mx[pos] = max( mx[pos] , x ));
        const int mid = ( l + r ) >> 1;
        tar <= mid ? insert(lson[pos],l,mid,tar,x) : insert(rson[pos],mid+1,r,tar,x);
    }
    inline int merge(int a,int b,int l,int r) {
        if( !a || !b ) return a | b;
        const int ret = ++cnt;
        if( l == r ) return mx[ret] = mx[a] + mx[b] , ret;
        const int mid = ( l + r ) >> 1;
        lson[ret] = merge(lson[a],lson[b],l,mid) , rson[ret] = merge(rson[a],rson[b],mid+1,r) , mx[ret] = max( mx[lson[ret]] , mx[rson[ret]] );
        return ret;
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr) {
        if( !pos || ( ll <= l && r <= rr ) ) return mx[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson[pos],l,mid,ll,rr);
        else if( ll > mid ) return query(rson[pos],mid+1,r,ll,rr);
        else return max( query(lson[pos],l,mid,ll,rr) , query(rson[pos],mid+1,r,ll,rr) );
    }
}pst;

int s[maxn],t[maxn],nxt[maxn];
int in[maxn],srt[maxn],len;
int root[maxn],ans;

inline void addedge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos) {
    static int ff;
    for(int at=s[pos];at;at=nxt[at]) dfs(t[at]) , root[pos] = pst.merge(root[pos],root[t[at]],1,len);
    ans = max( ans , ff = ( pst.query(root[pos],1,len,1,in[pos]) + 1 ) ) , pst.insert(root[pos],1,len,in[pos],ff);
}


int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , srt[i] = in[i];
    sort(srt+1,srt+1+n) , len = unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++) in[i] = lower_bound(srt+1,srt+1+len,in[i]) - srt;
    for(int i=2,t;i<=n;i++) scanf("%d",&t) , addedge(t,i);
    dfs(1) , printf("%d\n",ans);
    return 0;
}
