#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=55;

lli in[maxn];
int n,m;

inline bool judge(lli x) {
    lli tar = x * n - min( x , (lli) m ) , sum = 0;
    for(int i=1;i<=n;i++)
        sum += min( x , in[i] );
    return sum >= tar;
}
inline int bin() {
    int l = 0 , r = 1e9 , mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( judge(mid) ) l = mid;
        else r = mid;
    }
    return l;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lld",in+i);
    printf("%d\n",bin());
    return 0;
}
