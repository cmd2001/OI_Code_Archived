#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2,lim=1e5,blk=1e3;
const int inf=0x3f3f3f3f , minf = -inf;
const lli lli_inf = 0x3f3f3f3f3f3f3f3fll;

int in[maxn],n,k;

namespace Force {
    int s[maxn];
    inline void work() {
        lli ans = -lli_inf;
        memset(s,0x3f,sizeof(s));
        for(int i=n;i;i--) {
            for(int j=i+1;j<=n/*&&j<=i+blk*/;j++) {
                s[j] = min( s[j] , abs(in[i]-in[j]) ) , s[j] = min( s[j] , s[j-1] );
                if( j - i >= k )ans = max( ans , (lli) s[j] * ( j - i ) );
                if( (lli) s[j] * ( n - i ) <= ans ) break;
            }
        }
        printf("%lld\n",ans);
    }
}

int main() {
    static int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&k) , --k;
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        Force::work();
    }
}
