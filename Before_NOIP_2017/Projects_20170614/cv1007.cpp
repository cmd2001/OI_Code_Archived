#include<bits/stdc++.h>
using namespace std;

int main()
{
    static double sum=0;
    static int k;

    scanf("%d",&k);

    for(int i=1;;i++)
    {
        sum+=1.0/i;
        if(sum>k)
        {
            printf("%d\n",i);
            break;
        }
    }

    return 0;
}
