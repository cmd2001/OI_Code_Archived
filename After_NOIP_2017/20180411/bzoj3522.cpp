#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=5e3+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],dep[maxn];
lli s1[maxn],s2[maxn],tp[maxn],ans;
int n,mx;

inline void coredge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int from,int to) {
    coredge(from,to) , coredge(to,from);
}

inline void dfs(int pos,int fa) {
    mx = max( mx , dep[pos] ) , ++tp[dep[pos]];
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa )
            dep[t[at]] = dep[pos] + 1 , dfs(t[at],pos);
}
inline void calcbase(int pos) {
    memset(s1,0,sizeof(lli)*n) , memset(s2,0,sizeof(lli)*n);
    for(int at=s[pos];at;at=nxt[at]) {
        memset(tp,0,sizeof(lli)*(mx+1));
        dep[t[at]] = 1 , dfs(t[at],pos);
        for(int i=1;i<=mx;i++) ans += s2[i] * tp[i];
        for(int i=1;i<=mx;i++) s2[i] += s1[i] * tp[i];
        for(int i=1;i<=mx;i++) s1[i] += tp[i];
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b);
    for(int i=1;i<=n;i++) calcbase(i);
    printf("%lld\n",ans);
    return 0;
}

