#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e6+1e2;

struct Heap {
    int lson[maxn],rson[maxn],dat[maxn],dep[maxn],cnt;
    inline int merge(int x,int y) {
        if( ! ( x && y ) ) return x | y;
        if( dat[x] < dat[y] ) swap(x,y);
        rson[x] = merge(rson[x],y);
        if( dep[lson[x]] < dep[rson[x]] ) swap(lson[x],rson[x]);
        dep[x] = dep[rson[x]] + 1;
        return x;
    }
    inline int top(int x) {
        return dat[x];
    }
    inline void pop(int& x) {
        x = merge(lson[x],rson[x]);
    }
    inline void push(int& x,int d) {
        dat[x=++cnt] = d;
    }
}hp;

int root[maxn],siz[maxn],n,cnt;
lli ans;

int main() {
    scanf("%d",&n);
    for(int i=1,t;i<=n;i++) {
        scanf("%d",&t) , hp.push(root[++cnt],t-i) , siz[cnt] = 1;
        while( cnt > 1 && hp.top(root[cnt-1]) > hp.top(root[cnt]) ) {
            t = ( siz[cnt] & 1 ) & ( siz[cnt-1] & 1 );
            root[cnt-1] = hp.merge(root[cnt],root[cnt-1]) , siz[cnt-1] += siz[cnt] , --cnt;
            if(t) hp.pop(root[cnt]);
        }
    }
    for(int i=1,cur=1;i<=cnt;i++)
        for(int j=1;j<=siz[i];j++,cur++)
            ans += abs( hp.dat[cur] - hp.top(root[i]) );
    printf("%lld\n",ans);
    return 0;
}
