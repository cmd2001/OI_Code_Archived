#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
const int maxn=2e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
lli l[maxn<<1],p[maxn],q[maxn],lim[maxn];

namespace Slop {
    struct Point {
        lli x,y;
        friend long double operator * (const Point &x,const Point &y) {
            return (long double)x.x*y.x + (long double)x.y*y.y;
        }
        friend lli operator ^ (const Point &x,const Point &y) {
            return x.x * y.x + x.y * y.y;
        }
    }stk[maxn];
    int top;
    inline double slop(const Point &l,const Point &r) {
        return ( r.y - l.y ) / ( r.x - l.x );
    }
    inline lli tri(const Point &p) {
        if( !top ) return inf;
        int l = 1 , r = top , lmid , rmid;
        while( r > l + 2 ) {
            lmid = ( l + l + r ) / 3 , rmid = ( l + r + r ) / 3;
            if( stk[lmid] * p > stk[rmid] * p ) l = lmid;
            else r = rmid;
        }
        lli ret = inf;
        for(int i=l;i<=r;i++) ret = std::min( ret , stk[i] ^ p );
        return ret;
    }
    inline void push(const Point &x) {
        while( top > 1 && slop(stk[top-1],stk[top]) > slop(stk[top],x) ) {
            --top;
        }
        stk[++top] = x; 
    }
    inline void reset() {
        top = 0;
    }
}

lli dep[maxn],f[maxn];
int fa[maxn],ban[maxn];
int siz[maxn],cal[maxn],blksiz[maxn];
int pts[maxn],cnt;

inline void addedge(int from,int to,lli len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    for(int at=s[pos];at;at=nxt[at]) {
        fa[t[at]] = pos , dep[t[at]] = dep[pos] + l[at];
        pre(t[at]);
    }
}

inline void getrt(int pos,const int &fs,int &rt) {
    siz[pos] = 1 , cal[pos] = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( !ban[t[at]] ) {
            getrt(t[at],fs,rt) , siz[pos] += siz[t[at]];
            cal[pos] = std::max( cal[pos] , siz[t[at]] );
        }
    cal[pos] = std::max( cal[pos] , fs - siz[pos] );
    if( cal[pos] <= cal[rt] ) rt = pos;
}
inline void getpts(int pos) {
    pts[++cnt] = pos;
    for(int at=s[pos];at;at=nxt[at]) if( !ban[t[at]] ) getpts(t[at]);
}
inline bool cmp(const int &x,const int &y) {
    return dep[x] - lim[x] > dep[y] - lim[y];
}
inline void solve(int pos,int bs) {
    if( bs == 1 ) return;
    
    int rt = 0 , tfa = 0;
    getrt(pos,bs,rt) , tfa = fa[rt];
    for(int at=s[rt];at;at=nxt[at]) ban[t[at]] = 1;
    solve(pos,bs-siz[rt]+1);
    cnt = 0 , Slop::reset();
    for(int at=s[rt];at;at=nxt[at])
        getpts(t[at]);
    std::sort(pts+1,pts+1+cnt,cmp);
    for(int i=1,tp=rt;i<=cnt;i++) {
        const int now = pts[i];
        while( tp != fa[pos] && dep[tp] >= dep[now] - lim[now] ) {
            Slop::push((Slop::Point){-dep[tp],f[tp]});
            tp = fa[tp];
        }
        f[now] = std::min( f[now] , q[now] + p[now] * dep[now] + Slop::tri((Slop::Point){p[now],1}) );
    }
    ban[rt] = 1;
    for(int at=s[rt];at;at=nxt[at]) if( t[at] != tfa ) ban[t[at]] = 0;
    for(int at=s[rt];at;at=nxt[at])
        if( !ban[t[at]] && t[at] != tfa )
            solve(t[at],siz[t[at]]);
}

int main() {
    static int n;
    static lli lv;
    scanf("%d%*d",&n);
    for(int i=2,fa;i<=n;i++) {
        scanf("%d%lld%lld%lld%lld",&fa,&lv,p+i,q+i,lim+i);
        addedge(fa,i,lv);
    }
    memset(f,0x3f,sizeof(f)) , f[1] = 0 , *cal = inf;
    pre(1);
    solve(1,n);
    for(int i=2;i<=n;i++) printf("%lld\n",f[i]);
    return 0;
}
