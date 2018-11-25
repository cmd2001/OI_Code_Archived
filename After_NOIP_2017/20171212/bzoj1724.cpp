#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
using namespace std;

int n,x;
multiset<int> ms;
long long int ans;

int main()
{
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        ms.insert(x);
    }
    
    for(int i=1;i<n;i++)
    {
        x = *ms.begin();
        ms.erase(ms.begin());
        x += *ms.begin();
        ms.erase(ms.begin());
        ans += x;
        ms.insert(x);
    }
    
    printf("%lld\n",ans);
    
    return 0;
}