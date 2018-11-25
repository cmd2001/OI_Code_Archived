#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const double eps=1e-6;
double a,b,c,d;

double f(double x)
{
    return a*x*x*x+b*x*x+c*x+d;
}
bool judge(double lam)
{
    return fabs(lam)<=eps;
}

int main()
{
    scanf("%lf%lf%lf%lf",&a,&b,&c,&d);

    for(double i=-100.0;i<=100.0;i+=0.01)
    {
        if(judge(f(i))) printf("%0.2f ",i);
    }

    return 0;
}
