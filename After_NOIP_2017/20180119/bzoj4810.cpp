#include<cstdio>
#include<algorithm>
#include<bitset>
#include<cctype>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,lim=1e5;

int in[maxn],cnt[maxn],bel[maxn],ans[maxn];
bitset<maxn> val,rev;
int n,m,l,r;

struct QNode {
    int l,r,ope,x,id;
    friend bool operator < (const QNode &a,const QNode &b) {
        return bel[a.l] != bel[b.l] ? bel[a.l] < bel[b.l] : a.r < b.r;
    }
}ns[maxn];

inline void move(int x,int delta) {
    if( !cnt[x] && cnt[x]+delta ) val[x] = rev[lim-x] = 1;
    if( cnt[x] && !(cnt[x]+delta) ) val[x] = rev[lim-x] = 0;
    cnt[x] += delta;
}

inline bool calc(int ope,int x) {
    if( ope == 2 ) {
        return ( ( val << ( lim - x ) ) & rev ).count();
    } else if( ope == 1 ) {
        return ( ( val << x ) & val ).count();
    } else if( ope == 3 ) {
        int sq = sqrt(x);
        for(int i=1;i<=sq;i++)
            if( ! ( x % i ) )
                if( val[i] && val[x/i] ) return 1;
        return 0;
    }
    return 0;
}
inline void getans(int tarl,int tarr,int ope,int x,int id) {
    while( l < tarl ) move(in[l++],-1);
    while( tarl < l ) move(in[--l],1);
    while( tarr < r ) move(in[r--],-1);
    while( r < tarr ) move(in[++r],1);
    ans[id] = calc(ope,x);
}

inline void initblk() {
    int blk = sqrt(n) , cnt=0;
    for(int l=1,r;l<=n;l=r+1) {
        r = min( l + blk - 1 , n ) , ++cnt;
        for(int i=l;i<=r;i++)
            bel[i] = cnt;
    }
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint();
    for(int i=1;i<=n;i++)
        in[i] = getint();
    for(int i=1,ope,l,r,x;i<=n;i++) {
        ope = getint() , l = getint() , r = getint() , x = getint();
        ns[i] = (QNode){l,r,ope,x,i};
    }
    
    initblk();
    sort(ns+1,ns+1+m);
    move(in[l=r=1],1);
    
    for(int i=1;i<=m;i++)
        getans(ns[i].l,ns[i].r,ns[i].ope,ns[i].x,ns[i].id);
    
    for(int i=1;i<=m;i++)
        puts(ans[i]?"yuno":"yumi");
    
    return 0;
}