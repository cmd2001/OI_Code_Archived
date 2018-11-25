#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
const int maxn=2.5e3+1e2;

lli f[maxn],s[maxn];

int main() {
    static int n;
    scanf("%d%lld",&n,s);
    for(int i=1;i<=n;i++) scanf("%lld",s+i) , s[i] += s[i-1];
    memset(f,0x3f,sizeof(f)) , *f = 0;
    for(int i=1;i<=n;i++) for(int j=0;j<i;j++) f[i] = std::min(f[i],f[j]+s[i-j]+s[0]);
    printf("%lld\n",f[n]-s[0]);
    return 0;
}
