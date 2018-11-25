#include<cstdio>
#include<algorithm>
#include<cctype>
typedef long long int lli;
typedef long double ldb;
using namespace std;
const int maxn=1e5+1e2;

lli f[maxn],c;
struct Machine {
    lli d,p,g,su;
    friend bool operator < (const Machine &a,const Machine &b) {
        return a.g < b.g;
    }
}in[maxn];
struct Point {
    lli x,y;
    friend lli operator * (const Point &a,const Point &b) {
        return a.x * b.x + a.y * b.y;
    }
    friend ldb operator / (const Point &a,const Point &b) {
        return (ldb) (a.y-b.y) / (a.x-b.x);
    }
}stk[maxn];

int top;

inline void push(const Point &p) {
    if( top && stk[top].x == p.x ) {
        if( stk[top].y >= p.y ) return;
        else --top;
    }
    while( top > 1 && p / stk[top] >= stk[top] / stk[top-1] ) --top;
    stk[++top] = p;
}
inline lli query(lli d) {
    int l = 1 , r = top , lmid , rmid;
    const Point p = (Point){d,1};
    lli ret = 0;
    for(int i=l;i<=r;i++) ret = max( ret , stk[i] * p );
    return ret;
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    static int T,n,d;
    while( scanf("%d%lld%d",&n,&c,&d) == 3 && n ) {
        for(int i=1;i<=n;i++) in[i].d = getint() , in[i].p = getint() , in[i].su = getint() - in[i].p , in[i].g = getint();
        sort(in+1,in+1+n) , in[++n] = (Machine){d+1,0,0,0} , top = 0;
        for(int i=1;i<=n;i++) {
            f[i] = max( c , query(in[i].d) );
            if( f[i] >= in[i].p ) {
                push((Point){in[i].g,f[i]+in[i].su-in[i].g*in[i].d-in[i].g});
            }
        }
        printf("Case %d: %lld\n",++T,f[n]);
    }
    return 0;
}
//^[0-9]* [0-9]* [0-9]*$
