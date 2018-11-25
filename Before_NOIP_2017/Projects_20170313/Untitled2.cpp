#include<bits/stdc++.h>
#define debug cout
using namespace std;
int exgcd(int a,int b,int &x,int &y)
{
    debug<<a<<b<<endl;
    int d=a;
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
inline int calc(int a1,int b1,int a2,int b2)
{
    int t1,t2,delta=abs(b1-b2);
    int d=exgcd(a1,a2,t1,t2);
    //debug<<"d="<<d<<endl;
    if((b1-b2)%d) throw(d);
    t2=-t2;
    debug<<"t1="<<t1<<"t2="<<t2<<endl;
    if(delta) t1*=delta/d,t2*=delta/d;
    debug<<"t1="<<t1<<"t2="<<t2<<endl;
    debug<<"The num is"<<(t1*a1)+b1<<endl;
    return ((t1*a1)+b1)%(a1*a2/d);
}
int main()
{
    int a1,b1,a2,b2;
    scanf("%d%d%d%d",&a1,&b1,&a2,&b2);
    printf("ans=%d\n",calc(a1,b1,a2,b2));
    return 0;
}


