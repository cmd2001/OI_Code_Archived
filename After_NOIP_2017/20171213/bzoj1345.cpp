#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

lli stk[maxn];
lli ans,x;
int n,top;

inline void push(lli x)
{
    while( top && x >= stk[top] )
    {
        if( top == 1 )
            ans += x;
        else ans += min( x , stk[top-1] );
        top--;
    }
    stk[++top] = x;
}

int main()
{
    scanf("%d",&n);
    
    while( n-- )
    {
        scanf("%lld",&x);
        push(x);
    }
    for(int i=1;i<top;i++)
        ans += stk[i];
    
    printf("%lld\n",ans);
    
    return 0;
}
