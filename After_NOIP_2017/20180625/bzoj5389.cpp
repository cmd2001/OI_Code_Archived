#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
const int inf=0x3f3f3f3f;

int in[maxn],g[maxn],f[maxn],ans[maxn];

struct Query {
    int l,r,d,id;
    friend bool operator < (const Query &a,const Query &b) {
        return a.r < b.r;
    }
}qs[maxn];

inline void solveSecond(int x) {
    const int sq = sqrt(x);
    for(int i=1;i<=sq;i++) if( ! ( x % i ) ) f[i] = max( f[i] , g[x/i] ) , f[x/i] = max( f[x/i] , g[i] );
}

inline int getint() {
    int x;
    scanf("%d",&x);
    return x;
}

int main() {
    static int n,m;
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) in[i] = getint();
    for(int i=1,l,r,d;i<=m;i++) l = getint() , r = getint() , d = getint() , qs[i] = (Query){l,r,d,i};

    memset(f,0,sizeof(f)) , memset(g,0,sizeof(g)) , sort(qs+1,qs+1+m);
    for(int i=1,j=1;i<=n;i++) {
        solveSecond(in[i]);
        while( j <= m && qs[j].r == i ) {
            if( f[qs[j].d] >= qs[j].l ) ans[qs[j].id] = 1;
            ++j;
        }
        g[in[i]] = i;
    }


    for(int i=1;i<=n;i++) qs[i].l = n - qs[i].l + 1 , qs[i].r = n - qs[i].r + 1 , swap(qs[i].l,qs[i].r);
    reverse(in+1,in+1+n) , memset(f,0,sizeof(f)) , memset(g,0,sizeof(g)) , sort(qs+1,qs+1+m);
    for(int i=1,j=1;i<=n;i++) {
        solveSecond(in[i]);
        while( j <= m && qs[j].r == i ) {
            if( f[qs[j].d] >= qs[j].l ) ans[qs[j].id] = 1;
            ++j;
        }
        g[in[i]] = i;
    }

    for(int i=1;i<=m;i++) puts(ans[i]?"Yes":"No");
    return 0;
}
