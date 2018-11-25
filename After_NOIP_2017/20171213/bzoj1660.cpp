#include<cstdio>
using namespace std;
const int maxn=8e4+1e2;

int stk[maxn],top;
int n;
long long ans;

int main()
{
    scanf("%d",&n);
    
    for(int i=1,x;i<=n;i++)
    {
        scanf("%d",&x);
        while( top && stk[top] <= x )
            --top;
        ans += top;
        stk[++top] = x;
    }
    
    printf("%lld\n",ans);
    
    return 0;
}