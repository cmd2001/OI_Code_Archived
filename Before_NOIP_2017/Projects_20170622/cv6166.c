#include<stdio.h>
int main()
{
    long long int a=1,b=2;
    int n;
    register int i;

    scanf("%d",&n);
    if(n<=2)
    {
        printf("%d\n",n);
        return 0;
    }
    for(i=3;i<=n;i++)
    {
        a=b+a*(i-1);
        a%=14233333;
        a^=b^=a^=b;
    }
    printf("%lld\n",b);
    return 0;
}
