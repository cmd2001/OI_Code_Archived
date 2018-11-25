#include<cstdio>
typedef unsigned int uint;
typedef unsigned long long int ulli;
const int maxn=1e3+1e2;

ulli d[maxn],w[maxn],k;
uint n;

inline bool judge(uint l,uint r) {
    static ulli delta[maxn];
    for(uint i=l;i<=r;i++) delta[i] = 0;
    ulli sud = 0 , suw = 0 , used = 0;
    for(uint i=l;i<r;i++) {
        sud += d[i] , suw += w[i];
        if( suw < sud ) delta[i] = sud - suw;
        used += delta[i] , suw += delta[i];
    }
    if( used > k ) return 0;
    delta[r] = k - used;
    sud = suw = 0;
    for(uint i=r;i>l;i--) {
        sud += d[i-1] , suw += w[i] + delta[i];
        if( suw < sud ) return 0;
    }
    return 1;
}

int main() {
    scanf("%u%llu",&n,&k);
    for(uint i=1;i<n;i++) scanf("%llu",d+i);
    for(uint i=1;i<=n;i++) scanf("%llu",w+i);
    for(uint i=1;i<=n;i++) for(uint j=n;j>=i;j--) if( judge(i,j) ) { printf("%d%c",j,i!=n?' ':'\n'); break; }
    return 0;
}
