#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
const int maxn=1e2+1e1,inf=0x3f3f3f3f;
const double eps = 1e-8;

struct Point {
    int x,y;
    friend bool operator < (const Point &a,const Point &b) {
        return a.x < b.x;
    }
}ps[maxn];

int f[maxn],n,R;

inline void calccrs(const Point &p,double &l,double &r) {
    double dis = std::sqrt( R * R - p.y * p.y + eps );
    l = p.x - dis , r = p.x + dis;
}
inline bool can(int st,int ed) {
    double mil = -inf , mxr = inf , l , r;
    for(int i=st;i<=ed;i++) calccrs(ps[i],l,r) , mil = std::max( mil , l ) , mxr = std::min( mxr , r );
    return mxr + eps >= mil;
}
inline void getans() {
    memset(f,0x3f,sizeof(f)) , f[0] = 0 , std::sort(ps+1,ps+1+n);
    for(int i=1;i<=n;i++) for(int j=0;j<i;j++) if( can(j+1,i) ) f[i] = std::min( f[i] , f[j] + 1 );
}

int main() {
    scanf("%d%d",&n,&R);
    for(int i=1;i<=n;i++) scanf("%d%d",&ps[i].x,&ps[i].y);
    getans() , printf("%d\n",f[n]);
    return 0;
}
