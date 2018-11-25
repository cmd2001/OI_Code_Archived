#include<cstdio>
#include<algorithm>
#include<set>
typedef long long int lli;
const int maxn=2e5+1e2;

struct Node {
    int i,b;
    friend bool operator < (const Node &a,const Node &b) {
        return a.b > b.b;
    }
}in[maxn];
std::multiset<int> ms;

int main() {
    static int n;
    static lli ans;
    static std::multiset<int>::iterator it;
    scanf("%d",&n);
    for(int i=1,a,o,b;i<=n;i++) scanf("%d%d%d",&o,&a,&b) , ms.insert(o) , in[i] = (Node){a,b} , ans += (lli) a * b;
    std::sort(in+1,in+1+n);
    for(int i=1;i<=n;i++) if( ( it = ms.lower_bound(in[i].i) ) != ms.begin() ) ans -= (lli)*--it*in[i].b , ms.erase(it);
    return !printf("%lld\n",ans);
}
