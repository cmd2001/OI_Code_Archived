#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2,maxe=2e5+1e2;
const int mod=1e9+7;

int inv[maxe];
int s[maxn],t[maxe<<1],nxt[maxe<<1];
int deg[maxn],bdeg[maxn],f[maxn],ans=1;
int n,m,x,y;

inline int sub(const int &x,const int &y) {
    const int ret = x - y;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &x,const int &y) {
    if( ( x += y ) >= mod ) x -= mod;
}
inline void mule(int &x,const int &y) {
    x = (lli) x * y % mod;
}

inline void sieve() {
    inv[1] = 1;
    for(int i=2;i<=m+1;i++) inv[i] = mul(mod-mod/i,inv[mod%i]);
}

inline void addedge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt , ++deg[to] , ++bdeg[to];
}

inline void topo() {
    queue<int> q;
    f[y] = ans;
    for(int i=1;i<=n;i++) if( !deg[i] ) q.push(i);
    while( q.size() ) {
        const int pos = q.front(); q.pop() , mule(f[pos],inv[bdeg[pos]]);
        for(int at=s[pos];at;at=nxt[at]) {
            adde(f[t[at]],f[pos]);
            if( !--deg[t[at]] ) q.push(t[at]);
        }
    }
}

int main() {
    scanf("%d%d%d%d",&n,&m,&x,&y) , sieve();
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , addedge(a,b);
    ++bdeg[y];
    for(int i=2;i<=n;i++) mule(ans,bdeg[i]);
    if( y == 1 ) return printf("%d\n",ans) , 0;
    topo() , printf("%d\n",sub(ans,f[x]));
    return 0;
}

