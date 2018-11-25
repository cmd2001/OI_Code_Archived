#include<cstdio>
#include<algorithm>
#define lli long long int
#define bool unsigned char
const int maxn=1e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

lli vara[maxn],varb[maxn],vale[maxn<<1],tp;
int visa[maxn],visb[maxn],tim;
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int lnk[maxn],n,m;

inline void addedge(int from,int to,int val) {
    static int cnt = 0;
    t[++cnt] = to , vale[cnt] = val ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline bool dfs(int pos) {
    visa[pos] = tim;
    for(int at=s[pos];at;at=nxt[at])
        if( visb[t[at]] != tim ) {
            if( vara[pos] + varb[t[at]] == vale[at] ) {
                visb[t[at]] = tim;
                if( !lnk[t[at]] || dfs(lnk[t[at]]) ) {
                    lnk[t[at]] = pos;
                    return 1;
                }
            } else tp = std::min( tp , vara[pos] + varb[t[at]] - vale[at] );
        }
    return 0;
}
inline lli pir() {
    for(int i=1;i<=n+m;i++) {
        while(1) {
            ++tim , tp = inf;
            if( dfs(i) ) break;
            for(int i=1;i<=n+m;i++) if( visa[i] == tim ) vara[i] -= tp;
            for(int i=1;i<=n*m;i++) if( visb[i] == tim ) varb[i] += tp;
        }
    }
    lli ret = 0;
    for(int i=1;i<=n+m;i++) ret += vara[i];
    for(int i=1;i<=n*m;i++) ret += varb[i];
    return ret;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n+m;i++) vara[i] = -inf;
    for(int i=1;i<=n;i++)
        for(int j=1,id,t;j<=m;j++) {
            id =  m * ( i - 1 ) + j;
            scanf("%d",&t);
            vara[i] = std::max( vara[i] , -1ll * t ) , vara[j+n] = std::max( vara[j+n] , -1ll * t );
            addedge(i,id,-t) , addedge(j+n,id,-t);
        }
    printf("%lld\n",-pir());
    return 0;
}
