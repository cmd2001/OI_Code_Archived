#include<cstdio>
#include<cstring>
#include<cstdlib>
#define lli long long int
const int maxn=1e3+1e2,maxm=1e4+1e2;
const int mod=1e9+7;

int s[maxn],t[maxm<<1],nxt[maxm<<1],l[maxm<<1],cnt;
lli spd[maxn];
int n,fail;

inline lli fastpow(lli base,int tim,int mod) {
    lli ret = 1;
    while( tim ) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
inline void singledge(int from,int to,int len) {
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}

inline void dfs(int pos) {
    for(int at=s[pos];at&&!fail;at=nxt[at]) {
        const lli tar = spd[pos] * l[at] % mod;
        if( spd[t[at]] ) {
            if( spd[t[at]] != tar ) {
                fail = 1;
                return;
            }
        } else {
            spd[t[at]] = tar;
            dfs(t[at]);
        }
    }
}

inline void init() {
    memset(s+1,0,sizeof(int)*n) , memset(spd+1,0,sizeof(lli)*n) ,
    fail = cnt = 0;
}

int main() {
    static int T,m;
    scanf("%d",&T);
    for(int p=1;p<=T;p++) {
        init(); scanf("%d%d",&n,&m);
        for(int i=1,u,v,a,b,f;i<=m;i++) {
            scanf("%d%d%d%d",&u,&v,&a,&b) , f = b > 0 ? 1 : -1 , b = abs(b);
            singledge(u,v,((lli)b*fastpow(a,mod-2,mod)%mod*f+mod)%mod) ,
            singledge(v,u,((lli)a*fastpow(b,mod-2,mod)%mod*f+mod)%mod) ;
        }
        for(int i=1;i<=n&&!fail;i++) if( !spd[i] ) {
            spd[i] = 1;
            dfs(i);
        }
        printf("Case #%d: ",p);
        puts(fail?"No":"Yes");
    }
    return 0;
}
