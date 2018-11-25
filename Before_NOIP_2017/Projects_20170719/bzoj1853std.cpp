#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 10010
using namespace std;
typedef long long ll;
ll l,r;
int cnt;
int n;
ll lucky[N];
bool ban[N];
ll ans;
ll gcd(ll a,ll b)
{
    while(b)
    {
        ll t=b;
        b=a%b;
        a=t;
    }
    return a;
}
ll lcm(ll a,ll b)
{
    return a/gcd(a,b)*b; 
}
void init(ll num)
{
    if(num>r)return;
    lucky[cnt++]=num;
    init(num*10+6);
    init(num*10+8);
}
void dfs(int now,int chose,ll val)
{
    if(now>n)
    {
        if(!chose)return;
        if(chose&1)ans+=r/val-(l-1)/val;
        else ans-=r/val-(l-1)/val;
        return;
    }
    dfs(now+1,chose,val);
    ll tmp=val/gcd(lucky[now],val);
    if((double)tmp*lucky[now]<=r)
    {
        dfs(now+1,chose+1,tmp*lucky[now]);
    }
}
int main()
{
    scanf("%lld%lld",&l,&r);
    init(0);
    cnt--;
    sort(lucky+1,lucky+cnt+1);
    for(int i=1;i<=cnt;i++)
    {
        if(!ban[i])
        {
            for(int j=i+1;j<=cnt;j++)
            {
                if(lucky[j]%lucky[i]==0)
                {
                    ban[j]=1;
                }
            }
        }
    }
    for(int i=1;i<=cnt;i++)
        if(!ban[i])lucky[++n]=lucky[i];
    for(int i=1;i<=(n>>1);i++)swap(lucky[i],lucky[n-i+1]);
    dfs(1,0,1);
    printf("%lld\n",ans);
}
