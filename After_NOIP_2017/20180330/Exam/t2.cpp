#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define bool unsigned char
#define debug cout
typedef long double ldb;
using namespace std;
const int maxn=1e4+1e2,maxe=1e5+1e2;

int s[maxn],t[maxe],nxt[maxe],l[maxe];
ldb f[maxn][2],ans;
bool vis[maxn];

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}

inline void dfs(int pos) {
    if( vis[pos] ) return;
    vis[pos] = 1;
    ldb sf,sw,wn,wt;
    int se = 0;
    sf = sw = wn = wt = 0;
    for(int at=s[pos];at;at=nxt[at]) {
        dfs(t[at]) , sw += l[at] , ++se;
        sf += l[at] * ( f[t[at]][0] + 1 );
    }
    if( !se ) return; // Or you will get "nan" .
    f[pos][0] = sf / sw;
    for(int at=s[pos];at;at=nxt[at]) {
        wn = max( wn , ( sf - ( f[t[at]][0] + 1 ) * l[at] + ( f[t[at]][1] + 1 ) * l[at] ) / sw );
        if( se != 1 ) wt = max( wt , ( sf - ( f[t[at]][0] + 1 ) * l[at] ) / ( sw - l[at] ) );
    }
    f[pos][1] = max( wn , wt );
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b,l;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&l) , ++a , ++b;
        addedge(a,b,l);
    }
    dfs(1) , ans = max( f[1][0] , f[1][1] );
    printf("%0.6Lf\n",ans);
    return 0;
}

