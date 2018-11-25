#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<cctype>
typedef long long int lli;
const int maxn=5e5+1e2;

struct Point {
    int x,y;
    friend bool operator < (const Point &a,const Point &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
};

std::map<int,int> siz;
int w[maxn],hsw[maxn],hss[maxn],fix[maxn],bel[maxn];
int lson[maxn],rson[maxn],lazyw[maxn],lazys[maxn],mxw[maxn];
int root[maxn];

typedef std::pair<int,int> pii;
__inline pii mp(const int &x,const int &y) { return std::make_pair(x,y); }

inline void maintain(int pos) {
    mxw[pos] = std::max( std::max(mxw[lson[pos]],mxw[rson[pos]]) , w[pos] );
}
inline void applyw(int pos,const int &ww) {
    if( !pos ) return;
    lazyw[pos] = std::max( lazyw[pos] , ww ) , hsw[pos] = std::max( hsw[pos] , ww );
}
inline void applys(int pos,const int &ss) {
    if( !pos ) return;
    lazys[pos] = std::max( lazys[pos] , ss ) , hss[pos] = std::max( hss[pos] , ss );
}
inline void push(int pos) {
    if( lazyw[pos] ) applyw(lson[pos],lazyw[pos]) , applyw(rson[pos],lazyw[pos]) , lazyw[pos] = 0;
    if( lazys[pos] ) applys(lson[pos],lazys[pos]) , applys(rson[pos],lazys[pos]) , lazys[pos] = 0;
}
inline pii split(int pos,int tar) { // split first tar nodes into left .
    if( !pos ) return mp(0,0);
    push(pos);
    if( tar < pos ) { // split left .
        pii spl = split(lson[pos],tar);
        lson[pos] = spl.second , maintain(pos);
        return mp(spl.first,pos);
    } else {
        pii spr = split(rson[pos],tar);
        rson[pos] = spr.first , maintain(pos);
        return mp(pos,spr.second);
    }
}
inline int merge(int x,int y) {
    if( x == y || !x || !y ) return x | y;
    push(x) , push(y);
    if( x > y ) std::swap(x,y);
    if( fix[x] < fix[y] ) { // x will be the father .
        rson[x] = merge(rson[x],y) , maintain(x);
        return x;
    } else {
        lson[y] = merge(x,lson[y]) , maintain(y);
        return y;
    }
}

inline void remove(int x) { // split x from it's tree into a single node .
    pii spr = split(root[bel[x]],x) , spl = split(spr.first,x-1);
    root[bel[x]] = merge(spl.first,spr.second) , --siz[bel[x]];
}
inline void insert(int x,int id) { // insert x into root[id] .
    applyw(root[id],w[x]) , applyw(x,mxw[root[id]]);
    pii sp = split(root[id],x);
    root[id] = merge(merge(sp.first,x),sp.second) , applys(root[id],siz[id]++);
}

inline int getpos(const Point &p) {
    static std::map<Point,int> cov;
    static int cnt = 0;
    if( cov.find(p) == cov.end() ) return cov[p] = ++cnt;
    else return cov[p];
}

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st=buf+BS,*ed=st;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , fix = 1 , ch;
    while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret * fix;
}

int main() {
    static int n,t;
    n = getint();
    for(int i=1,x,y;i<=n;i++) mxw[i] = w[i] = getint() , x = getint() , y = getint() , insert(i,bel[i]=getpos((Point){x,y})) , fix[i] = i;
    t = getint() , std::random_shuffle(fix+1,fix+1+n);
    for(int i=1,p,x,y;i<=t;i++) p = getint() , x = getint() , y = getint() , remove(p) , insert(p,bel[p]=getpos((Point){x,y}));
    for(int i=1;i<=n;i++) remove(i);
    for(int i=1;i<=n;i++) printf("%lld\n",(lli)hss[i]*hsw[i]);
    return 0;
}
