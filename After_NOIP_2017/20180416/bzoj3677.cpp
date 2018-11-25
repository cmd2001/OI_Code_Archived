#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn=2e5+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
vector<int> son[maxn],pef[maxn],suf[maxn],len[maxn];
int f[maxn][2],ans;

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs1(int pos,int fa) {
    f[pos][0] = 0 , f[pos][1] = -inf;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) son[pos].push_back(t[at]) , len[pos].push_back(l[at]);
    for(unsigned i=0;i<son[pos].size();i++) {
        dfs1(son[pos][i],pos) , f[pos][0] += max( f[son[pos][i]][0] , f[son[pos][i]][1] + len[pos][i] );
        pef[pos].push_back(f[son[pos][i]][0]-max(f[son[pos][i]][0],f[son[pos][i]][1]+len[pos][i])+len[pos][i]) ,
        suf[pos].push_back(f[son[pos][i]][0]-max(f[son[pos][i]][0],f[son[pos][i]][1]+len[pos][i])+len[pos][i]) ;
    }
    for(unsigned i=0;i<son[pos].size();i++) f[pos][1] = max( f[pos][1] , f[pos][0] + pef[pos][i] );
    for(unsigned i=1;i<son[pos].size();i++) pef[pos][i] = max( pef[pos][i] , pef[pos][i-1] );
    for(int i=(signed)son[pos].size()-2;i>=0;i--) suf[pos][i] = max( suf[pos][i] , suf[pos][i+1] );
}
inline void dfs2(int pos,int ffa0,int ffa1,int lfa) {
    f[pos][1] += max( ffa0 , ffa1 + lfa ) , f[pos][0] += max( ffa0 , ffa1 + lfa ) , f[pos][1] = max( f[pos][1] , f[pos][0] + ffa0 - max( ffa0 , ffa1 + lfa ) + lfa );
    ans = max( ans , f[pos][0] );
    for(unsigned i=0;i<son[pos].size();i++) {
        int fnow0 = f[pos][0] - max( f[son[pos][i]][0] , f[son[pos][i]][1] + len[pos][i] );
        int delta = ffa0 - max( ffa0 , ffa1 + lfa ) + lfa;
        if( i != 0 ) delta = max( delta , pef[pos][i-1] );
        if( i != son[pos].size() - 1 ) delta = max( delta , suf[pos][i+1] );
        dfs2(son[pos][i],fnow0,fnow0+delta,len[pos][i]);
    }
}

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1,a,b,l;i<n;i++) scanf("%d%d%d",&a,&b,&l) , addedge(a,b,l) , addedge(b,a,l);
    dfs1(1,-1) , dfs2(1,0,-inf,-inf) , printf("%d\n",ans);
    return 0;
}
