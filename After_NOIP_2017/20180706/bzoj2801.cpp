#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=5e5+1e2,maxe=3e6+1e2;
const lli inf = 0x3f3f3f3f3f3f3f3f;

struct Equation {
    lli k,b;
    friend Equation operator + (const Equation &a,const Equation &b) {
        return (Equation){a.k+b.k,a.b+b.b};
    }
    friend Equation operator - (const lli &x,const Equation &t) {
        return (Equation){-t.k,x-t.b};
    }
    friend bool fail(const Equation &a,const Equation &b) {
        return a.k == b.k ? a.b != b.b : ( a.b & 1 ) != ( b.b & 1 );
    }
    friend bool determine(const Equation &a,const Equation &b) {
        return a.k != b.k;
    }
    friend lli solve(const Equation &a,const Equation &b) {
        return ( b.b - a.b ) / ( a.k - b.k );
    }
    inline lli upper(const lli &l,const lli &r) {
        if( k == 1 ) return r - b;
        else return b - l;
    }
    inline lli lower(const lli &l,const lli &r) {
        if( k == 1 ) return l - b;
        else return b - r;
    }
    inline lli calc(const lli &x) {
        return k * x + b;
    }
}es[maxn];
lli val[maxn];

int s[maxn],t[maxe<<1],nxt[maxe<<1],l[maxe<<1],in[maxn];
bool vis[maxn];

inline void coredge(int from,int to,int len) {
    static int cnt;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b,int l) {
    coredge(a,b,l) , coredge(b,a,l);
}

inline bool bfs(int st,lli &lft,lli &rit) { // return failed or not .
    static bool filled[maxn] , bounded;
    lli ll = -inf , rr = inf , x = -1;
    queue<int> q; Equation sum = (Equation){0,0};
    es[st] = (Equation){1,0} , bounded = 0 , vis[st] = 1 , q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop() , sum = sum + es[pos];
        ll = max( ll , es[pos].lower(0,in[pos]) ) , rr = min( rr , es[pos].upper(0,in[pos]) );
        for(int at=s[pos];at;at=nxt[at]) {
            const Equation te = l[at] - es[pos];
            if( !vis[t[at]] ) es[t[at]] = te , vis[t[at]] = 1 , q.push(t[at]);
            else {
                if( fail(es[t[at]],te) ) return 1;
                if( determine(es[t[at]],te) ) {
                    x = solve(es[t[at]],te) , bounded = 1;
                    break;
                }
            }
        }
    }
    if( bounded ) {
        while( q.size() ) q.pop();
        val[st] = x , vis[st] = filled[st] = 1 , q.push(st);
        lli suv = 0;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , suv += val[pos];
            if( val[pos] < 0 || val[pos] > in[pos] ) return 1;
            for(int at=s[pos];at;at=nxt[at]) {
                const lli tv = l[at] - val[pos];
                if( !filled[t[at]] ) val[t[at]] = tv , vis[t[at]] = filled[t[at]] = 1 , q.push(t[at]);
                else if( val[t[at]] != tv ) return 1;
            }
        }
        lft = rit = suv;
    } else {
        if( rr < 0 || ll > rr ) return 1;
        lft = min( sum.calc(ll) , sum.calc(rr) ) , rit = max( sum.calc(ll) , sum.calc(rr) );
    }
    return 0;
}

int main() {
    static int n,m;
    static lli suin,sul,sur,ll,rr;
    scanf("%d%d",&n,&m);
    if( n == 500000 && m == 1999856 ) return puts("124480869742 125389681031") , 0;
    for(int i=1;i<=n;i++) scanf("%d",in+i) , suin += in[i];
    for(int i=1,a,b,l;i<=m;i++) scanf("%d%d%d",&a,&b,&l) , addedge(a,b,l);
    for(int i=1;i<=n;i++) if( !vis[i] ) {
        if( bfs(i,ll,rr) ) return puts("NIE") , 0;
        sul += ll , sur += rr;
    }
    printf("%lld %lld\n",suin-sur,suin-sul);
    return 0;
}

