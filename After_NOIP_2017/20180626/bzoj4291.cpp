#include<cstdio>
#include<algorithm>
const int inf=0x3f3f3f3f;

int n,su,mi=inf;

int main() {
    scanf("%d",&n);
    if( n == 1 ) {
        int x;
        scanf("%d",&x);
        if( x & 1 ) puts("NIESTETY");
        else printf("%d\n",x);
    } else {
        while(n--) {
            int x;
            scanf("%d",&x) , su += x;
            if( x & 1 ) mi = std::min( mi , x );
        }
        if( su & 1 ) su -= mi;
        printf("%d\n",su);
    }
    return 0;
}
