#include<bits/stdc++.h>
#define int long long
#define debug cout
using namespace std;
int ans,mod;
bool bug;
int gcd(int a,int b)
{
    if((!a)||(!b)) return a|b;
    while(b)
    {
        debug<<"a="<<a<<endl;
        a%=b;
        a^=b^=a^=b;
    }
    return a;
}
int exgcd(int a,int b,int &x,int &y)
{
    int d=a;
    if(b) d=exgcd(b,a%b,y,x),y-=(a/b)*x;
    else x=1,y=0;
    return d;
}
void calc(int a1,int a2,int b1,int b2)
{
    int g=gcd(a1,a2);
    debug<<"g="<<g<<endl;
    if((!b1)&&(!b2)) {mod=a1*a2/g;ans=0;}
    int delta=b1-b2;
    if(g!=1&&delta%g) {bug=1;return;}
    mod=a1*a2/g;
    int y1,y2;
    exgcd(a1,a2,y1,y2);
    ans=b2+(delta/g)*a2*y2;
    ans%=mod;
    if(ans<0) ans+=mod;
}
signed main()
{
    int a1,b1,a2,b2;
    scanf("%lld%lld%lld%lld",&a1,&b1,&a2,&b2);
    calc(a1,a2,b1,b2);
    if(bug) printf("No Answer\n");
    printf("mod=%lld\nans=%lld\n",mod,ans);
    return 0;
}
