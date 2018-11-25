#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn=2e3+1e2;
const int inf=0x3f3f3f3f;

vector<int> pics[maxn],keys[maxn];
unsigned char vis[maxn];
int s[maxn],t[maxn<<1],nxt[maxn<<1],cnt;
int vals[maxn];
int ans;

inline void addedge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}

inline void dfs(int pos,int fa,int sum) {
    for(unsigned i=0;i<keys[pos].size();i++)
        vis[keys[pos][i]] = 1;
    for(unsigned i=0;i<pics[pos].size();i++)
        if( vis[pics[pos][i]] ) sum += vals[pics[pos][i]];
    ans = max( ans , sum );
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa )
            dfs(t[at],pos,sum);
    for(unsigned i=0;i<keys[pos].size();i++)
        vis[keys[pos][i]] = 0;
}

inline void reset() {
    memset(s,0,sizeof(s)) , cnt = 0;
    for(int i=0;i<maxn;i++)
        keys[i].clear() , pics[i].clear();
    ans = -inf;
}

int main() {
    static int T,n,m;
    scanf("%d",&T);
    for(int t=1;t<=T;t++) {
        reset();
        scanf("%d%d",&n,&m);
        for(int i=1,a,b;i<n;i++) {
            scanf("%d%d",&a,&b);
            addedge(a,b) , addedge(b,a);
        }
        for(int i=1,p,k;i<=m;i++) {
            scanf("%d%d%d",&p,&k,vals+i);
            pics[p].push_back(i) , keys[k].push_back(i);
        }
        for(int i=1;i<=n;i++)
            dfs(i,-1,0);
        printf("Case #%d: ",t);
        printf("%d\n",ans);
    }
    
    return 0;
}