#include<cstdio>
#include<cmath>
typedef long double ldb;
const int maxn=1e4+1e2;
const ldb e = exp(1);

ldb f[maxn];

int main() {
    static int n;
    freopen("homework.in","r",stdin);
    freopen("homework.out","w",stdout);
    scanf("%d",&n) , *f = 1 - 1 / e;
    for(int i=1;i<=n;i++) f[i] = 1 - i * f[i-1];
    printf("%0.4Lf\n",120/e-44);
    printf("%0.4Lf\n",f[n]);
    return fclose(stdout);
}
