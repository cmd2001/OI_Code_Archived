#include<cstdio>
#include<algorithm>
const int maxn=3e2+1e1;

int main() {
    static int in[maxn],n,k,l,r,ans;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++) scanf("%d",in+i);
    std::sort(in+1,in+1+k) , l = 1 , r = n;
    for(int i=k;i&&r>l;i--,l++,r--) ans += in[i] * ( r - l );
    printf("%d\n",ans);
    return 0;
}
