#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

lli w[maxn],sum,len,mi,ans,ami=0x3f3f3f3f;
int a[maxn],rb[maxn],tar[maxn],vis[maxn],n;

inline void dfs(int pos) {
    if( vis[pos] ) return;
    vis[pos] = 1,
    sum += w[a[pos]] , ++len , mi = min( mi , w[a[pos]] );
    dfs(tar[pos]);
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",w+i) , ami = min( ami , w[i] );
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1,x;i<=n;i++) scanf("%d",&x) ,rb[x] = i;
    for(int i=1;i<=n;i++) tar[i] = rb[a[i]];
    for(int i=1;i<=n;i++)
        if( !vis[i] && tar[i] != i ) {
            sum = len = 0 , mi = 0x3f3f3f3f;
            dfs(i);
            ans += min( sum + ( len - 2 ) * mi , sum + mi + ami * ( len + 1 ) );
        }
    printf("%lld\n",ans);
    return 0;
}

