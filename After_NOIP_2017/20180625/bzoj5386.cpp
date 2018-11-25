#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],deg[maxn],f[maxn],siz[maxn],n,k,ans;
bool vis[maxn];

inline void coredge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    ++deg[a] , ++deg[b];
    coredge(a,b) , coredge(b,a);
}

int main() {
    scanf("%d%d",&n,&k);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b);
    queue<int> q;
    for(int i=1;i<=n;i++) if( deg[i] <= 1 ) f[i] = 1 , q.push(i);
    while( q.size() ) {
        const int pos = q.front(); q.pop() , vis[pos] = 1 , ++siz[f[pos]];
        for(int at=s[pos];at;at=nxt[at]) if( --deg[t[at]] == 1 ) {
            if( !vis[t[at]] ) q.push(t[at]) , vis[t[at]] = 1 , f[t[at]] = f[pos] + 1;
        }
    }
    for(int i=1;i<=k>>1;i++) ans += siz[i];
    if( ans < n && ( k & 1 ) ) ++ans;
    printf("%d",ans);
    return 0;
}
