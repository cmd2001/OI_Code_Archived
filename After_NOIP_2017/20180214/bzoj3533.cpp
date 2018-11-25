#include<cstdio>
#include<algorithm>
#include<vector>
#define lli long long int
using namespace std;
const int maxn=4e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

struct Point {
    lli x,y;
    friend Point operator + (const Point &a,const Point &b) {
        return (Point){a.x+b.x,a.y+b.y};
    }
    friend Point operator - (const Point &a,const Point &b) {
        return (Point){a.x-b.x,a.y-b.y};
    }
    friend lli operator * (const Point &a,const Point &b) {
        return a.x * b.y - a.y * b.x;
    }
    friend lli operator ^ (const Point &a,const Point &b) {
        return a.x * b.x + a.y * b.y;
    }
    friend bool operator < (const Point &a,const Point &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
};
vector<Point> up[maxn<<3],down[maxn<<3];
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],cnt;

inline Point readnxt(const vector<Point> &l,const vector<Point> &r,vector<Point>::const_iterator &lat,vector<Point>::const_iterator &rat) {
    if( lat == l.end() ) return *rat++;
    else if( rat == r.end() ) return *lat++;
    return *lat < *rat ? *lat++ : *rat++;
}
inline void Merge_Up(vector<Point> &dst,const vector<Point> &l,const vector<Point> &r) {
    vector<Point>::const_iterator lat=l.begin(),rat=r.begin();
    const unsigned fs = l.size() + r.size();
    int top = -1;
    for(unsigned i=1;i<=fs;i++) {
        Point now = readnxt(l,r,lat,rat);
        if( top < 1 ) dst.push_back(now) , ++top ;
        else {
            while( top >= 1 && ( dst[top] - dst[top-1] ) * ( now - dst[top] ) >= 0 ) dst.pop_back() , --top;
            dst.push_back(now) , ++top;
        }
    }
}
inline void Merge_Down(vector<Point> &dst,const vector<Point> &l,const vector<Point> &r) {
    vector<Point>::const_iterator lat=l.begin(),rat=r.begin();
    const unsigned fs = l.size() + r.size();
    int top = -1;
    for(unsigned i=1;i<=fs;i++) {
        Point now = readnxt(l,r,lat,rat);
        if( top < 1 ) dst.push_back(now) , ++top;
        else {
            while( top >= 1 && ( dst[top] - dst[top-1] ) * ( now - dst[top] ) <= 0 ) dst.pop_back() , --top;
            dst.push_back(now) , ++top;
        }
    }
}
inline lli tri(const vector<Point> &sou,const Point &p) {
    int l = 0 , r = sou.size() - 1 , lmid , rmid;
    while( r > l + 2 ) {
        lmid = ( l + l + r ) / 3 , rmid = ( l + r + r ) / 3;
        if( ( sou[lmid] ^ p ) < ( sou[rmid] ^ p ) ) l = lmid;
        else r = rmid;
    }
    lli ret = -inf;
    for(int i=l;i<=r;i++) ret = max( ret , sou[i] ^ p );
    return ret;
}
inline void build(int pos,int l,int r) {
    if( l == r ) return;
    const int mid = ( l + r ) >> 1;
    build(lson[pos]=++cnt,l,mid) , build(rson[pos]=++cnt,mid+1,r);
}
inline void insert(int pos,int l,int r,const int &tar,const Point &p) {
    if( l == r ) {
        up[pos].push_back(p) , down[pos].push_back(p);
        return;
    }
    const int mid = ( l + r ) >> 1;
    if( tar <= mid ) insert(lson[pos],l,mid,tar,p);
    else insert(rson[pos],mid+1,r,tar,p);
    if( tar == r ) {
        Merge_Up(up[pos],up[lson[pos]],up[rson[pos]]);
        Merge_Down(down[pos],down[lson[pos]],down[rson[pos]]);
    }
}
inline lli query(int pos,int l,int r,const int &ll,const int &rr,const Point &p) {
    if( ll <= l && r <= rr ) return p.y >= 0 ? tri(up[pos],p) : tri(down[pos],p);
    const int mid = ( l + r ) >> 1;
    if( rr <= mid ) return query(lson[pos],l,mid,ll,rr,p);
    if( ll > mid ) return query(rson[pos],mid+1,r,ll,rr,p);
    return max( query(lson[pos],l,mid,ll,rr,p) , query(rson[pos],mid+1,r,ll,rr,p) );
}
inline void decode(int &x,const lli &lastans) {
    x ^= ( lastans & 0x7fffffff );
}

int main() {
    static int n,tpe,len;
    static lli lastans;
    static char t[10];
    scanf("%d%s",&n,t) , tpe = *t != 'E';
    build(cnt=1,1,n);
    for(int i=1,x,y,l,r;i<=n;i++) {
        scanf("%s%d%d",t,&x,&y);
        if( tpe ) decode(x,lastans) , decode(y,lastans);
        if( *t == 'A' ) insert(1,1,n,++len,(Point){x,y});
        else {
            scanf("%d%d",&l,&r);
            if( tpe ) decode(l,lastans) , decode(r,lastans);
            lastans = query(1,1,n,l,r,(Point){x,y});
            printf("%lld\n",lastans);
        }
    }
    return 0;
}

