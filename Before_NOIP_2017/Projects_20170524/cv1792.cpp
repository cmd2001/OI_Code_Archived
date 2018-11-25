#include<bits/stdc++.h>
using namespace std;
const int maxn=1e7+1e2;
int ans[maxn],cnt;
inline void getans(int x)
{
    for(unsigned int i=2;i*i<=x;i++)
    {
        if(!(x%i)) while(!(x%i)) ans[++cnt]=i,x/=i;
    }
    if(x!=1) ans[++cnt]=x;
}
int main()
{
    static int x;
    scanf("%d",&x);
    getans(x);
    printf("%d=",x);
    for(int i=1;i<cnt;i++) printf("%d*",ans[i]);
    printf("%d\n",ans[cnt]);
    return 0;
}

