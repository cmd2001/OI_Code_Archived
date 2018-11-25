#include<cstdio>
#include<algorithm>
const int maxn=1e6+1e2;

int in[maxn],f[maxn],n,mx;

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    std::sort(in+1,in+1+n);
    for(int i=1;i<=n;i++) {
        mx = std::max( mx , in[i] - f[i-1] ) , f[i] = mx;
    }
    printf("%d\n",f[n]);
    return 0;
}
