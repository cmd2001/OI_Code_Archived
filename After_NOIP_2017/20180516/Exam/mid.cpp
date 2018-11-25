#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#include<cstdio>
typedef long long int lli;
using namespace std;
const int maxe=4e7+1e2;
const int mod=1e9+7;

int root;
struct SemgnetTree {
    int lson[maxe],rson[maxe],sum[maxe],cnt;
    inline void insert(int &pos,int l,int r,const int &tar) {
        if( !pos ) pos = ++cnt;
        ++sum[pos];
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        tar <= mid ? insert(lson[pos],l,mid,tar) : insert(rson[pos],mid+1,r,tar) , sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline int query(int pos,int l,int r,int k) {
        if( l == r ) return l;
        const int mid = ( l + r ) >> 1;
        return k <= sum[lson[pos]] ?  query(lson[pos],l,mid,k) : query(rson[pos],mid+1,r,k-sum[lson[pos]]);
    }
}sgt;

inline int gen(int t,int ans) {
    return ( ( 714636908ll * t % mod + 681692770 ) % mod ) * ( ( 846930886ll * ans % mod + 804289376 ) % mod ) % mod;
}

int main() {
    static int n,t,ans,out;
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;i++) sgt.insert(root,1,mod,t) , ans = sgt.query(1,1,mod,(i+1)>>1) , out ^= ans , t = gen(t,ans);
    printf("%d\n",out);
    return 0;
}
