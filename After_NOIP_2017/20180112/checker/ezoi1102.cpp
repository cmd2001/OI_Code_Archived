#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e3+1e2,maxm=2e5+1e2;
const int mod=1000000;

lli sum[maxm],f[maxm];
int in[maxm];
int t,n,L,R;

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    t = getint() , n = getint() , L = getint() , R = getint();
    //debug<<"L = "<<L<<"R = "<<R<<endl;
    while(n--) ++in[getint()];
    
    for(int i=0;i<=R;i++)
        sum[i] = 1;
    for(int i=1;i<=t;i++) {
        for(int j=R;j;j--) {
            f[j] = sum[j] - ( j - in[i] - 1>= 0 ? sum[j-in[i]-1] : 0 );
        }
        for(int j=1;j<=R;j++)
            sum[j] = ( sum[j-1] + f[j] ) % mod;
    }
    
    printf("%lld\n",((sum[R]-sum[L-1])%mod+mod)%mod);
    return 0;
}