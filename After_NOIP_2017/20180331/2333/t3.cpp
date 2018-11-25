#include<bits/stdc++.h>
typedef long long int lli;
using namespace std;

inline lli f(lli x) {
    if( x <= 1 ) return x;
    return ( ( x + 1 ) >> 1 ) + f( x >> 2 );
}

int main() {
    static lli n;
    scanf("%lld",&n) , printf("%lld\n",f(n));
    return 0;
}