#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=55;

int in[maxn],ans[maxn<<1],n,t;

inline void getin()
{
    memset(in,0,sizeof(in));
    memset(ans,0,sizeof(ans));
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
}
inline void getans()
{
    sort(in+1,in+1+n);

    ans[n]=in[1];
    int pos=2,r=n+1,l=n-1,cur=1;

    while(pos<=n)
    {
        if(cur) ans[r++]=in[pos++];
        else ans[l--]=in[pos++];
        cur^=1;
    }

    for(int i=n;i<r;i++) printf("%d ",ans[i]);
    for(int i=l+1;i<n;i++) printf("%d ",ans[i]);
    putchar('\n');
}

int main()
{

    freopen("heightround.in","r",stdin);
    freopen("heightround.out","w",stdout);

    scanf("%d",&t);
    while(t--)
    {
        getin();
        getans();
    }

    fclose(stdin);
    fclose(stdout);

    return 0;
}

