#include<bits/stdc++.h>
#define lli long long int
using namespace std;
const int mod=1e9+7;

int n,k;
inline lli slowpow(register lli base) {
    lli ret = 1;
    for(int i=1;i<=k;i++)
        ret = ret * base % mod;
    return ret;
    
}

int main() {
    lli ans = 0;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            ans = ( ans + slowpow(__gcd(i,j) ) ) % mod;
    printf("%lld\n",ans);
    return 0;
}