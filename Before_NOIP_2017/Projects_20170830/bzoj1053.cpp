#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define lli long long int
#define debug cout
using namespace std;
const  lli lp[]={0,1,2,3,5,7,11,13,17,19,23,29,31},
lx[]={0,1,2,6,30,210,2310,30030,510510,9699690,223092870,6469693230};
int c[20],ed;
 
lli n,pos;
lli ans,cnt;
 
inline int calc()
{
    int ret=1;
    for(int i=1;i<=ed;i++) ret*=(c[i]+1);
    return ret;
}
 
inline void dfs(lli num,int pos)
{
    if(pos==1)
    {
        int c=calc();
        if(c>cnt) cnt=c,ans=num;
        else if(c==cnt) ans=min(ans,num);
        return;
    }
    for(int i=pos;i;i--)
        if(num*lp[i]<=n)
        {
            c[i]++;
            dfs(num*lp[i],i);
            c[i]--;
        }
}
         
     
 
int main()
{
     
    scanf("%lld",&n);
     
    while(lx[pos]<=n) pos++;
    pos--;
     
     
    for(int i=1;i<=pos;i++)
    {
        for(int j=1;j<=i;j++) c[i]=1;
        ed=i;
        dfs(lx[i],i);
    }
     
    printf("%lld\n",ans);
     
     
    return 0;
}
