#include<cstdio>
#include<algorithm>
#include<set>
typedef long long int lli;
const int maxn=4e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

struct Point {
    lli x,y,v;
    friend bool operator < (const Point &a,const Point &b) {
        if( a.y != b.y ) return a.y < b.y;
        return a.x < b.x;
    }
};
std::multiset<Point> st;

struct Node {
    lli x,y,v;
    int tpe;
    friend bool operator < (const Node &a,const Node &b) {
        return a.x != b.x ? a.x < b.x : a.tpe > b.tpe;
    }
}ns[maxn];

int main() {
    static int n,m,cnt;
    static lli w,h,su;
    scanf("%d%d%lld%lld",&n,&m,&w,&h);
    for(int i=1,x,y,v;i<=n;i++) scanf("%d%d%d",&x,&y,&v) , su += v , ns[++cnt] = (Node){x*h-y*w,x*h+y*w,v,0};
    for(int i=1,x,y,v;i<=m;i++) scanf("%d%d%d",&x,&y,&v) , ns[++cnt] = (Node){x*h-y*w,x*h+y*w,v,1};
    std::sort(ns+1,ns+1+cnt);
    for(int i=cnt;i;i--) {
        if( ! ns[i].tpe ) st.insert((Point){ns[i].x,ns[i].y,ns[i].v});
        else {
            Point tmp = (Point){inf,ns[i].y};
            while( ns[i].v && st.size() ) {
                std::multiset<Point>::iterator it = st.upper_bound(tmp);
                if( it == st.begin() ) break;
                --it;
                Point p = *it; st.erase(it);
                lli sub = std::min( p.v , ns[i].v );
                su -= sub , p.v -= sub , ns[i].v -= sub;
                if( p.v ) st.insert(p);
            }
        }
    }
    printf("%lld\n",su);
    return 0;
}

