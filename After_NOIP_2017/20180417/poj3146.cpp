#include<cstdio>
const int mod=10000;

int main() {
    static int n,p,cse,ans;
    while( scanf("%d%d",&p,&n) == 2 && ( n || p ) ) {
        ans = 1 , ++cse;
        while( n ) ans = ans * ( n % p + 1 ) % mod , n /= p;
        printf("Case %d: %04d\n",cse,ans);
    }
    return 0;
}
