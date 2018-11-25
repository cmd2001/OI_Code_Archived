#include <bits/stdc++.h>
using namespace std;
const int maxn=5000005;
const int mod=1e9+7;
int pri[maxn],fi[maxn],t;
bool flag[maxn];
long long sumfi[maxn];
long long mod2,mod3,mod6,mod12,mod30;
long long fast(long long num,int ci)
{
    long long ans=1;
    while(ci)
    {
        if(ci&1) ans=ans*num%mod;
        num=num*num%mod;ci=ci>>1;
    }
    return ans;
}
map<long long ,long long>mp;
void pre()
{
    t=0;memset(flag,0,sizeof(flag));
    fi[1]=1;
    for(int i=2;i<maxn;i++)
    {
        if(!flag[i]){
            pri[t++]=i;fi[i]=i-1;
        }
        for(int j=0;j<t&&pri[j]*i<maxn;j++)
        {
            flag[pri[j]*i]=1;
            if(i%pri[j]==0){
                fi[i*pri[j]]=fi[i]*pri[j];
                break;
            }
            fi[i*pri[j]]=fi[i]*(pri[j]-1);
        }
    }
    for(int i=1;i<maxn;i++)
    {
        sumfi[i]=sumfi[i-1]+fi[i];
        if(sumfi[i]>=mod) sumfi[i]-=mod;
    }
    mod2=fast(2,mod-2);
    mod3=fast(3,mod-2);
    mod6=fast(6,mod-2);
    mod12=fast(12,mod-2);
    mod30=fast(30,mod-2);
    mp.clear();
}

long long gett(long long n,int k)
{
    n%=mod;
    if(k==1)
        return n*(n+1)/2%mod;
    if(k==2)
        return n*(n+1)%mod*(2*n+1)%mod*mod6%mod;
    if(k==3){
        long long t=n*(n+1)/2%mod;;
        return t*t%mod;
    }
    if(k==4){
        return n*(n+1)%mod*(2*n+1)%mod*((3*n*n%mod+3*n-1)%mod)%mod*mod30%mod;
    }
    if(k==5){
        long long t=n*(n+1)%mod;
        t=t*t%mod;
        t=t*((2*n*n%mod+2*n-1)%mod)%mod;
        t=t*mod12%mod;
        return t;
    }
}
long long solve(long long u)
{
    if(u<maxn){
        return sumfi[u];
    }
    if(mp[u]) return mp[u];
    long long tmp=u%mod;
    long long ans=tmp*(tmp+1)/2%mod;
    for(long long i=2,j;i<=u;i=j+1)
    {
        j=u/(u/i);
        ans=(ans-solve(u/i)*(j-i+1))%mod;
    }
    ans%=mod;
    if(ans<0) ans+=mod;
    mp[u]=ans;
    return ans;
}

int main()
{
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
    pre();
    long long n;
    int k;
    scanf("%lld%d",&n,&k);
    long long ans=0;
    for(long long i=1,j;i<=n;i=j+1)
    {
        j=n/(n/i);
        ans=(ans+solve(n/i)*(gett(j,k)-gett(i-1,k)))%mod;
    }
    ans=ans*2;
    ans=ans-gett(n,k);
    ans%=mod;
    if(ans<0) ans+=mod;
    printf("%lld\n",ans);
    return 0;
}
