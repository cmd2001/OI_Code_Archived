#include<cstdio>
const int maxn=1e5+1e2;

int sum[maxn],mx;
int n,m;

inline bool judge(int x) { // assert x >= max( sum[i+1] - sum[i] ) .
    int ret = 0 , last = 0;
    for(int i=1;i<=n;i++) if( sum[i+1] - sum[last] > x ) last = i , ++ret;
    ret += ( last != n );
    return ret <= m;
}
inline int bin() {
    if( judge(mx) ) return mx;
    int l = mx , r = 2e9 , mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( judge(mid) ) r = mid;
        else l = mid;
    }
    return r;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1,p;i<=n;i++) {
        scanf("%d",&p);
        sum[i] = sum[i-1] + p , mx = p > mx ? p : mx;
    }
    printf("%d\n",bin());
    return 0;
}
