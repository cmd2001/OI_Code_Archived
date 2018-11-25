#include<cstdio>
#include<algorithm>
#include<cstdlib>
typedef long long int lli;
const int maxn=1e5+1e2;

lli in[maxn],pos,neg;
int n;

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",in+i);
    for(int i=n;i>1;i--) {
        in[i] -= in[i-1];
        if( in[i] > 0 ) pos += in[i];
        else neg -= in[i];
    }
    printf("%lld\n%lld\n",std::max(pos,neg),std::abs(pos-neg)+1);
    return 0; 
}