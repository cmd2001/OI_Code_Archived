#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=5*1e5+10;
const double inf=1e20,eps=1e-8;
struct node
{
    double xx1,yy1,xx2,yy2;
}segma[maxn];
int n,t;
bool ans;
bool check(int at,double x,double y)
{
    double l=-inf,r=inf;
    double a,b;
    for(int i=1;i<=n;i++)
    {
        if(i!=at)
        {
            a=(segma[i].yy1-y)/(segma[i].xx1-x);
            b=(segma[i].yy2-y)/(segma[i].xx2-x);
            l=max(l,min(a,b));
            r=min(r,max(a,b));
        }
        //debug<<"at="<<at<<" i="<<i<<"   l="<<l<<"   r="<<r<<endl;
    }
    return r-l>-eps;
}

int main()
{
    scanf("%d",&t);
    //debug<<t<<endl;
    for(int j=1;j<=t;j++)
    {
        scanf("%d",&n);
        //debug<<n<<endl;
        memset(segma,0,sizeof(segma));
        ans=0;
        for(int i=1;i<=n;i++) scanf("%lf%lf%lf%lf",&segma[i].xx1,&segma[i].yy1,&segma[i].xx2,&segma[i].yy2);
        for(int i=1;i<=n;i++)
        {
            if(check(i,segma[i].xx1,segma[i].yy1))
            {
                ans=1;
                break;
            }
            if(check(i,segma[i].xx2,segma[i].yy2))
            {
                ans=1;
                break;
            }
        }
        if(ans) printf("Yes!\n");
        else printf("No!\n");
    }
    return 0;
}
