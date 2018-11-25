#include<cstdio>
#include<algorithm>
#define bool unsigned char
#define lli long long int
using namespace std;
const int maxn=5e4+1e2,maxm=1e5+1e2;

int s[maxn],t[maxm<<1],nxt[maxm<<1];
lli dis[maxn],l[maxm<<1],p[70];
bool vis[maxn];

inline void addedge(int from,int to,lli len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}

inline void insert(lli x) {
    for(int i=62;~i;i--) {
        if( ! ( x >> i ) & 1 ) continue;
        if( !p[i] ) {
            p[i] = x;
            break;
        }
        x ^= p[i];
    }
}

inline void dfs(int pos,lli xo) {
    vis[pos] = 1 , dis[pos] = xo;
    for(int at=s[pos];at;at=nxt[at])
        if( vis[t[at]] ) insert(dis[t[at]]^xo^l[at]);
        else dfs(t[at],xo^l[at]);
}

inline lli query(lli x) {
    for(int i=62;~i;i--)
        x = max( x , x ^ p[i] );
    return x;
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) {
        lli l;
        scanf("%d%d%lld",&a,&b,&l);
        addedge(a,b,l) , addedge(b,a,l);
    }
    
    dfs(1,0);
    
    printf("%lld\n",query(dis[n]));
    
    return 0;
}