#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=5e4+1e2,maxd=5;
const int inf=0x3f3f3f3f;

int cmp;
struct Point {
    int d[maxd];
    friend bool operator < (const Point &a,const Point &b) {
        return a.d[cmp] < b.d[cmp];
    }
}ps[maxn],qr;

int lson[maxn],rson[maxn],mn[maxn][maxd],mx[maxn][maxd],nv[maxn],cnt;
int n,k;

inline void fil(int pos,int id) {
    nv[pos] = id;
    for(int i=0;i<k;i++) mn[pos][i] = mx[pos][i] = ps[id].d[i];
}
inline void update(int fa,int son) {
    for(int i=0;i<k;i++) mn[fa][i] = min( mn[fa][i] , mn[son][i] ) , mx[fa][i] = max( mx[fa][i] , mx[son][i] );
}
inline void build(int pos,int dir,int ll,int rr) {
    const int mid = ( ll + rr ) >> 1;
    cmp = dir , nth_element(ps+ll,ps+mid,ps+rr+1);
    fil(pos,mid) , lson[pos] = rson[pos] = 0;
    if( ll < mid ) build(lson[pos]=++cnt,(dir+1)%k,ll,mid-1) , update(pos,lson[pos]);
    if( mid < rr ) build(rson[pos]=++cnt,(dir+1)%k,mid+1,rr) , update(pos,rson[pos]);
}

inline int sq(const int &x) {
    return x * x;
}
inline int dis(const Point &p,const Point &q) {
    int ret = 0;
    for(int i=0;i<k;i++) ret += sq( p.d[i] - q.d[i] );
    return ret;
}
inline int h(int pos,const Point &p) {
    int ret = 0;
    for(int i=0;i<k;i++)
        if( p.d[i] < mn[pos][i] ) ret += sq( mn[pos][i] - p.d[i] );
        else if( mx[pos][i] < p.d[i] ) ret += sq( p.d[i] - mx[pos][i] );
    return ret;
}

struct Node {
    int dis,id;
    friend bool operator < (const Node &a,const Node &b) {
        return a.dis < b.dis;
    }
};
priority_queue<Node> pq;

inline void query(int pos,const Point &p) {
    int dd = dis(ps[nv[pos]],p);
    if( dd < pq.top().dis ) pq.pop() , pq.push((Node){dd,nv[pos]});
    int hl = lson[pos] ? h(lson[pos],p) : inf , hr = rson[pos] ? h(rson[pos],p) : inf;
    if( hl < hr ) {
        if( hl < pq.top().dis ) query(lson[pos],p);
        if( hr < pq.top().dis ) query(rson[pos],p);
    } else {
        if( hr < pq.top().dis ) query(rson[pos],p);
        if( hl < pq.top().dis ) query(lson[pos],p);
    }
}

inline void solve_case(const Point &p,int m) {
    static int ans[10];
    for(int i=1;i<=m;i++) pq.push((Node){inf,0});
    query(1,p);
    for(int i=m;i;i--) ans[i] = pq.top().id , pq.pop();
    printf("the closest %d points are:\n",m);
    for(int i=1;i<=m;i++) for(int j=0;j<k;j++) printf("%d%c",ps[ans[i]].d[j],j!=k-1?' ':'\n');
}

int main() {
    static int t,m;
    while( scanf("%d%d",&n,&k) == 2 ) {
        for(int i=1;i<=n;i++) for(int j=0;j<k;j++) scanf("%d",ps[i].d+j);
        build(cnt=1,0,1,n) , scanf("%d",&t);
        while(t--) {
            for(int i=0;i<k;i++) scanf("%d",qr.d+i);
            scanf("%d",&m) , solve_case(qr,m);
        }
    }
    return 0;
}
