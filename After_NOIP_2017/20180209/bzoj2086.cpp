#include<cstdio>
#define max(a,b) ( (a) > (b) ? (a) : (b) )
#define lli long long int
const int maxn=1e6+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

lli in[maxn],s[maxn];
int stk[maxn],top;

int main() {
    static int n,m,ans;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",in+i);
    for(int i=1,k;i<=m;i++) {
        scanf("%d",&k) , top = ans = 0;
        for(int i=1;i<=n;i++) s[i] = in[i] - k;
        for(int i=1;i<=n;i++) s[i] += s[i-1];
        for(int i=1;i<=n;i++) if( s[stk[top]] > s[i] ) stk[++top] = i;
        for(int i=n;i;i--) {
            while( top && s[i] - s[stk[top-1]] >= 0 ) --top;
            ans = max( ans , i - stk[top] );
        }
        printf("%d%c",ans,i!=m?' ':'\n');
    }
    return 0;
}
