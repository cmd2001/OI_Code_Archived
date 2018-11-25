#include<bits/stdc++.h>
#define debug cout
using namespace std;
int xx1,yy1,xx2,yy2;
int n,x,y;
int ans;
struct node
{
    int s1,s2;
    friend bool operator < (const node &a,const node &b) {return a.s1>b.s1;}
}data[100100];
int main()
{
    scanf("%d%d%d%d",&xx1,&yy1,&xx2,&yy2);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&x,&y);
        data[i].s1=((xx1-x)*(xx1-x)+(yy1-y)*(yy1-y));
        data[i].s2=((xx2-x)*(xx2-x)+(yy2-y)*(yy2-y));
    }
    sort(data+1,data+1+n);
    int mxb=0;
    ans=0x3fffffff;
    for(int i=1;i<=n;i++)
    {
        ans=min(ans,mxb+data[i].s1);
        mxb=max(mxb,data[i].s2);
    }
    printf("%d",ans);
    return 0;
}
