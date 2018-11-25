#include<cstdio>
#include<cstring>
#include<algorithm>
typedef double db;
const int maxn=2.5e3+1e2;
const db eps = 1e-3;

int s[maxn],t[maxn],nxt[maxn],siz[maxn];
db S[maxn],P[maxn],v[maxn],f[maxn][maxn];
int k,n;

inline void addedge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void mul(db* dst,const db* sou,int &ld,const int ls) {
    static db tp[maxn];
    memset(tp,0xfe,sizeof(db)*(ld+ls+1));
    for(int i=0;i<=ld;i++) for(int j=0;j<=ls;j++) tp[i+j] = std::max(tp[i+j],dst[i]+sou[j]);
    memcpy(dst,tp,sizeof(db)*(ld+ls+1)) , ld += ls;
}

inline void dfs(int pos) {
    f[pos][0] = 0 , siz[pos] = 0;
    for(int at=s[pos];at;at=nxt[at]) dfs(t[at]) , mul(f[pos],f[t[at]],siz[pos],siz[t[at]]);
    for(int i=++siz[pos];i;i--) f[pos][i] = f[pos][i-1] + v[pos];
}

inline bool judge(double mid) {
    for(int i=1;i<=n;i++) v[i] = P[i] - mid * S[i];
    dfs(1);
    return f[1][k] >= 0;
}
inline double bin() {
    double l = 0 , r = 1e4 , mid;
    while( r - l > eps ) {
        mid = ( l + r ) / 2.0;
        if( judge(mid) ) l = mid;
        else r = mid;
    }
    return l;
}

int main() {
    scanf("%d%d",&k,&n) , ++k , ++n;
    for(int i=2,t;i<=n;i++) scanf("%lf%lf%d",S+i,P+i,&t) , addedge(++t,i);
    printf("%0.3lf\n",bin());
    return 0;
}
