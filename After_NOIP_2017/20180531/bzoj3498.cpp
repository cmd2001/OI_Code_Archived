#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<cmath>
typedef long long int lli;
const int maxn=1e5+1e2;

int val[maxn],srt[maxn],rnk[maxn],mrk[maxn];
std::vector<int> in[maxn];
std::set<int> rel[maxn];

inline bool cmp(const int &x,const int &y) {
    return val[x] > val[y];
}

int main() {
    static int n,m,sq;
    static lli ans;
    scanf("%d%d",&n,&m) , sq = std::sqrt(m);
    for(int i=1;i<=n;i++) scanf("%d",val+i) , srt[i] = i;
    std::sort(srt+1,srt+1+n,cmp);
    for(int i=1;i<=n;i++) rnk[srt[i]] = i;
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , rnk[a] < rnk[b] ? in[a].push_back(b) : in[b].push_back(a);
    for(int i=n;i;i--) {
        const int u = srt[i];
        for(unsigned j=0;j<in[u].size();j++) mrk[in[u][j]] = i;
        for(unsigned j=0;j<in[u].size();j++) {
            const int v = in[u][j];
            if( in[v].size() <= sq ) {
                for(unsigned k=0;k<in[v].size();k++) if( mrk[in[v][k]] == i ) ans += val[u];
            } else {
                for(unsigned k=0;k<in[u].size();k++) if( rel[v].count(in[u][k]) ) ans += val[u];
            }
            rel[u].insert(v);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
