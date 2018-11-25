#include<cstdio>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=1e5+1e2;

int f[maxn],s[maxn];
lli m;
int n;

inline bool judge(int t) {
    lli mx = -1 , now = 0;
    for(int i=1;i<=n;i++) {
        if( s[i] > t ) {
            mx = max( mx , now );
            now = 0;
        } else now += f[i];
    }
    mx = max( mx , now );
    return mx >= m;
}

inline int bin() {
    int l = 0 , r = 1e9 , mid;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( judge(mid) ) r = mid;
        else l = mid;
    }
    return r;
}

int main() {
    scanf("%d%lld",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d",f+i,s+i);
    
    printf("%d\n",bin());
    return 0;
}
