#include<bits/stdc++.h>
using namespace std;
int n,now;
int main()
{
    now=1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++) now%=10,putchar('0'+now),now++;
        putchar('\n');
    }
    return 0;
}
