#include<cstdio>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=5e4+1e2;

lli sum[maxn];

int main() {
    static int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%lld",sum+i) , sum[i] += sum[i-1];
    for(int i=1,ans,p;i<=q;i++) {
        scanf("%d",&p);
        ans = lower_bound(sum+1,sum+1+n,p)-sum;
        if( sum[ans] == p ) ++ans;
        printf("%d\n",ans);
    }
    return 0;
}
