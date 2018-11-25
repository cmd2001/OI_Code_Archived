#include<stdio.h>
int getint()
{
    int ret=0,fix=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') fix=-1;ch=getchar();}
    while('0'<=ch&&ch<='9')
    {
        ret=ret*10+ch-'0';
        ch=getchar();
    }
    return ret*fix;
}

char getcmd()
{
    char ch=getchar();
    while(ch=='\n'||ch==' ') ch=getchar;
    return ch;
}
int main()
{
    while(1)
    {
        printf("%d\n",getint());
    }
    return 0;
}
