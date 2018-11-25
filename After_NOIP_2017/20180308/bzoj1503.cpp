#include<cstdio>
#include<algorithm>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long int lli;
#ifdef ONLINE_JUDGE
typedef tree<lli,null_mapped_type,greater<lli>,rb_tree_tag,tree_order_statistics_node_update> Tree;
#else
typedef tree<lli,null_type,greater<lli>,rb_tree_tag,tree_order_statistics_node_update> Tree;
#endif
Tree tr,tr_t;

int main() {
    static lli add,sum,miv,k;
    int n;
    static char o[10];
    scanf("%d%lld",&n,&miv);
    for(int i=1;i<=n;i++) {
        scanf("%s%lld",o,&k);
        if( *o == 'I' ) {
            if( k >= miv ) tr.insert(((k-add)<<20)+i);
        } else if( *o == 'A' ) {
            add += k;
        } else if( *o == 'S' ) {
            add -= k;
            lli low = miv - add;
            tr.split(low<<20,tr_t);
            sum += tr_t.size();
        } else {
            if( tr.size() < k ) puts("-1");
            else printf("%lld\n",((*tr.find_by_order(k-1))>>20)+add);
        }
    }
    printf("%lld\n",sum);
    return 0;
}
