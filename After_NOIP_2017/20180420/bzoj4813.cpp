#include<cstdio>
#include<algorithm>
const int maxn=1e2+1e1;

int s[maxn],t[maxn<<1],nxt[maxn<<1],n,m,chain,cnt;

inline void addedge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline int dfs(int pos,int fa) {
    int ret = 0;
    for(int at=s[pos],son;at;at=nxt[at]) if( t[at] != fa ) son = dfs(t[at],pos) + 1 , ret = std::max( ret , son );
    return ret;
}

int main() {
    scanf("%d%d",&n,&m);
    if( m > ( n - 1 ) * 2 ) return printf("%d\n",n),0;
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , ++a , ++b , addedge(a,b) , addedge(b,a);
    chain = dfs(1,-1);
    if( m <= chain ) printf("%d\n",m+1);
    else printf("%d\n",(m-chain)/2+chain+1);
    return 0;
}
