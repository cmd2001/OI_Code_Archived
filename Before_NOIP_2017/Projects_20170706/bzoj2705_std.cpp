#include<stdio.h>  
#include<stdlib.h>  
#include<math.h>  
#include<iostream>
using namespace std;
typedef long long LL;  
LL phi(LL m)  
{  
    LL ans=m,sq=(LL)sqrt(m),i;  
    for(i=2;i<=sq;i++)  
    {  
        if(m%i==0) ans=ans/i*(i-1);  
        while(m%i==0) m/=i;  
    }  
    if(m>1) ans=ans/m*(m-1);  
    return ans;  
}  
int main()  
{  
    LL n,i,j,m,ans=0; 
	scanf("%lld",&n);  
    cout<<phi(n)<<endl;
    for(i=(LL)sqrt(n);i>=1;i--)  
    {  
        if(n%i==0)  
        {  
            ans+=i*phi(n/i);  
            if(i*i<n) ans+=(n/i)*phi(i);  
        }  
    }  
    printf("%lld",ans);  
    return 0;  
}  
