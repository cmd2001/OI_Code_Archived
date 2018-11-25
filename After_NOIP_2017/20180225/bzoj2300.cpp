#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxq=2e5+1e2;

struct Point {
    double x,y;
    friend bool operator < (const Point &a,const Point &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
    friend Point operator - (const Point &a,const Point &b) {
        return (Point){a.x-b.x,a.y-b.y};
    }
    friend double operator * (const Point &a,const Point &b) {
        return a.x * b.y - a.y * b.x;
    }
    inline double dis() {
        return sqrt( x * x + y * y );
    }
}ps[maxn];
inline double dis(const Point &a,const Point &b) {
    return ( a - b ) . dis();
}

int tpe[maxq],arg[maxq],vis[maxn];
set<Point> st;
double ans,aa[maxq];

inline void insert(const Point &p) {
    set<Point>::iterator prv,lst,nxt=st.lower_bound(p);
    prv = nxt , --prv;
    if( ( p - *prv ) * ( *nxt - p ) > 0 ) return;
    ans -= dis(*prv,*nxt);
    while( 1 ) { // nxt can't be st.end() .
        lst = nxt , ++nxt;
        if( nxt == st.end() ) break;
        if( ( *lst - p ) * ( *nxt - *lst ) <= 0 ) break;
        ans -= dis(*lst,*nxt)  , st.erase(lst);
    }
    while( prv != st.begin() ) {
        lst = prv , --prv;
        if( ( *lst - *prv ) * ( p - *lst ) <= 0 ) break;
        ans -= dis(*lst,*prv) , st.erase(lst);
    }
    st.insert(p);
    lst = st.find(p) , prv = lst , --prv , nxt = lst , ++nxt;
    ans += dis(*prv,p) + dis(*nxt,p);
}

int main() {
    static int n,q;
    static double l,x,y;
    scanf("%lf%lf%lf",&l,&x,&y);
    st.insert((Point){0,0}) , st.insert((Point){l,0}) , ans = l;
    insert((Point){x,y});
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lf%lf",&ps[i].x,&ps[i].y);
    scanf("%d",&q);
    for(int i=1;i<=q;i++) {
        scanf("%d",tpe+i);
        if( tpe[i] == 1 ) scanf("%d",arg+i) , vis[arg[i]] = 1;
    }
    for(int i=1;i<=n;i++) if( !vis[i] ) insert(ps[i]);
    for(int i=q;i;i--)
        if( tpe[i] == 1 ) insert(ps[arg[i]]);
        else aa[i] = ans;
    for(int i=1;i<=q;i++) if( tpe[i] == 2 ) printf("%0.2lf\n",aa[i]);
    return 0;
}

