#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#define debug cerr
using namespace std;
// segment tree and binary search tree optimized network flow and output .
const int maxn=2e4+1e2,maxt=6e5+1e2,maxe=1e7+1e2;
const int inf=0x3f3f3f3f;

int st,ed,pcnt;
namespace NetworkFlow {
    int s[maxt<<1],t[maxe<<1],nxt[maxe<<1],f[maxe<<1];
    int dep[maxt<<1];
    inline void coredge(int from,int to,int flow) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow) {
        coredge(from,to,flow) , coredge(to,from,0);
    }
    inline bool bfs() {
        memset(dep,-1,sizeof(dep)) , dep[st] = 0;
        queue<int> q; q.push(st);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int at=s[pos];at;at=nxt[at]) if( f[at] && !~dep[t[at]] ) dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
        }
        return ~dep[ed];
    }
    inline int dfs(int pos,int flow) {
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at]) if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],min(flow,f[at])) , ret += now , flow -= now , f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline int dinic() {
        int ret = 0;
        while( bfs() ) ret += dfs(st,inf);
        return ret;
    }
}

int srt[maxn],len;

struct Point {
    int x,y,id;
    friend bool operator < (const Point &a,const Point &b) {
        return a.y < b.y;
    }
}in[maxn];

inline bool cmp(const Point &x,const Point &y) {
    return x.x < y.x;
}

struct BinarySearchTree {
    int l[maxt],r[maxt],miy[maxt],miid[maxt],lson[maxt],rson[maxt],rid[maxt],cnt;
    inline void build(int &pos,int ll,int rr) {
        rid[pos=++cnt] = ++pcnt; const int mid = ( ll + rr ) >> 1;
        NetworkFlow::singledge(rid[pos],in[mid].id,1) , miy[pos] = in[mid].y , miid[pos] = in[mid].id;
        l[pos] = in[ll].y , r[pos] = in[rr].y;
        if( ll < mid ) build(lson[pos],ll,mid-1) , NetworkFlow::singledge(rid[pos],rid[lson[pos]],inf);
        if( mid < rr ) build(rson[pos],mid+1,rr) , NetworkFlow::singledge(rid[pos],rid[rson[pos]],inf);
    }
    inline void query(int pos,const int &ll,const int &rr,const int &id) {
        if( !pos || rr < l[pos] || r[pos] < ll ) return;
        if( ll <= l[pos] && r[pos] <= rr ) return NetworkFlow::singledge(id,rid[pos],1);
        if( ll <= miy[pos] && miy[pos] <= rr ) NetworkFlow::singledge(id,miid[pos],1);
        query(lson[pos],ll,rr,id) , query(rson[pos],ll,rr,id);
    }
}bst;

struct SegmentTree {
    int vl[maxn<<2],vr[maxn<<2],rid[maxn<<2],roots[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void build(int pos,int l,int r,int ll,int rr) {
        vl[pos] = ll , vr[pos] = rr , rid[pos] = ++pcnt;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1 , tmid = upper_bound(in+ll,in+rr+1,(Point){mid,-1,-1},cmp) - in - 1;
        build(lson(pos),l,mid,ll,tmid) , build(rson(pos),mid+1,r,tmid+1,rr);
        NetworkFlow::singledge(rid[pos],rid[lson(pos)],inf) , NetworkFlow::singledge(rid[pos],rid[rson(pos)],inf);
    }
    inline void dfs(int pos,int l,int r) {
        if( l == r ) return sort(in+vl[pos],in+vr[pos]+1) , bst.build(roots[pos],vl[pos],vr[pos]);
        const int mid = ( l + r ) >> 1;
        dfs(lson(pos),l,mid) , dfs(rson(pos),mid+1,r);
        sort(in+vl[pos],in+vr[pos]+1) , bst.build(roots[pos],vl[pos],vr[pos]); // maybe we should use merge-sort here .
    }
    inline void query(int pos,int l,int r,const int &ll,const int &rr,const int &yll,const int &yrr,const int &id) {
        if( ll <= l && r <= rr ) return bst.query(roots[pos],yll,yrr,id);
        const int mid = ( l + r ) >> 1;
        if( ll <= mid ) query(lson(pos),l,mid,ll,rr,yll,yrr,id);
        if( mid < rr ) query(rson(pos),mid+1,r,ll,rr,yll,yrr,id);
    }
}sgt;

int n,m,ans;

namespace Graph {
    int s[maxt],t[maxe<<1],nxt[maxe<<1],l[maxe<<1];
    int stk[maxe<<1],top;
    inline void addedge(int from,int to,int len) {
        static int cnt;
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void dfs(int pos) {
        for(int &at=s[pos];at;at=nxt[at]) if( l[at]-- ) dfs(t[at]) , stk[++top] = pos;
    }
    inline void print() {
        for(int i=1;i<=top;i++) {
            if( stk[i] <= n ) printf("%d ",stk[i]); // left point .
            else if( stk[i] <= n + m ) printf("%d\n",stk[i]-n);
        }
    }
}
inline void transbuild() {
    for(int i=1;i<=pcnt;i++) for(int at=NetworkFlow::s[i];at;at=NetworkFlow::nxt[at]) if( ! ( at & 1 ) && NetworkFlow::f[at^1] ) {
        Graph::addedge(i,NetworkFlow::t[at],NetworkFlow::f[at^1]);
    }
    Graph::addedge(ed,st,ans);
}


int main() {
    scanf("%d%d",&n,&m) , st = n + m + 1 , pcnt = ed = n + m + 2;
    for(int i=1;i<=n;i++) NetworkFlow::singledge(i,ed,1);
    for(int i=1;i<=m;i++) NetworkFlow::singledge(st,n+i,1);
    for(int i=1,x,y;i<=n;i++) scanf("%d%d",&x,&y) , in[i].x = x + y , in[i].y = x - y , in[i].id = i; // covert .
    sort(in+1,in+1+n,cmp);
    for(int i=1;i<=n;i++) {
        if( i == 1 || in[i].x != srt[len] ) srt[++len] = in[i].x;
        in[i].x = len;
    }
    sgt.build(1,1,len,1,n) , sgt.dfs(1,1,len);
    for(int i=1,x,y,d,ix,iy,l,r;i<=m;i++) {
        scanf("%d%d%d",&ix,&iy,&d) , x = ix + iy , y = ix - iy;
        l = lower_bound(srt+1,srt+1+len,x-d) - srt , r = upper_bound(srt+1,srt+1+len,x+d) - srt - 1;
        if( l > r ) continue;
        sgt.query(1,1,len,l,r,y-d,y+d,i+n);
    }
    printf("%d\n",ans=NetworkFlow::dinic());
    transbuild() , Graph::dfs(st) , Graph::print();
    return 0;
}

