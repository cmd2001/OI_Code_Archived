#include<cstdio>
#include<algorithm>
const int maxn=1.2e6+1e2;

int in[maxn],sta[maxn],n,cnt,mod,ans;

int main() {
    scanf("%d%d%d",in+1,&mod,&n) , n <<= 2;
    if( mod == 1 ) return puts("1"),0;
    for(int i=2;i<=n;i++) {
        in[i] = ( in[i-2] + in[i-1] ) % mod;
        if( i > 6 && ( i & 1 ) ) sta[++cnt] = (long long) in[i] * in[1] % mod;
    }
    std::sort(sta+1,sta+1+cnt);
    for(int i=1;i<=cnt;i++) if( sta[i] != sta[i-1] || i == 1 ) ++ans;
    printf("%d\n",ans%mod);
    return 0;
}
