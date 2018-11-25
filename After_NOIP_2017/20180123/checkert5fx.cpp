#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int in[maxn],sum[maxn];
int n,m;

inline bool check(int x) {
    int ret = 0 , last = 0;
    for(int i=1;i<=n;i++) {
        if( sum[i+1] - sum[last] > x ) {
            last = i , ++ret;
        }
    }
    if( last != n ) ++ret;
    return ret <= m;
}

inline int bin() {
    int l = 0 ,r = 2e9 , mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( check(mid) ) r = mid;
        else l = mid;
    }
    return r;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i) , sum[i] = sum[i-1] + in[i];
    printf("%d\n",bin());
    return 0;
}