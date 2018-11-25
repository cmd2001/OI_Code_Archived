#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e4+1e2;
bool bug;
int t,n;
__int128_t a[11],b[11];
__int128_t ans,mod;
__int128_t s,e,add=1;
__int128_t gcd(__int128_t a,__int128_t b)
{
	return (!(a%b))?b:gcd(b,a%b);
}
__int128_t exgcd(__int128_t a,__int128_t b,__int128_t &x,__int128_t &y)
{
    __int128_t d=a;
    if(b)
    {
        d=exgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
    else
    {
        x=1,y=0;
    }
    return d;
}
__int128_t calc(__int128_t a1,__int128_t a2,__int128_t b1,__int128_t b2)
{
	__int128_t absdelta;
	if(a1<a2){swap(a1,a2);swap(b1,b2);}
	__int128_t g=gcd(a1,a2),delta=(b2-b1);
	if(delta<0) absdelta=-delta;
	else absdelta=delta;
	if(absdelta%g){bug=1;return 0;}
	mod=a1*a2/g;
	__int128_t y1,y2;
	exgcd(a1,a2,y1,y2);
	__int128_t ret=a1*y1*(delta/g)+b1;
	ret%=mod;
	if(ret<0) ret+=mod;
	return ret;
}
int main()
{
    __int128_t delta,tme;
    scanf("%d%lld%lld",&n,&s,&e);
    if(n==1)
    {
        long long int aa,bb;
        scanf("%lld%lld",&aa,&bb);
        if(!bb) printf("0\n");
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",a+i,b+i);
        add*=*(a+i);
    }
    for(int i=1;i<n&&!bug;i++)
    {
        long long int num=calc(a[i],a[i+1],b[i],b[i+1]);
        a[i+1]=mod;
        b[i+1]=num;
        ans=num;
    }
    if(bug) {printf("0\n0\n");return 0;}
    delta=s-ans;
    delta=delta/add;
    ans+=delta*add;
    if(ans<s) ans+=add;
    if(ans<=e) tme=(e-ans)/mod+1,cout<<(long long int)tme<<"\n"<<(long long int)ans<<endl;
    else puts("0\n0");
	return 0;
}
