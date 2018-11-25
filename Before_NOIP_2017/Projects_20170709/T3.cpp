#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;

int refer[]={6,2,5,5,4,5,6,3,7,5};
int n,c;
lli x;

inline int counter(lli x)
{
    int ret=0,cnt=0;
    while(x)
    {
        ret+=refer[x%10];
        x/=10;
        cnt++;
    }
    if(cnt<n) ret+=(n-cnt)*6;
    return ret;
}

int main()
{
    scanf("%d%lld",&n,&x);

    c=counter(x);
    for(register lli i=x+1;;i++)
    {
        if(counter(i)==c)
        {
            printf("%lld\n",i-x);
            break;
        }
    }

    return 0;
}


