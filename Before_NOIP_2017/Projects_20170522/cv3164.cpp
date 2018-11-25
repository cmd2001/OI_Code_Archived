#include<bits/stdc++.h>
using namespace std;
int t,cnt;
long long int in;
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
long long int lli_abs(long long int x)
{
    return x>0?x:-x;
}
long long int lli_rand()
{
    long long int ret=rand();
    ret|=rand()<<15;
    ret|=rand()<<30;
    return ret|=rand()<<45;
}
long long int gcd(long long int a,long long int b)
{
    return a%b==0?b:gcd(b,a%b);
}
long long int nxtr(long long int a,long long int mod)
{
    return (a*a%mod+1)%mod;
}
void pollard(long long int x)
{
    if(x==1) return;
    if(miller(x))
    {
        ++cnt;
        return;
    }
    long long int t=lli_rand(),a=nxtr(t,x),b=nxtr(a,x);
    while(1)
    {
        t=gcd(lli_abs(a-b),x);
        if(t!=1&&t!=x) break;
        a=nxtr(a,x);
        b=nxtr(b,x);
        b=nxtr(b,x);
        if(a==b)
        {
            a=lli_rand()%x+1;
            b=lli_rand()%x+1;
        }
    }
    pollard(t);
    pollard(x/t);
}
int main()
{
    srand(time(NULL));
    scanf("%d",&t);
    while(t--)
    {
        cnt=0;
        scanf("%lld",&in);
        pollard(in);
        printf("%d\n",cnt);
    }
    return 0;
}


