#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=2e6+1e2;

int que[maxn],st=1,ed;
int n,d,ans;
lli in[maxn],p;

int main() {
    scanf("%d%lld%d",&n,&p,&d) , ans = d;
    for(int i=1;i<=n;i++) scanf("%lld",in+i) , in[i] += in[i-1];
    for(int i=d,j=0;i<=n;i++) {
        while( st <= ed && in[que[ed]] - in[que[ed]-d] <= in[i] - in[i-d] ) --ed;
        que[++ed] = i;
        while( j < i && in[i] - in[j] - ( in[que[st]] - in[que[st]-d] ) > p ) {
            ++j;
            if( que[st] - d < j ) ++st;
        }
        ans = max( ans , i - j );
    }
    printf("%d\n",ans);
    return 0;
}