#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=2e2+1e1;

int in[maxn][maxn],ans[maxn];
int n,tpe;

namespace Tarjan {
    int dfn[maxn],low[maxn],id[maxn],stk[maxn],vis[maxn],ins[maxn],top,dd,iid;
    inline void dfs(int pos) {
        vis[pos] = 1;
        low[pos] = dfn[pos] = ++dd ,
        stk[++top] = pos , ins[pos] = 1;
        for(int i=1;i<=n;i++)
            if( in[pos][i] && !vis[i] ) {
                dfs(i);
                low[pos] = min( low[pos] , low[i] );
            } else if( ins[i] ) low[pos] = min( low[pos] , dfn[i] );
        if( low[pos] == dfn[pos] ) {
            ++iid;
            do {
                const int x = stk[top--]; ins[x] = 0;
                id[x] = iid;
            } while( ins[pos] );
        }
    }
    inline bool work() {
        for(int i=1;i<=n;i++) if( !vis[i] ) dfs(i);
        for(int i=1;i<=n;i++) if( id[i] != id[1] ) return 0;
        return 1;
    }
}
namespace Build {
    int nxt[maxn],used[maxn],head,tail;
    inline void init(int hh) {
        memset(nxt,0,sizeof(nxt));
        head = tail = hh;
    }
    inline int build(int hh) {
        init(hh);
        for(int i=1;i<=n;i++)
            if( i != hh ) {
                if( in[i][head] ) nxt[i] = head , head = i;
                else {
                    int now;
                    for(now=head;nxt[now]&&in[nxt[now]][i];now=nxt[now]);
                    nxt[i] = nxt[now] , nxt[now] = i;
                    if( !nxt[i] ) tail = i;
                }
            }
        return in[tail][head];
    }
    inline void getans(int tpe) {
        if( tpe ) build(1);
        else for(int i=1;i<=n;i++) if( build(i) ) break;
        for(int i=head,now=0;i;i=nxt[i]) ans[++now] = i;
    }
    
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",in[i]+j);
    int tpe = Tarjan::work() ^ 1;
    Build::getans(tpe);
    printf("%d\n",tpe);
    for(int i=1;i<=n;i++) printf("%d%c",ans[i],i!=n?' ':'\n');
    return 0;
}
