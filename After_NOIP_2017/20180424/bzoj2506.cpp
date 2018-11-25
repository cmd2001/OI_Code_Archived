#pragma GCC optimize(2)
#include<cstdio>
#include<vector>
using namespace std;
const int maxn=1e5+1e2,maxs=1e2+1e1,maxi=1e4+1e2,lim=100,mx=1e4;

int in[maxn],f[maxs][maxs],su[maxi],ans[maxn];

struct Query {
    int id,p,k,mul;
};
vector<Query> v[maxn];

inline void solve(const Query &q) {
    int ret = 0;
    if( q.p <= lim ) ret = f[q.p][q.k];
    else for(int i=q.k;i<=mx;i+=q.p) ret += su[i];
    ans[q.id] += q.mul * ret;
}
inline void move(int t) {
    for(int i=1;i<=lim;i++) ++f[i][t%i];
    ++su[t];
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1,l,r,p,k;i<=m;i++) scanf("%d%d%d%d",&l,&r,&p,&k) , v[l-1].push_back((Query){i,p,k,-1}) , v[r].push_back((Query){i,p,k,1});
    for(int i=0;i<=n;i++) {
        if(i) move(in[i]);
        for(unsigned j=0;j<v[i].size();j++) solve(v[i][j]);
    }
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}

