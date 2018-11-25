#include<bits/stdc++.h>
using namespace std;
int in;
long long int out;
long long int fastpow(long long int base,int tme)
{
    long long int ret=1,now=base;
    while(tme)
    {
        if(tme&1) ret*=now;
        now*=now;
        tme>>=1;
    }
    return ret;
}
int main()
{
    scanf("%d",&in);
    out=fastpow(2,in);
    printf("%lld\n",out);
    return 0;
}
