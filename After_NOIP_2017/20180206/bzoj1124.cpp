#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define bool unsigned char
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

int tar[maxn],deg[maxn],n;

namespace Maximum_Death { // returning number of person who can keep alive
    int vis[maxn];
    
    inline void killself() {
        for(int i=1;i<=n;i++)
            if( tar[i] == i ) vis[i] = -1;
    }
    inline bool realring(int pos,int t) {
        if( vis[pos] ) return vis[pos] == t;
        vis[pos] = t;
        if( deg[tar[pos]] != 1 ) {
            realring(tar[pos],t);
            return 0;
        }
        return realring(tar[pos],t);
    }
    inline int work() {
        int ret = 0;
        killself();
        for(int i=1;i<=n;i++)
            if( !vis[i] ) ret += realring(i,i);
        //debug<<"ringed ret = "<<ret<<endl;
        for(int i=1;i<=n;i++)
            ret += !deg[i];
        //debug<<"ret = "<<ret<<endl;
        return ret;
    }
}

namespace Minimum_Death {
    int d[maxn];
    bool vis[maxn];
    
    inline int dfs(int pos) {
        if( vis[pos] ) return 0;
        vis[pos] = 1;
        return dfs(tar[pos]) + 1;
    }
    inline int topo() {
        int ret = 0;
        queue<int> q;
        for(int i=1;i<=n;i++)
            if( !d[i] ) q.push(i);
        while( q.size() ) {
            const int pos = q.front(); q.pop(); ++ret;
            vis[pos] = 1;
            if( !vis[tar[pos]] && !--deg[tar[tar[pos]]] ) {
                q.push(tar[tar[pos]]);
            }
            vis[tar[pos]] = 1;
        }
        return ret;
    }
    inline int work() {
        memcpy(d,deg,sizeof(d));
        int ret = topo() ;
        //debug<<"in mini inital ret = "<<ret<<endl;
        for(int i=1;i<=n;i++)
            if( !vis[i] ) ret += dfs(i) >> 1;
        //debug<<"in mini ret = "<<ret<<endl;
        return ret;
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d",tar+i) , ++deg[tar[i]];
    }
    printf("%d %d\n",n-Minimum_Death::work(),n-Maximum_Death::work());
    return 0;
}


