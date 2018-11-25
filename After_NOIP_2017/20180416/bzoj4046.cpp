#include<cstdio>
#include<cctype>
#include<algorithm>
typedef long long int lli;
const int maxn=2e6+1e2;

int cnt[maxn],mx;
lli ans;

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int n,t;
    n = getint();
    while(n--) mx = std::max( mx , t = getint() ) , ++cnt[t];
    for(int i=1;i<=mx;i++) {
        ans -= cnt[i];
        for(int j=i;j<=mx;j+=i) ans += (lli) cnt[i] * cnt[j];
    }
    printf("%lld\n",ans);
    return 0;
}
