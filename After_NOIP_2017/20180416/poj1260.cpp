#include<cstdio>
#include<algorithm>
const int maxn=1e2+1e1;
const int inf=0x3f3f3f3f;

int f[maxn],cst[maxn],su[maxn],n;

int main() {
    static int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d%d",su+i,cst+i) , su[i] += su[i-1];
        for(int i=1;i<=n;i++) {
            f[i] = inf;
            for(int j=0;j<i;j++) f[i] = std::min( f[i] , f[j] + cst[i] * ( su[i] - su[j] + 10 ) );
        }
        printf("%d\n",f[n]);
    }
}
