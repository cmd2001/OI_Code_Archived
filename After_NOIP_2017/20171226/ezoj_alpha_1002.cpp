#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const lli inf=0x7fffffffffffffff;

lli ans,x;

inline int count(lli x) {
    int ret = 0;
    while(x)
        ret += x % 10 ,
        x /= 10;
    return ret;
}

int main() {
    static int n;
    scanf("%d",&n);
    while( n-- ) {
        scanf("%lld",&x);
        ans = inf;
        for(int i=0;i<=18*9;i++)
            if( count(x-i) == i )
                ans = min( ans , x-i );
        if( ans != inf )
            printf("%lld\n",ans);
        else
            puts("Stupid SiriusRen");
    }
    
    return 0;
}