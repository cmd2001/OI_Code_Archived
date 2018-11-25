#include<cstdio>
#include<cctype>
using namespace std;
const int maxn=1e3+1e2;

int in[maxn],cnt[maxn];
int n;
long double ans;

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n = getint();
    for(int i=1;i<=n;i++)
        ++cnt[in[i]=getint()];
    for(int i=1;i<=1000;i++)
        cnt[i] += cnt[i-1];
    for(int i=1;i<=n;i++)
        ans += ( n + 1.0 ) / ( n + 1.0 - cnt[in[i]-1] );
    
    printf("%0.2Lf\n",ans);
    
    return 0;
}