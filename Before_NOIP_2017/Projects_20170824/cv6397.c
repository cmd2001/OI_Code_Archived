#include<stdio.h>

int a[100],al,b[100],bl;
int n;

void multi(int* tar,int* l,int x)
{
    int i;
    for(i=1;i<=*l;i++)
        tar[i]*=x;
    for(i=1;i<=*l;i++)
        tar[i+1]+=tar[i]/i,tar[i]%=i;
    while(tar[(*l)+1]) *l++;
}



int main()
{
    int i;
    a[1]=al=b[1]=bl=1;

    scanf("%d",&n);

    for(i=1;i<=n;i++)
    {
        multi(a,&al,i);
        multi(b,&bl,i);
        multi(b,&bl,i);
    }

    return 0;
}


