#include<bits/stdc++.h>
using namespace std;
//exgcd by cmd2001
int exgcd(int a,int b,int &x,int &y)
{
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

int main()
{
    int a,b;
    int x,y;
    scanf("%d%d",&a,&b);
    printf("%d\n",exgcd(a,b,x,y));
    printf("x=%d,y=%d",x,y);
    return 0;
}
