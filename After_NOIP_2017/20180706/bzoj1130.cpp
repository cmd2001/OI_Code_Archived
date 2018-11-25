#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=30,maxs=(1<<13),mask=maxs-1;
const int inf=0x3f3f3f3f;
 
int pre[maxs+100],deg[maxn],n;
int ans=inf,ss;
inline int forcebit(int x) {
    int ret = 0;
    #define lowbit(x) (x&-x)
    while( x ) ++ret , x -= lowbit(x);
    return ret;
}
inline int countbit(int x) {
    return pre[x>>13] + pre[x&mask];
}
 
inline void dfs(int sta,int sum,int now,int last) {
    if( sum == n / 2 ) {
        if( now < ans ) {
            ans = now , ss = sta;
        }
        return;
    }
    for(int i=last+1;i<=n;i++)
        if( ! ( sta & ( 1 << ( i - 1 ) ) ) )
            dfs(sta|(1<<(i-1)),sum+1,now-countbit(sta&deg[i])+countbit((~sta)&deg[i]),i);
}
 
int main() {
    static int m;
    for(int i=0;i<maxs;i++) pre[i] = forcebit(i);
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d",&a,&b);
        deg[a] |= ( 1 << ( b - 1 ) ) ,
        deg[b] |= ( 1 << ( a - 1 ) ) ;
    }
    dfs(0,0,0,0);
    for(int i=1;i<=n;i++) if( ss & ( 1 << ( i - 1 ) ) ) printf("%d ",i);
    putchar('\n');
    return 0;
}
