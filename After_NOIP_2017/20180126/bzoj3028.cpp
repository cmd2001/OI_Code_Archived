#include<cstdio>
#include<cctype>
#define lli long long int
#define debug cout
using namespace std;
const int mod=10007,inv=1668;

inline lli getint() {
    lli ret = 0;
    char ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0',ret%=mod; while( isdigit(ch=getchar()) );
    return ret;
    
}
int main() {
    lli n,ans;
    n = getint();
    ans = n * ( n + 1 ) % mod * ( n + 2 ) % mod * inv % mod;
    printf("%lld\n",ans);
    return 0;
}
