#include<cstdio>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=1e3+1e2;

struct Node {
    lli id;
    int val;
    friend bool operator < (const Node &a,const Node &b) {
        return a.val > b.val;
    }
}ns[maxn];

inline bool insert(lli x) {
    static lli p[70];
    for(int i=62;~i;i--) {
        if( ! ( x >> i ) ) continue;
        if( !p[i] ) {
            p[i] = x;
            return 1;
        }
        x ^= p[i];
    }
    return 0;
}

int main() {
    static int n,ans;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld%d",&ns[i].id,&ns[i].val);
    
    sort(ns+1,ns+1+n);
    for(int i=1;i<=n;i++)
        if( insert(ns[i].id) )
            ans += ns[i].val;
    
    printf("%d\n",ans);
    
    return 0;
}