#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e4+1e2;
long long int siz[maxn];
inline void getans(int x)
{
    for(int i=2,t;i<=x;i++)
    {
        t=i;
        for(int j=2;j<=i;j++)
        {
            while(!(t%j)) t/=j,siz[j]++;
        }
    }
}
int main()
{
    static int x;
    scanf("%d",&x);
    getans(x);
    for(int i=1;i<=x;i++) if(siz[i]) printf("%lld ",siz[i]);
    return 0;
}

