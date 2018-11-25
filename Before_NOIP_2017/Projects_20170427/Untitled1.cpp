#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int lst[15]={0,2,3,5,7,11,13,17,19,23,29,31,61,24251},pn=13;
int fast_pow(int x,int t,int mod)
{
    int ret=1,now=x%mod;
    while(t)
    {
        if(t&1) ret=((long long)ret*now)%mod;
        now=((long long)now*now)%mod;
        t>>=1;
    }
    return ret;
}
bool test(int a,long long int n)
{
    int tme=n-1,cnt=0;
    while(!(tme&1)) tme>>=1,++cnt;
    int tmp=fast_pow(a,tme,n);
    if(tmp==1||tmp==n-1) return 1;
    while(cnt--)
    {
        tmp=((long long)tmp*tmp)%n;
        if(tmp==n-1) return 1;
    }
    return 0;
}
bool miller(long long n)
{
    if(n==1) return 0;
    for(int i=1;i<=pn;i++) if(n==lst[i]) return 1;
    for(int i=1;i<=pn;i++) if(!(n%lst[i])) return 0;
    for(int i=1;i<=pn;i++)
    {
        if(!test(lst[i],n)) return 0;
    }
    return 1;
}
int main()
{
    long long int n;
    scanf("%lld",&n);
    if(miller(n)) puts("prime");
    else puts("composite");
    return 0;
}



