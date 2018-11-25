#include<stdio.h>
int main()
{
    unsigned long long int ans,sum=1;
    int n;
    scanf("%d",&n);
    if(!n)
    {
        putchar('1');
        return 0;
    }
    while(n--)
    {
        ans=sum;
        sum+=ans;
    }
    printf("%llu\n",ans);
    return 0;
}
