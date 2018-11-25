#include<cstdio>
#define lli long long int
using namespace std;
const int maxn=1e5+1e2,maxm=2e6+1e2;
const int mod = 1e9+7;

int id[maxn][22];
int fa[maxm],st[maxm],cnt;
int n;

inline void gen() {
    for(int i=1;i<=n;i++) {
        for(int len=0;i+(1<<len)-1<=n;len++)
            id[i][len] = ++cnt , st[cnt] = i;
    }
    for(int i=1;i<=cnt;i++) fa[i] = i;
}
inline int findfa(int x) {
    return fa[x] == x ? x : fa[x] = findfa(fa[x]);
}
inline void merge(int x,int y) {
    x = findfa(x) , y = findfa(y);
    if( x != y ) fa[y] = x;
}
inline void merge(int i,int j,int l) {
    for(int len=20;~len;len--)
        if( (1<<len) <= l ) {
            merge( id[i][len] , id[j][len] );
            i += ( 1 << len ) ,
            j += ( 1 << len ) ,
            l -= ( 1 << len );
        }
}
inline void getans() {
    for(int len=20;len;len--)
        for(int i=1;i<=n;i++)
            if( id[i][len] && id[i][len] != findfa(id[i][len]) ) {
                int t = findfa(id[i][len]) , f = st[t] , p = 1 << (len-1);
                merge(id[i][len-1],id[f][len-1]) , merge(id[i+p][len-1],id[f+p][len-1]);
            }
    lli ans = 1;
    for(int i=1,t=0;i<=n;i++) {
        if( findfa(id[i][0]) == id[i][0] ) ans *= t++ ? 10 : 9 , ans %= mod;
    }
    printf("%lld\n",ans);
}

int main() {
    static int m,l,r,len;
    scanf("%d%d",&n,&m);
    gen();
    for(int i=1;i<=m;i++) {
        scanf("%d%d%d%*d",&l,&len,&r);
        len = ( len - l + 1 );
        merge(l,r,len);
    }
    getans();
    return 0;
}
