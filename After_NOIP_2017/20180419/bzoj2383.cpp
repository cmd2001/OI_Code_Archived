#include<cstdio>
#include<algorithm>
typedef long double ldb;
const int maxn=2e5+1e2;

ldb x[maxn],r[maxn];
int stk[maxn],top,n;

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%Lf%Lf",x+i,r+i);
        while( top ) {
            const int t = stk[top];
            r[i] = std::min( r[i] , ( x[t] - x[i] ) * ( x[t] - x[i] ) / 4 / r[t] );
            if( r[i] > r[t] ) --top;
            else break;
        }
        stk[++top] = i , printf("%0.3Lf\n",r[i]);
    }
    return 0;
}
