#include<iostream>
#include<cstdio>
#include<cstring>
#define debug cout
using namespace std;
const int maxn=1e4+1e2;

int delta[maxn];

int main()
{
    static int n,sum,now;
    scanf("%d%d",&n,&sum);
    now=(n*(n-1))>>1;
    for(int i=1;i<n;i++) // i is the pos;
    {
        if(now>sum&&now-2*(n-i)>=sum)
        {
            now-=2*(n-i);
            delta[i]=-1;
        }
        else delta[i]=1;
    }
    if(sum!=now)
    {
        puts("NIE");
        return 0;
    }
    for(int i=1,t=0;i<=n;i++)
    {
        printf("%d\n",t);
        t+=delta[i];
    }
    return 0;
}

