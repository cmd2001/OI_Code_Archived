#include<cstdio>
typedef long long int lli;
const int maxn=1e2+1e1;

lli fib[maxn],n,ans;
int cnt;

int main() {
    scanf("%lld",&n);
    fib[1] = fib[cnt=2] = 1;
    while( fib[cnt] < n ) ++cnt , fib[cnt] = fib[cnt-2] + fib[cnt-1];
    for(int i=cnt;i;i--) if( n >= fib[i] ) n -= fib[i] , ans = fib[i];
    printf("%lld\n",ans);
    return 0;
}

