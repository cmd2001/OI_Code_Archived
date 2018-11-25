#include<cstdio>
#include<cmath>
typedef long double ldb;
using namespace std;
const int maxn=1e5+1e2,lim=1e5;
const ldb e = exp(1);

ldb f[maxn];

inline void work() {
    f[lim] = ( 1 / ( lim + 1 ) + 1 / ( ( lim + 1 ) * e ) ) / 2.0;
    for(int i=lim;i;i--) f[i-1] = ( 1 - f[i] ) / i;
}

int main() {
    static int n;
    scanf("%d",&n) , work() , printf("%0.4Lf\n",f[n]);
    return 0;
}
