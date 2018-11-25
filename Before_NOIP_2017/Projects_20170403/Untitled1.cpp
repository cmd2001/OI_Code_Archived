#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=3*1e7;
unsigned long long int prime[2831500];
int cnt,cntans;
bool vis[maxn];
long long int x,ans;
void getprime()
{
    for(int i=2;i<maxn&&cnt<maxn;i++)
    {
        if(!vis[i]) {prime[++cnt]=i;}
        for(int j=1;j<=cnt&&i*prime[j]<maxn;j++)
        {
            vis[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}
void calc(long long int x)
{
    ans=x;
    if(x==1) return;
    for(int i=1;i<=cnt;i++)
    {
        //debug<<"i="<<i<<endl;
        //debug<<prime[i]<<endl;
        if(x%prime[i]==0)
        {
            ans/=prime[i];ans*=prime[i]-1;
            while(x%prime[i]==0) x/=prime[i];
            if(x==1) break;
        }
    }
    if(x!=1) ans/=x,ans*=x-1;
    return;
}
int main()
{
    freopen("wa.txt","w",stdout);
    int t;
    getprime();
    debug<<"prime got"<<endl;
    debug<<"cnt="<<cnt<<endl;
    debug<<"max_prime="<<prime[cnt]<<endl;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld",&x);
        //debug<<"x="<<x<<endl;
        calc(x);
        printf("%lld\n",ans);
    }
    return 0;
}
