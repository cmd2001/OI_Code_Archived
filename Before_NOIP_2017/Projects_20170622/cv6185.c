#include<stdio.h>

char out[10],*st=out+9;
int n;

int main()
{
    scanf("%d",&n);
    if(!n) putchar('0');
    while(n)
    {
        *st=n%8;
        *st+='0';
        n/=8;
        st--;
    }
    puts(st+1);
    return 0;
}
