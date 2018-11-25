#pragma GCC optimize("Ofast")
#include<cstdio>
typedef long long int lli;
const int maxn=5e7+1e2;
const int mod=998244353;

int su[maxn],n,s;
lli ans;

inline int calc(int x) {
    int ret = 0;
    while(x) ret += x % 10 , x /= 10;
    return ret;
}

int main() {
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    scanf("%d%d",&n,&s);
    for(int i=1;i<=n;i++) su[i] = su[i-1] + calc(i);
    for(int l=0,r=0;l<=n;l++) {
        while( r < n && su[r+1] - ( l ? su[l-1] : 0 ) <= s ) ++r;
        ans += r - l + 1;
    }
    printf("%lld\n",ans%mod);
    fclose(stdout);
    return 0;
}
