#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int maxn=1e5+1e2,maxe=5e5+1e4;

struct LinearBase {
    int dat[33];
    inline bool insert(int x) {
        for(int i=31;~i;i--) if( x & ( 1 << i ) ) {
            if( !dat[i] ) return dat[i] = x,1;
            else x ^= dat[i];
        }
        return 0;
    }
    inline void clear() {
        memset(dat,0,sizeof(dat));
    }
}lb;

int s[maxn],t[maxe],nxt[maxe];
int sum[maxn],val[maxe],vis[maxn];

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
    vis[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( !vis[t[at]] ) pre(t[at]);
        else {
            val[at] = rand() , 
            sum[t[at]] ^= val[at] , 
            sum[pos] ^= val[at];
        }
}
inline void dfs(int pos) {
    vis[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( !vis[t[at]] ) {
        dfs(t[at]) ,
        sum[pos] ^= ( val[at] = sum[t[at]] );
    }
}
inline bool judge(int t,int mask) {
    int x,ret=1; lb.clear();
    while(t--) {
        scanf("%d",&x) , x ^= mask;
        ret &= lb.insert(val[x]);
    }
    return ret;
}

int main() {
    static int n,m,q,su;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d",&a,&b);
        if( a > b ) swap(a,b);
        addedge(a,b);
    }
    pre(1) , memset(vis,0,sizeof(vis)) , dfs(1);
    scanf("%d",&q);
    for(int i=1,t;i<=q;i++) {
        scanf("%d",&t);
        if( judge(t,su) ) puts("Connected") , ++su;
        else puts("Disconnected"); 
    }
    return 0;
}