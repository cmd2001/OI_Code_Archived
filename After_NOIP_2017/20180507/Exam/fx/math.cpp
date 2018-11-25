#include<cstdio>
#include<algorithm>
#include<vector>
typedef long long int lli;
const int maxn=2e3+1e2,maxs=(1<<14)+5;
const int prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43},pl=14,full=1<<14;
const int mod=1e9+7;

struct Node {
    int sta,mx;
    friend bool operator < (const Node &a,const Node &b) { return a.mx > b.mx; }
}ns[maxn];

std::vector<Node> grp[maxn];
lli f[maxn][maxs],ans;
int n,cnt;

inline Node cut(int x) {
    int ret = 0;
    for(int i=0;i<pl;i++)
        if( ! ( x % prime[i] ) ) {
            ret |= (1<<i);
            while( ! ( x % prime[i] ) ) x /= prime[i];
        }
    return (Node){ret,x};
}

inline void getgrp() {
    std::sort(ns+1,ns+1+n);
    for(int i=1;i<=n;i++) {
        if( ns[i].mx != ns[i-1].mx || ns[i].mx == 1 ) ++cnt;
        grp[cnt].push_back(ns[i]);
    }
}
inline void dp() {
    **f = 1;
    for(int i=1;i<=cnt;i++) {
        for(unsigned cur=0;cur<grp[i].size();cur++)
            for(int sta=0;sta<full;sta++) {
                if( ! ( sta & grp[i][cur].sta ) )
                    f[i][sta|grp[i][cur].sta] = ( f[i][sta|grp[i][cur].sta] + f[i-1][sta] ) % mod;
                }
        for(int sta=0;sta<full;sta++) f[i][sta] = ( f[i][sta] + f[i-1][sta] ) % mod;
    }
    for(int i=0;i<full;i++) ans = ( ans + f[cnt][i] ) % mod;
}

int main() {
    scanf("%d",&n);
    for(int i=1,t;i<=n;i++) scanf("%d",&t) , ns[i] = cut(t);
    getgrp() , dp() , printf("%lld\n",(ans-1+mod)%mod);
    return 0;
}
