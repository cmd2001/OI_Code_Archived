#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
const int maxn=75;
const lli inf=0x3f3f3f3f3f3f3f3fll;

struct Node {
    int d,w,v;
    friend bool operator < (const Node &a,const Node &b) { return a.d < b.d; }
}ns[maxn];

lli f[maxn][maxn][maxn];
int srt[maxn],su[maxn],len;
int n,k;

inline lli dfs(int l,int r,int w) { // w[root] >= w .
    if( l > r ) return 0;
    if( ~f[l][r][w] ) return f[l][r][w];
    lli &ret = f[l][r][w]; ret = inf;
    for(int rt=l;rt<=r;rt++) {
        if( ns[rt].w >= w ) ret = std::min( ret , dfs(l,rt-1,ns[rt].w) + dfs(rt+1,r,ns[rt].w) );
        ret = std::min( ret , dfs(l,rt-1,w) + dfs(rt+1,r,w) + k );
    }
    ret += su[r] - su[l-1];
    return ret;
}

inline void pre() {
    std::sort(ns+1,ns+1+n) , std::sort(srt+1,srt+1+n);
    for(int i=1;i<=n;i++) ns[i].w = std::lower_bound(srt+1,srt+1+n,ns[i].w) - srt, su[i] = su[i-1] + ns[i].v;
}

int main() {
    scanf("%d%d",&n,&k) , memset(f,-1,sizeof(f));
    for(int i=1;i<=n;i++) scanf("%d",&ns[i].d);
    for(int i=1;i<=n;i++) scanf("%d",&ns[i].w) , srt[i] = ns[i].w;
    for(int i=1;i<=n;i++) scanf("%d",&ns[i].v);
    pre() , printf("%lld\n",dfs(1,n,1));
    return 0;
}
