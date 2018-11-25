#pragma GCC optimize("Ofast","no-stack-protector")
#pragma GCC target("avx")
#include<cstdio>
#include<algorithm>
#include<cctype>
typedef long long int lli;
const int maxn=3e5+1e2;

struct Node {
    lli cst,tim;
    friend Node operator + (const Node &a,const Node &b) { return (Node){a.cst+b.cst,a.tim+b.tim}; }
    friend Node operator - (const Node &a,const Node &b) { return (Node){a.cst-b.cst,a.tim-b.tim}; }
    friend bool operator < (const Node &a,const Node &b) { return a.cst != b.cst ? a.cst < b.cst : a.tim < b.tim; }
}f[maxn][2],per;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
int n,k,c;
lli su;

__inline void coredge(int from,int to,int len) {
    static int cnt;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
__inline void addedge(int a,int b,int l) {
    coredge(a,b,l) , coredge(b,a,l);
}

__inline void dfs(int pos,int fa) {
    f[pos][0] = (Node){0,0} , f[pos][1] = per;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
        dfs(t[at],pos);
        const Node w = (Node){l[at],0};
        const Node tp0 = std::min( f[pos][1] + f[t[at]][1] - per , f[pos][0] + f[t[at]][0] + w );
        const Node tp1 = std::min( f[pos][1] + f[t[at]][0] + w , f[pos][0] + f[t[at]][1] );
        f[pos][0] = std::min( tp0 , tp1 ) , f[pos][1] = std::min( tp0 + per , tp1 );
    }
}
__inline Node calc(lli cst) {
    per = (Node){cst,1} , dfs(1,-1);
    return f[1][0];
}
__inline lli bin() {
    Node now;
    if( (now = calc(c)).tim <= k ) return su + now.cst;
    lli l = 0 , r = 1e12 , mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( calc(mid).tim <= k ) r = mid;
        else l = mid;
    }
    now = calc(r);
    return su + now.cst - k * ( r - c );
}

__inline char nextchar() {
    static const int BS = 1 <<21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
__inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    freopen("ext.in","r",stdin);
    freopen("ext.out","w",stdout);
    n = getint() , k = getint() , c = getint();
    for(int i=1,a,b,l;i<n;i++) a = getint() , b = getint() , su += ( l = getint() ) , addedge(a,b,l);
    printf("%lld\n",bin());
    fclose(stdout);
    return 0;
}
