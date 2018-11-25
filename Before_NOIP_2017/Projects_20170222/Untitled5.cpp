#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3;
int in[maxn],n,ans;
int cnt(int x)
{
    int ret=0;
    while(x)
    {
        ++ret;
        x&=(x-1);
    }
    return ret;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>*(in+i);
    for(int at=31;at>=0;at--)
    {
        for(int j=1;j<=n;j++)
        {
            if(in[j]&(1<<at))
            {
                for(int i=1;i<=n;i++)
                {
                    if(in[i]&(1<<at)&&i!=j)
                    {
                        in[i]^=in[j];
                    }
                }
                if(!(ans&(1<<at))) ans^=in[j];
                in[j]=0;
            }
        }
    }
    cout<<ans<<'\n'<<cnt(ans)<<endl;
    return 0;
}
