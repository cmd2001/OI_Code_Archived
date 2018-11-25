#include<cstdio>
#include<set>
using namespace std;
const int maxn=2e5+1e2;

int in[maxn];
int s[maxn],t[maxn<<1],nxt[maxn<<1];
multiset<int> f[maxn];

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos) {
    for(int at=s[pos];at;at=nxt[at]) {
        dfs(t[at]);
        if( f[t[at]].size() > f[pos].size() ) swap(f[t[at]],f[pos]);
        for(multiset<int>::iterator it=f[t[at]].begin();it!=f[t[at]].end();it++) f[pos].insert(*it);
        f[t[at]].clear();
    }
    multiset<int>::iterator it = f[pos].lower_bound(in[pos]);
    if( it != f[pos].end() ) f[pos].erase(it);
    f[pos].insert(in[pos]);
}

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1,fa;i<=n;i++) {
        scanf("%d%d",in+i,&fa);
        if( i != 1 ) addedge(fa,i);
    }
    dfs(1);
    printf("%u\n",(unsigned)f[1].size());
    return 0;
}
