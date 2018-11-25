#pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
typedef long long int lli;
const int maxn=2e5+1e2;

struct Point {
    lli x,y;
    friend Point operator - (const Point &a,const Point &b) { return (Point){a.x-b.x,a.y-b.y}; }
    friend lli operator * (const Point &a,const Point &b) { return a.x * b.y - a.y * b.x; }
    friend lli operator ^ (const Point &a,const Point &b) { return a.x * b.x + a.y * b.y; }
    friend bool operator < (const Point &a,const Point &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
}ps[maxn];

struct Query {
    Point p;
    int id;
};

namespace Convex {
    int top;
    Point ps[maxn];
    inline void build(std::vector<Point> &v) {
        std::sort(v.begin(),v.end()) , top = 0;
        for(unsigned i=0;i<v.size();i++) {
            while( top && ps[top].y <= v[i].y ) --top;
            while( top > 1 && ( ps[top] - ps[top-1] ) * ( v[i] - ps[top] ) >= 0 ) --top;
            ps[++top] = v[i];
        }
    }
    inline lli tri(const Point &ref) {
        int l = 1 , r = top , lmid , rmid;
        lli ret = 0;
        while( r > l + 2 ) {
            lmid = ( l + l + r ) / 3 , rmid = ( l + r + r ) / 3;
            if( (ps[lmid]^ref) < (ps[rmid]^ref) ) l = lmid;
            else r = rmid;
        }
        for(int i=l;i<=r;i++) ret = std::max( ret , ps[i] ^ ref );
        return ret;
    }
}

int st[maxn];
std::set<int> vs;
lli ans[maxn];

namespace SegmentTree {
    std::vector<Point> pts[maxn<<2];
    std::vector<Query> qrs[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void insert_point(int pos,int l,int r,const int &ll,const int &rr,const Point &p) {
        if( ll <= l && r <= rr ) return pts[pos].push_back(p);
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) insert_point(lson(pos),l,mid,ll,rr,p);
        else if( ll > mid ) insert_point(rson(pos),mid+1,r,ll,rr,p);
        else insert_point(lson(pos),l,mid,ll,rr,p) , insert_point(rson(pos),mid+1,r,ll,rr,p);
    }
    inline void insert_query(int pos,int l,int r,const int &tar,const Query &q) {
        qrs[pos].push_back(q);
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert_query(lson(pos),l,mid,tar,q);
        else insert_query(rson(pos),mid+1,r,tar,q);
    }
    inline void dfs(int pos,int l,int r) {
        if( pts[pos].size() && qrs[pos].size() ) {
            Convex::build(pts[pos]);
            for(unsigned i=0;i<qrs[pos].size();i++) ans[qrs[pos][i].id] = std::max( ans[qrs[pos][i].id] , Convex::tri(qrs[pos][i].p) );
        }
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        dfs(lson(pos),l,mid) , dfs(rson(pos),mid+1,r);
    }
}
using namespace SegmentTree;

int main() {
    static int n,iid,qid;
    scanf("%d",&n);
    for(int i=1,o,x,y;i<=n;i++) {
        scanf("%d%d",&o,&x);
        if( o != 2 ) {
            scanf("%d",&y);
            if( o == 1 ) ps[++iid] = (Point){(lli)x,(lli)y} , vs.insert(iid) , st[iid] = i;
            else if( o == 3 ) insert_query(1,1,n,i,(Query){(lli)x,(lli)y,++qid});
        } else insert_point(1,1,n,st[x],i-1,ps[x]) , vs.erase(x);
    }
    while( vs.size() ) {
        int t = *vs.begin(); vs.erase(vs.begin());
        insert_point(1,1,n,st[t],n,ps[t]);
    }
    dfs(1,1,n);
    for(int i=1;i<=qid;i++) printf("%lld\n",ans[i]);
    return 0;
}
