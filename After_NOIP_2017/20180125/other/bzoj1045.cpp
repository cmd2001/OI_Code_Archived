#include<cstdio>
#include<algorithm>
#define lli long long int
#define abs(x) ( x > 0 ? x : -(x) )
const int maxn=1e6+1e2;

lli in[maxn],avr,ans;
int n,mid;

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",in+i) , avr += in[i];
    avr /= n;
    for(int i=1;i<=n;i++)
        in[i] += in[i-1] - avr;
    std::sort(in+1,in+1+n);
    mid = ( n >> 1 ) + 1;
    for(int i=1;i<=n;i++)
        ans += abs( in[i] - in[mid] );
    printf("%lld\n",ans);
    return 0;
}
