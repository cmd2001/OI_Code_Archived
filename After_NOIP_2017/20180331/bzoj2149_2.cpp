#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>
#include<cmath>
#include<vector>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;
const lli mul = 1e13+1e10;

namespace Convex {
    int cmp; // 0 compare x , 1 compare slope .
    struct Point {
        lli x,y;
        long double slop;
        friend bool operator < (const Point &a,const Point &b) {
            if( !cmp ) return a.x != b.x ? a.x < b.x : a.y < b.y;
            return a.slop > b.slop;
        }
        friend Point operator - (const Point &a,const Point &b) {
            return (Point){a.x-b.x,a.y-b.y};
        }
        friend long double operator * (const Point &a,const Point &b) {
            return (long double)a.x * b.y - (long double)b.x * a.y;
        }
        inline lli calc(lli a,lli b) const {
            return a * x + b * y;
        }
    };
    set<Point> st;
    
    inline void Pop_right(set<Point>::iterator nxt,const Point &p) {
        set<Point>::iterator lst;
        while(1) {
            nxt = st.lower_bound(p);
            lst = nxt , ++nxt;
            if( nxt == st.end() ) return;
            if( lst->x == p.x ) {
                if( p.y > lst->y ) st.erase(lst);
                else break;
            }
            else {
                if( (*lst-p) * (*nxt-*lst) < 0 ) return;
                st.erase(lst);
            }
        }
    }
    inline void Pop_left(set<Point>::iterator prv,const Point &p) {
        set<Point>::iterator lst;
        prv = st.lower_bound(p) , --prv;
        if( prv == st.begin() && prv->x == p.x ) return void(st.erase(prv));
        while(prv!=st.begin()) {
            prv = st.lower_bound(p) , --prv;
            lst = prv , --prv;
            if( p.x == lst->x ) {
                if( p.y > lst->y ) st.erase(lst);
                else break;
                continue;
            }
            else {
                if( (*lst-*prv) * (p-*lst) < 0 ) break;
                st.erase(lst);
            }
        }
    }
    inline bool fail(const Point &p) {
        set<Point>::iterator it = st.lower_bound((Point){p.x,0,0});
        if( it != st.end() && it->x == p.x ) {
            if( it->y >= p.y ) return 1; // p is useless at all .
            else return 0; // p must be on convex .
        }
        if( it != st.end() && it != st.begin() ) {
            set<Point>::iterator prv = it; --prv;
            if( ( p - *prv ) * (*it - p ) > 0  ) return 1;
        }
        return 0;
    }
    inline void insert(const Point &p) {
        cmp = 0;
        if( fail(p) ) return;
        set<Point>::iterator prv,nxt,lst=st.lower_bound(p);
        if(lst!=st.begin()) Pop_left(--lst,p);
        lst=st.lower_bound(p);
        if(lst!=st.end()) Pop_right(lst,p);
        st.insert(p) , lst = st.find(p);
        if(lst!=st.begin()) {
            prv = lst , --prv;
            Point x = *prv;
            x.slop = (long double)( p.y - x.y ) / ( p.x - x.x );
            st.erase(prv) , st.insert(x);
        }
        nxt = lst = st.find(p) , ++nxt;
        if(nxt!=st.end()) {
            Point x = p , n = *nxt;
            x.slop = (long double)( n.y - x.y ) / ( n.x - x.x );
            st.erase(lst) , st.insert(x);
        } else {
            Point x = p;
            x.slop = -1e18;
            st.erase(lst) , st.insert(x);
        }
    }
    inline lli query(const lli &k) {
        cmp = 1;
        set<Point>::iterator it = st.lower_bound((Point){0,0,(long double)-k}); // it can't be st.end() if st isn't empty .
        if( it==st.end() ) return 0;
        lli ret = it->calc(k,1);
        if( it != st.begin() ) {
            --it;
            ret = max( ret , it->calc(k,1) );
        }
        ++it; if( ++it!=st.end() ) ret = max( ret , it->calc(k,1) );
        return ret;
    }
    inline void clear() {
        st.clear() , cmp = 0;
    }
}

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
    cmp = 1 , sort(vec.begin(),vec.end()) , Convex::clear();
    for(unsigned i=0;i<vec.size();i++) {
        if( isl[vec[i].id] ) {
            Convex::insert((Convex::Point){vec[i].hei,f[vec[i].id],0});
        } else {
            f[vec[i].id] = max( f[vec[i].id] , cst[vec[i].id] + Convex::query(n-vec[i].id+1));
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
    cmp = 0 , sort(vec.begin(),vec.end());
    solve(vec);
    for(int i=1;i<=n;i++) ans = max( ans , f[i] );
    ans -= add;
    sel = ( ans + mul ) / mul;
    lst = mul * sel - ans;
    printf("%lld %lld\n",sel,lst);
    return 0;
}