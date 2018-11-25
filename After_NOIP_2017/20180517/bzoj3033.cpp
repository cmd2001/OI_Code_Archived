#include<cstdio>
const int maxn=2051;

int ans[maxn],vis[maxn];
int n,tar;

inline bool dfs(int pos,int dep) {
    if(vis[pos]) return 0;
    if( dep == tar ) return 1;
    ans[dep] = pos & 1 , vis[pos] = 1;
    if( dfs((pos<<1)&(tar-1),dep+1) ) return 1;
    if( dfs((pos<<1|1)&(tar-1),dep+1) ) return 1;
    return vis[pos] = 0;
}

int main() {
    scanf("%d",&n) , printf("%d ",tar=1<<n) , dfs(0,1);
    for(int i=1;i<n;i++) putchar('0');
    for(int i=1;i<=tar-n+1;i++) putchar('0'+ans[i]);
    putchar('\n');
    return 0;
}
