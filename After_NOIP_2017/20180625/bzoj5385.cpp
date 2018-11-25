#include<cstdio>
typedef long long int lli;
const int maxn=62;

lli f[maxn],p;
int t,k;

int main() {
    f[1] = 1; for(int i=2;i<=60;i++) f[i] = ( f[i-1] << 1 ) | 1;
    scanf("%d",&t);
    while(t--) {
        scanf("%d%lld",&k,&p);
        while( f[k-1] >= p ) --k;
        if( p == f[k-1] + 1 ) puts("0");
        else printf("%lld\n",p-f[k-1]-1);
    }
    return 0;
}
