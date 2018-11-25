#include<bits/stdc++.h>
#define debug cout
using namespace std;
int gcd(int x,int y)
{
	return x%y==0?y:gcd(y,x%y);
}
int a,b,g,l,ans1,ans2;
double mi;
int main()
{
    scanf("%d%d%d",&a,&b,&l);
    g=gcd(a,b),a/=g,b/=g,mi=2147483647;
    for(int i=1;i<=l;i++)
        for(int j=1;j<=l;j++)
            if((double)i/j>=(double)a/b&&fabs((double)a/b-(double)i/j)<=mi)
            {
                mi=fabs((double)a/b-(double)i/j),
                ans1=i,ans2=j;
            }
    g=gcd(ans1,ans2);
    ans1/=g,ans2/=g;
    printf("%d %d",ans1,ans2);
    return 0;
}
