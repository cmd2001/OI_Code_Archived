#include<cstdio>
#include<algorithm>
#include<set>
#include<cmath>
using namespace std;
const int maxn=1e5+1e2;

int cmp; // 0 compare x , 1 compare slope .
struct Point {
    double x,y,slop;
    friend bool operator < (const Point &a,const Point &b) {
        if( !cmp ) return a.x != b.x ? a.x < b.x : a.y < b.y;
        return a.slop > b.slop;
    }
    friend Point operator - (const Point &a,const Point &b) {
        return (Point){a.x-b.x,a.y-b.y};
    }
    friend double operator * (const Point &a,const Point &b) {
        return a.x * b.y - b.x * a.y;
    }
    inline double calc(double a,double b) const {
        return a * x + b * y;
    }
};
set<Point> st;
double a[maxn],b[maxn],rate[maxn],f[maxn],ans;

inline void Pop_right(set<Point>::iterator nxt,const Point &p) {
    set<Point>::iterator lst;
    while(1) {
        lst = nxt , ++nxt;
        if( nxt == st.end() ) return;
        if( (*lst-p) * (*nxt-*lst) <= 0 ) return;
        st.erase(lst);
    }
}
inline void Pop_left(set<Point>::iterator prv,const Point &p) {
    set<Point>::iterator lst;
    while(prv!=st.begin()) {
        lst = prv , --prv;
        if( (*lst-*prv) * (p-*lst) <= 0 ) break;
        st.erase(lst);
    }
}
inline void insert(const Point &p) {
    cmp = 0;
    set<Point>::iterator prv,nxt,lst=st.lower_bound(p);
    if(lst!=st.begin()) Pop_left(--lst,p);
    lst=st.lower_bound(p);
    if(lst!=st.end()) Pop_right(lst,p);
    st.insert(p) , lst = st.find(p);
    if(lst!=st.begin()) {
        prv = lst , --prv;
        Point x = *prv;
        x.slop = ( p.y - x.y ) / ( p.x - x.x );
        st.erase(prv) , st.insert(x);
    }
    nxt = lst , ++nxt;
    if(nxt!=st.end()) {
        Point x = p , n = *nxt;
        x.slop = ( n.y - x.y ) / ( n.x - x.x );
        st.erase(lst) , st.insert(x);
    } else {
        Point x = p;
        x.slop = -1e18;
        st.erase(lst) , st.insert(x);
    }
}
inline double query(const int id) {
    cmp = 1;
    const double k = -a[id] / b[id];
    set<Point>::iterator it = st.lower_bound((Point){0,0,k}); // it can't be st.end() if st isn't empty .
    if( it==st.end() ) return 0;
    double ret = it->calc(a[id],b[id]);
    if( it != st.begin() ) {
        --it;
        ret = max( ret , it->calc(a[id],b[id]) );
    }
    return ret;
}

int main() {
    static int n;
    scanf("%d%lf",&n,&ans);
    for(int i=1;i<=n;i++) scanf("%lf%lf%lf",a+i,b+i,rate+i);
    for(int i=1;i<=n;i++) {
        ans = max( ans , query(i) );
        f[i] = ans * rate[i] / ( a[i] * rate[i] + b[i] );
        insert((Point){f[i],f[i]/rate[i],0});
    }
    printf("%0.3lf\n",ans);
    return 0;
}

