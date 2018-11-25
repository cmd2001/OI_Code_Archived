#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define lli long long int
using namespace std;

inline bool judge(int x)
{
    if(x==0||x==1) return 0;
    int sq=sqrt(x);
    for(int i=2;i<=sq;i++) if(!(x%i)) return 0;
    return 1;
}

inline int fastpow(int base,int tme,int mod)
{
    lli ret=1,now=base%mod;
    while(tme)
    {
        if(tme&1)
        {
            ret*=now;
            if(ret>=mod) ret%=mod;
        }
        now*=now;
        if(now>=mod) now%=mod;
        tme>>=1;
    }
    ret%=mod;
    return ret;
}

int main()
{
    static int a,p;
    while(scanf("%d%d",&p,&a)==2&&(p||a))
    {
        if(judge(p))
        {
            puts("no");
            continue;
        }
        if(fastpow(a,p-1,p)==1) puts("yes");
        else puts("no");
    }
    return 0;
}
