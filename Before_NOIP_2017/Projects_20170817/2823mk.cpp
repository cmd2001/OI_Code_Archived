#include<bits/stdc++.h>
using namespace std;

int main()
{
    freopen("2823mkd.txt","w",stdout);
    const int maxn=10000000,maxk=100000;
    printf("%d %d\n",maxn,maxk);
    for(int i=1;i<=maxn;i++) printf("%d ",rand()-rand());
    fclose(stdout);
    return 0;
}
