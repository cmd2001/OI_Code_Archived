#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<bitset>
#include<queue>
#define debug cout
using namespace std;
const int maxn=3e4+1e2,maxe=1e5+1e2;

vector<int> g[maxn],rg[maxn];
bitset<maxn> tar[maxn];
int deg[maxn],f[maxn];
int n,m,ans;

inline bool cmp(const int &x,const int &y) {
    return f[x] > f[y];
}
inline void getans() {
    for(int i=1;i<=n;i++) for(unsigned j=0;j<rg[i].size();j++) ++deg[rg[i][j]];
    queue<int> q;
    for(int i=1;i<=n;i++) if( !deg[i] ) q.push(i);
    while( q.size() ) {
        const int pos = q.front(); q.pop() , f[pos] = max( f[pos] , 1 ) , tar[pos][pos] = 1;
        if( g[pos].size() ) {
            sort(g[pos].begin(),g[pos].end(),cmp);
            for(unsigned j=0;j<g[pos].size();j++) {
                if( tar[pos][g[pos][j]] ) ++ans;
                else tar[pos] |= tar[g[pos][j]];
            }
        }
        for(unsigned j=0;j<rg[pos].size();j++) {
            f[rg[pos][j]] = max( f[rg[pos][j]] , f[pos] + 1 );
            if( !--deg[rg[pos][j]] ) q.push(rg[pos][j]);
        }
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , g[a].push_back(b) , rg[b].push_back(a);
    getans() , printf("%d\n",ans);
    return 0;
}

