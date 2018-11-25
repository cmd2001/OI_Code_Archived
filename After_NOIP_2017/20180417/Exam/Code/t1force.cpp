#include<bits/stdc++.h>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=5e3+1e2;

lli t,c[maxn][maxn],ans;
int n,mod;

inline void pre() {
    c[0][0] = 1 % mod;
    for(int i=1;i<=n;i++) {
        c[i][0] = 1 % mod;
        for(int j=1;j<=i;j++)
            c[i][j] = ( c[i-1][j] + c[i-1][j-1] ) % mod;
    }
    /*for(int i=0;i<=n;i++) {
        for(int j=0;j<=i;j++) debug<<c[i][j]<<" "; debug<<endl;
    }*/
    //for(int i=0;i<n;i++) debug<<c[n-1][i]<<" "; debug<<endl;
}

int main() {
    scanf("%d%d",&n,&mod) , pre();
    for(int i=1;i<=n;i++) scanf("%lld",&t) , ( ans += t * c[n-1][i-1] % mod ) %= mod;
    printf("%lld\n",ans);
    return 0;
}
