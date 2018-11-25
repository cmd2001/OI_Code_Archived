#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2e5+1e2;

int in[maxn],mx[maxn],t,mod;
int lst,n;
char q[5];

int main()
{
    scanf("%d%d",&n,&mod);

    for(int i=1,x;i<=n;i++)
    {
        scanf("%s%d",q,&x);
        if(*q=='A')
        {
            in[++t]=(x+lst)%mod;
            for(int i=t;i;i--)
                if(mx[i]<in[t]) mx[i]=in[t];
                else break;
        }
        else printf("%d\n",lst=mx[t-x+1]);
    }

    return 0;
}

