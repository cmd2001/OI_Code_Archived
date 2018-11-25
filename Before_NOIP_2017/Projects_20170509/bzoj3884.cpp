#include<bits/stdc++.h>
#define debug cout
using namespace std;
map<int,int> mem;
int fastpow(int x,int tme,int mod)
{
    int ret=1,now=x%mod;
    while(tme)
    {
        if(tme&1) ret=(long long int)ret*now%mod;
        now=(long long int)now*now%mod;
        tme>>=1;
    }
    return ret%mod;
}
int phi(int x)
{
    if(!x) return 0;
    if(x==1) return 1;
    int ret=x;
    for(int i=2;i*i<=x;i++) // Don;t write i<=x
    {
        if(!(x%i)) ret/=i,ret*=(i-1);
        while(!(x%i)) x/=i;
    }
    if(x>1) ret/=x,ret*=(x-1);
    return ret;
}
int calc(int x)
{
    if(mem.count(x)) return mem[x];
    int ph=phi(x);
    return mem[x]=fastpow(2,calc(ph)+ph,x);
}
int main()
{
    int t,x;
    mem[1]=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&x);
        printf("%d\n",calc(x));
    }
    return 0;
}




