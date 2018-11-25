#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e3+1e2;

int a[maxn],b[maxn],mx,ans;
int sg[maxn],vis[maxn];

int main() {
    static int n,m;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i) , mx = max( mx , a[i] );
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d",b+i);
    for(int i=1;i<=mx;i++) {
        memset(vis,0,sizeof(vis));
        for(int j=1;j<=m;j++) if( i - b[j] >= 0 ) vis[sg[i-b[j]]] = 1;
        for(int j=0;j<=mx;j++)
            if( !vis[j] ) {
                sg[i] = j;
                break;
            }
    }
    for(int i=1;i<=n;i++) ans ^= sg[a[i]];
    if( !ans ) return puts("NO"),0;
    puts("YES");
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( a[i] >= b[j] && ! ( ans ^ sg[a[i]] ^ sg[a[i]-b[j]] )  )
                return printf("%d %d\n",i,b[j]),0;
    return 0;
}
