#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
int in[maxn],m,n;
int cmd,a,b;
bool rev;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&cmd);
        if(cmd==3) rev^=1;
        else if(cmd==2)
        {
            scanf("%d%d",&a,&b);
            if(rev) in[n-a+1]=b;
            else in[a]=b;
        }
        else if(cmd==1)
        {
            scanf("%d",&a);
            if(rev) printf("%d\n",in[n-a+1]);
            else printf("%d\n",in[a]);
        }
    }
    return 0;
}

