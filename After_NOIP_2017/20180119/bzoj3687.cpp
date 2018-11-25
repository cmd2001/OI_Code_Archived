#include<cstdio>
#include<bitset>
using namespace std;
const int maxl=2e6+1e2,lim=2e6;

bitset<maxl> f;

int main() {
    static int n;
    static long long ans;
    scanf("%d",&n);
    f[0] = 1;
    for(int i=1,x;i<=n;i++) {
        scanf("%d",x);
        f = f ^ ( f << x );
    }
    for(int i=1;i<=lim;i++)
        if( f[i] ) ans ^= i;
    printf("%lld\n",ans);
    return 0;
}