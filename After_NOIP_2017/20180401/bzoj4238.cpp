#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e5+1e2,maxe=2e5+1e2;

int dep[maxn],fa[maxn],vis[maxn],can[maxn],ban[maxn],sizcan;
int s[maxn],t[maxe<<1],nxt[maxe<<1],cnt=1;
int n,ans;

inline void addedge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}

inline void dfs(int pos,int sou) {
    vis[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) {
        if( at == ( sou ^ 1 ) ) continue;
        else {
            if( !vis[t[at]] ) {
                fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1;
                dfs(t[at],at);
                can[pos] += can[t[at]] , ban[pos] += ban[t[at]];
            } else if( dep[t[at]] <= dep[pos] ) {
                if( ( dep[pos] - dep[t[at]] + 1 ) & 1 ) ++can[pos] , --can[t[at]] , ++sizcan;
                else ++ban[pos] , --ban[t[at]];
            }
        }
    }
}

inline void getans() {
    for(int i=1;i<=n;i++) if( !vis[i] ) dfs(i,0);
    for(int i=1;i<=n;i++) if( fa[i] && can[i] == sizcan && !ban[i] ) ++ans;
    ans += ( sizcan == 1 );
}

int main() {
    static int m;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , addedge(a,b) , addedge(b,a);
    getans() , printf("%d\n",ans);
    return 0;
}
//我这样的人活在世上，真是对不起呢。