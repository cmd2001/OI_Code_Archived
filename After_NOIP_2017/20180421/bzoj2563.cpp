#include<cstdio>
#include<algorithm>
const int maxn=1e4+1e2;

int in[maxn],n,m,ans;

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , ans -= in[i] , in[i] <<= 1;
    for(int i=1,a,b,v;i<=m;i++) scanf("%d%d%d",&a,&b,&v) , ans -= v , in[a] += v , in[b] += v;
    std::sort(in+1,in+1+n);
    for(int i=2;i<=n;i+=2) ans += in[i];
    printf("%d\n",ans);
    return 0;
}
