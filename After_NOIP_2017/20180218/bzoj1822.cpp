#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
const int maxn=2e2+1e1,maxm=maxn*maxn;

int per[maxn],r[maxn];
bool can[maxn][maxn];
int n,m,k;

namespace Geometry {
    const double eps = 1e-8;
    inline int dcmp(const double &x) {
        if( fabs(x) <= eps ) return 0;
        return x < 0 ? -1 : 1;
    }
    struct Point {
        int x,y;
    }ps[maxn],ts[maxn];
    struct Circle {
        Point o;
        int r;
    }cs[maxn];
    struct Line {
        double a,b,c;
    };
    inline Line CalcLine(const Point &a,const Point &b) {
        if( a.x == b.x ) return (Line){1.0,0.0,(double)-a.x};
        if( a.y == b.y ) return (Line){0.0,1.0,(double)-a.y};
        const double dy = b.y - a.y , dx = b.x - a.x;
        const double k = dy / dx  , t = a.y - k * a.x;
        return (Line){k,-1.0,t};
    }
    inline double CalcDis(const Point &p,const Line &l) {
        const double u = p.x * l.a + p.y * l.b + l.c;
        const double d = l.a * l.a + l.b * l.b;
        return fabs(u) / ( sqrt(d) );
    }
    inline double CalcDis(const Point &a,const Point &b) {
        const int dx = a.x - b.x , dy = a.y - b.y;
        return sqrt( dx * dx + dy * dy );
    }
    inline bool Cross(const Line &l,const Point &a,const Point &b,const Circle &c) {
        double t;
        if( dcmp( ( t = CalcDis(c.o,l) ) - c.r ) > 0 ) return 0;
        double disa = CalcDis(a,c.o) , disb = CalcDis(b,c.o) , disf = CalcDis(a,b);
        disa = sqrt( disa * disa - t * t ) , disb = sqrt( disb * disb - t * t );
        return !dcmp( disa + disb - disf );
    }
    inline bool Inside(const Point &p,const Circle &c) {
        return dcmp( CalcDis(p,c.o) - c.r ) <= 0;
    }
    inline bool CalcCan(const Point &p,const Point &t,const int id) {
        if( dcmp( CalcDis(p,t) - r[id] ) >= 0 ) return 0;
        const Line l = CalcLine(p,t);
        for(int i=1;i<=k;i++) {
            if( Inside(p,cs[i]) || Inside(t,cs[i]) || Cross(l,p,t,cs[i]) ) return 0;
        }
        return 1;
    }
    inline void gen() {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                can[i][j] = CalcCan(ps[i],ts[j],i);
    }
}

namespace Flow {
    const int inf=0x3f3f3f3f;
    int s[maxn<<1],t[maxm<<1],nxt[maxm<<1],f[maxm<<1],dep[maxn<<1],cnt,st,ed;
    
    inline void coredge(int from,int to,int flow) {
        t[++cnt] = to , f[cnt] = flow ,
        nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow) {
        coredge(from,to,flow) , coredge(to,from,0);
    }
    inline bool bfs() {
        memset(dep,-1,sizeof(dep)) , dep[st] = 0;
        queue<int> q; q.push(st);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int at=s[pos];at;at=nxt[at])
                if( f[at] && !~dep[t[at]] )
                    dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
        }
        return ~dep[ed];
    }
    inline int dfs(int pos,int flow) {
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dep[t[at]] > dep[pos] ) {
                now = dfs(t[at],min(flow,f[at]));
                ret += now , flow -= now ,
                f[at] -= now , f[at^1] += now;
                if( !flow ) return ret;
            }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline int dinic() {
        int ret = 0 , now = 0;
        while( bfs() ) {
            while( ( now = dfs(st,inf) ) ) ret += now;
        }
        return ret;
    }
    inline void rebuild(int lim) {
        memset(s,0,sizeof(s)) , cnt = 1;
        st = n + m + 1 , ed = st + 1;
        for(int i=1;i<=n;i++) singledge(st,i,lim/per[i]+1);
        for(int i=1;i<=m;i++) singledge(i+n,ed,1);
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(can[i][j]) singledge(i,j+n,1);
    }
    inline bool judge(int lim) {
        rebuild(lim);
        return dinic() == m;
    }
}

inline int bin() {
    int ll = 0 , rr = 4000100 , mid;
    if( Flow::judge(ll) ) return ll;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( Flow::judge(mid) ) rr = mid;
        else ll = mid;
    }
    return rr != 4000100 ? rr : -1;
}

int main() {
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) {
        using Geometry::ps;
        scanf("%d%d%d%d",&ps[i].x,&ps[i].y,r+i,per+i);
    }
    for(int i=1;i<=m;i++) {
        using Geometry::ts;
        scanf("%d%d",&ts[i].x,&ts[i].y);
    }
    for(int i=1;i<=k;i++) {
        using Geometry::cs;
        scanf("%d%d%d",&cs[i].o.x,&cs[i].o.y,&cs[i].r);
    }
    Geometry::gen();
    printf("%d\n",bin());
    return 0;
}
