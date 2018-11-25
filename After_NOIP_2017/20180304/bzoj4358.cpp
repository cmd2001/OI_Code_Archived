#pragma GCC optimize(3)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cctype>
const int maxn=5e4+1e2,maxb=230;

int in[maxn],bel[maxn],mil[maxn],mxr[maxn],anss[maxn],ed[maxn];
int n,ans,l,r,top;
struct Node {
    int l,r,id;
    friend bool operator < (const Node &a,const Node &b) {
        return bel[a.l] != bel[b.l] ? bel[a.l] < bel[b.l] : a.r < b.r;
    }
}ns[maxn];
struct StkNode {
    int *dst,ov;
    StkNode() {}
    StkNode(int &x) { dst = &x , ov = x; }
    inline void res() { *dst = ov; }
}stk[maxn<<2];

inline void move_without_mem(int nw) {
    const int i = in[nw];
    mxr[i] = mxr[i+1] + 1 , mil[i] = mil[i-1] + 1 ;
    const int p = mil[i] + mxr[i] - 1;
    ans = std::max( ans , p );
    mxr[i-mil[i]+1] = p , mil[i+mxr[i]-1] = p;
}
inline void move_with_mem(int nw) {
    const int i = in[nw];
    stk[++top] = StkNode(mxr[i]) , stk[++top] = StkNode(mil[i]);
    mxr[i] = mxr[i+1] + 1 , mil[i] = mil[i-1] + 1 ;
    const int p = mil[i] + mxr[i] - 1;
    stk[++top] = StkNode(ans) , ans = std::max( ans , p );
    stk[++top] = StkNode(mxr[i-mil[i]+1]) , stk[++top] = StkNode(mil[i+mxr[i]-1]);
    mxr[i-mil[i]+1] = p , mil[i+mxr[i]-1] = p;
}
inline void reset() {
    while(top)
        stk[top--].res();
}
inline int force(int l,int r) { // assert inited .
    for(int i=l;i<=r;i++) move_with_mem(i);
    int ret = ans;
    reset();
    return ret;
}

inline void init() {
    memset(mil,0,sizeof(int)*(n+2)) , memset(mxr,0,sizeof(int)*(n+2)) , ans = 0;
}
inline void initblk() {
    const int bs = sqrt(n);
    int cnt = 0;
    for(int l=1,r;l<=n;l=r+1) {
        r = std::min( l + bs - 1 , n ) , ed[++cnt] = r;
        for(int k=l;k<=r;k++) bel[k] = cnt;
    }
}

inline char nextchar() {
    static char buf[1<<18],*st=buf+(1<<18),*ed=buf+(1<<18);
    if( st == ed ) ed = buf + fread(st=buf,1,1<<18,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}
int main() {
    static int m;
    n = getint() , m = getint() , initblk();
    for(int i=1;i<=n;i++) in[i] = getint();
    for(int i=1;i<=m;i++) ns[i].l = getint() , ns[i].r = getint() , ns[i].id = i;
    std::sort(ns+1,ns+1+m);
    for(int i=1;i<=m;i++) {
        if( bel[ns[i].l] == bel[ns[i].r] ) anss[ns[i].id] = force(ns[i].l,ns[i].r);
    }
    for(int i=1;i<=m;i++) {
        if( bel[ns[i].l] != bel[ns[i-1].l] ) {
            init(); const int p = in[l=r=ed[bel[ns[i].l]]];
            mxr[p] = mil[p] = 1;
        }
        if( bel[ns[i].l] == bel[ns[i].r] ) continue;
        while( r < ns[i].r ) move_without_mem(++r);
        while( ns[i].l < l ) move_with_mem(--l);
        anss[ns[i].id] = ans;
        reset() , l = ed[bel[ns[i].l]];
    }
    for(int i=1;i<=m;i++) printf("%d\n",anss[i]);
    return 0;
}

