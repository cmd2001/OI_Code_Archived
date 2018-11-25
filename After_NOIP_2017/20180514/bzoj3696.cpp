#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2,maxe=5e2+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int f[maxn][maxe],mxd[maxn];
lli ans[maxe];

inline void addedge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos) {
    f[pos][mxd[pos]=0] = 1;
    for(int at=s[pos];at;at=nxt[at]) {
        dfs(t[at]);
        for(int i=0;i<=mxd[pos];i++) for(int j=0;j<=mxd[t[at]];j++) ans[i^(j+1)] += (lli) f[pos][i] * f[t[at]][j];
        for(int j=0;j<=mxd[t[at]];j++) f[pos][j+1] += f[t[at]][j];
        mxd[pos] = max( mxd[pos] , mxd[t[at]] + 1 );
    }
}

int main() {
    static int n,mx;
    scanf("%d",&n);
    for(int i=2,fa;i<=n;i++) scanf("%d",&fa) , addedge(fa,i);
    dfs(1);
    for(mx=512;!ans[mx];--mx) ;
    for(int i=0;i<=mx;i++) printf("%lld\n",ans[i]);
    return 0;
}
