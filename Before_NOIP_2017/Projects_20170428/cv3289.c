#include<stdio.h>
#define maxn 100100
int a[maxn],n,cnt,i;
long long int tmp,base;
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++) scanf("%d",a+i);
    base=2,cnt=1;
    for(i=2;i<=n;i++)
    {
        if(base!=0&&a[i]<a[i-1]){++cnt;base=0;}
        if(base!=1&&a[i]>a[i-1]){++cnt,base=1;}
    }
    if(cnt) printf("%d\n",cnt);
    else puts("0");
    return 0;
}

