#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=2.5e5+1e2;

lli in[maxn],n,lst,ans;
int len;

inline bool check(lli x) {
    for(int i=1;i<=len;i++) if( ! ( in[i] % x ) ) return 0;
    return 1;
}
inline lli gcd(lli x,lli y) {
    if( ! ( x && y ) ) return x | y;
    register lli t;
    while( t = x % y ) x = y , y = t;
    return y;
}
inline void getans() {
    for(lli i=1;i*i<=lst;i++) if( ! ( lst % i ) ) {
        if( check(i) ) return void(ans=n/i);
        else if( check(lst/i) ) ans = n / ( lst / i );
    }
}

int main() {
    scanf("%lld%d",&n,&len) , --len;
    for(int i=1;i<=len;i++) scanf("%lld",in+i) , in[i] = gcd(in[i],n);
    scanf("%lld",&lst) , lst = gcd(lst,n);
    std::sort(in+1,in+1+len) , len = std::unique(in+1,in+1+len) - in - 1;
    getans() , printf("%lld\n",ans);
    return 0;
}
