#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int lst[15]={0,2,3,5,7,11,13,17,19,23,29,31,61,24251},pn=13;
long long int multi(long long int a,long long int b,long long int m)
{
    long long int d=((long double)a*b/m+0.5);
    long long int ret=a*b-d*m;
    if(ret<0) ret+=m;
    return ret;
}
long long fast_pow(long long x,long long t,long long mod)
{
    long long ret=1,now=x%mod;
    while(t)
    {
        if(t&1) ret=multi(ret,now,mod);
        now=multi(now,now,mod);
        t>>=1;
    }
    return ret;
}
bool judge(long long int n,int b)
{

    return fast_pow(b,n-1,n)==1;
}
bool calc(long long int a)
{
    if(a==1) return 0;
    for(int i=1;i<=pn&&a>lst[i];i++)
    {
        if(a==lst[i]) return 1;
        if(!judge(a,lst[i])) return 0;
    }
    return 1;
}
int main()
{
    long long int n;
    scanf("%lld",&n);
    if(calc(n)) puts("Yes");
    else puts("No");
    return 0;
}

