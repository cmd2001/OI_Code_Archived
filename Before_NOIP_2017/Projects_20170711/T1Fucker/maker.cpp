#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+1e2;

int delta[maxn],sum[maxn];
int ans;
int main()
{
    srand(time(NULL));
    int n=rand()%10000+1;
    for(int i=2;i<=n;i++)
    {
        delta[i]=(rand()&1)?-1:1;
    }
    for(int i=1;i<=n;i++)
    {
        sum[i]=sum[i-1]+delta[i];
    }
    for(int i=1;i<=n;i++) ans+=sum[i];
    cout<<n<<endl<<ans<<endl;
    return 0;
}

