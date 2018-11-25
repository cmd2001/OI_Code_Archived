#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

lli n ,lam;
int in[maxn];

inline lli count(int x) {
    lli ret = 0;
    int l = 1 ;
    for(int r=2;r<=n;r++) {
        while( in[r] - in[l] >= x )
            l++;
        ret += r - l;
    }
    return ret;
}
inline int getans() {
    int l = 0 , r = 1000000001 , mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( count(mid) <= lam )
            l = mid;
        else
            r = mid;
    }
    return l;
}

int main() {
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    sort(in+1,in+1+n);
    lam = n * ( n - 1 ) >> 1;
    if( lam & 1 )
        lam >>= 1;
    else lam >>= 1 , lam --;
    //debug<<"sorted"<<endl;
    
    printf("%d\n",getans());
    
    return 0;
}