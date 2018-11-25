#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef unsigned long long int ulli;
using namespace std;
const int maxn=1e5+1e2,maxe=8e6+1e2;
const ulli base = 107 , lim = -1;

int roots[maxn];
struct PersistentSegmentTree {
    int lson[maxe],rson[maxe],su[maxe],cnt;
    inline void insert(int &pos,int pre,ulli l,ulli r,const ulli &tar) {
        su[pos=++cnt] = su[pre] + 1;
        if( l == r ) return;
        const ulli mid = ( l >> 1 ) + ( r >> 1 ) + ( ( l & 1 ) & ( r & 1 ) );
        if( tar <= mid ) insert(lson[pos],lson[pre],l,mid,tar) , rson[pos] = rson[pre];
        else insert(rson[pos],rson[pre],mid+1,r,tar) , lson[pos] = lson[pre];        
    }
    inline int query(int pos,int pre,ulli l,ulli r,const ulli &tar) {
        if( pos == pre || l == r ) return su[pos] - su[pre];
        const ulli mid = ( l >> 1 ) + ( r >> 1 ) + ( ( l & 1 ) & ( r & 1 ) );
        return tar <= mid ? query(lson[pos],lson[pre],l,mid,tar) : query(rson[pos],rson[pre],mid+1,r,tar);
    }
}pst;

int in[maxn];
ulli h[maxn],pows[maxn],th;

int main() {
    static int n,m,k;
    scanf("%d%d%d",&n,&m,&k) , *pows = 1;
    for(int i=1;i<=n;i++) scanf("%d",in+i) , h[i] = h[i-1] * base + in[i] , pows[i] = pows[i-1] * base;
    for(int i=k;i<=n;i++) pst.insert(roots[i],roots[i-1],0,lim,h[i]-h[i-k]*pows[k]);
    for(int i=1,l,r;i<=m;i++) {
        scanf("%d%d",&l,&r) , th = 0 , l += k - 1;
        for(int i=1,t;i<=k;i++) scanf("%d",&t) , th = th * base + t;
        if( l > r || !pst.query(roots[r],roots[l-1],0,lim,th) ) puts("Yes");
        else puts("No");
    }
    return 0;
}



