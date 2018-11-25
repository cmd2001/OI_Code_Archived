#pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
#include<ext/rope>
const int maxn=1e5+1e2;

int ans[maxn],n;
__gnu_cxx::rope<int> seq;

struct BinaryIndexTree {
    int dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int x,int val) {
        while( x <= n ) dat[x] = std::max( dat[x] , val ) , x += lowbit(x);
    }
    inline int query(int x) {
        int ret = 0;
        while(x) ret = std::max( ret , dat[x] ) , x -= lowbit(x);
        return ret;
    }
}bit;

int main() {
    scanf("%d",&n);
    for(int i=1,t;i<=n;i++) scanf("%d",&t) , seq.insert(t,i);
    for(int i=0,t;i<n;i++) t = seq[i] , bit.update(t,ans[t]=bit.query(t)+1);
    for(int i=1;i<=n;i++) printf("%d\n",ans[i]=std::max(ans[i],ans[i-1]));
    return 0;
}
