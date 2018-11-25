#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define debug cout
typedef long long int lli;
typedef long double ldb;
using namespace std;
const int maxn=1e5+1e2;
const lli mul = 1e13 + 1e10;

struct Convex {
    struct Point {
        lli x,y;
        friend Point operator - (const Point &a,const Point &b) {
            return (Point){a.x-b.x,a.y-b.y};
        }
        friend ldb operator * (const Point &a,const Point &b) {
            return (ldb)a.x*b.y - (ldb)a.y*b.x;
        }
        friend lli operator ^ (const Point &a,const Point &b) {
            return a.x * b.x + a.y * b.y;
        }
    }ps[maxn];
    int top;
    inline void push(const Point &p) {
        while( top > 1 ) {
            if( p.x == ps[top].x && p.y > ps[top].y ) --top;
            else if( ( ps[top] - ps[top-1] ) * ( p - ps[top] ) > 0 ) --top;
            else break;
        }
        if( top == 1 && p.x == ps[top].x && p.y > ps[top].y ) --top;
        if( !top || p.x != ps[top].x ) ps[++top] = p;
    }
    inline lli query(const Point &p) {
        int l = 1 , r = top , lmid , rmid;
        while( r > l + 2 ) {
            lmid = ( l + l + r ) / 3 , rmid = ( l + r + r ) / 3;
            if( ( p ^ ps[lmid] ) < ( p ^ ps[rmid] ) ) l = lmid;
            else r = rmid;
        }
        lli ret = 0;
        for(int i=l;i<=r;i++) ret = max( ret , p ^ ps[i] );
        return ret;
    }
    inline void clear() {
        top = 0;
    }
}con;

lli ina[maxn],inb[maxn],f[maxn],cst[maxn],ans,add; // f[id] .
bool isl[maxn];
int n;
 
int cmp; // 0 compare height , 1 compare id .
struct Node {
    lli hei,id;
    friend bool operator < (const Node &a,const Node &b) {
        if( cmp ) return a.id != b.id ? a.id < b.id : a.hei < b.hei;
        else return a.hei != b.hei ? a.hei < b.hei : a.id < b.id;
    }
}ns[maxn];
 
vector<Node> vec;
 
inline void solve(vector<Node> &vec) {
    if( vec.size() <= 1 ) {
        if( vec.size() ) f[vec[0].id] = max( f[vec[0].id] , cst[vec[0].id] );
        return;
    }
    vector<Node> vl,vr;
    const unsigned mid = vec.size() >> 1;
    for(unsigned i=0;i<mid;i++) vl.push_back(vec[i]);
    for(unsigned i=mid;i<vec.size();i++) vr.push_back(vec[i]);
    solve(vl);
    for(unsigned i=0;i<vl.size();i++) isl[vl[i].id] = 1;
    for(unsigned i=0;i<vr.size();i++) isl[vr[i].id] = 0;
    cmp = 0 , sort(vec.begin(),vec.end()) , con.clear();
    for(unsigned i=0;i<vec.size();i++) {
        if( isl[vec[i].id] ) {
            con.push((Convex::Point){vec[i].hei,f[vec[i].id]});
        } else {
            f[vec[i].id] = max( f[vec[i].id] , cst[vec[i].id] + con.query((Convex::Point){n-vec[i].id+1,1}));
        }
    }
    solve(vr);
}
 
int main() {
    static lli sel,lst;
    scanf("%d",&n) , add = (lli) n * ( n + 1 ) >> 1;
    for(int i=1;i<=n;i++) scanf("%lld",ina+i) , ina[i] -= i;
    for(int i=1;i<=n;i++) {
        scanf("%lld",inb+i);
        if( ina[i] >= 0 ) {
            cst[i] = mul - inb[i] - ina[i] * ( n - i + 1 ) ,
            vec.push_back((Node){ina[i],i});
        }
    }
    cmp = 1 , sort(vec.begin(),vec.end());
    solve(vec);
    for(int i=1;i<=n;i++) ans = max( ans , f[i] );
    ans -= add;
    sel = ( ans + mul ) / mul;
    lst = mul * sel - ans;
    printf("%lld %lld\n",sel,lst);
    return 0;
}
