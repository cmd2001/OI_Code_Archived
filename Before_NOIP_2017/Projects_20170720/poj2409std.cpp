#include <iostream>  
#include <string.h>  
using namespace std;  
int c,n;//c种颜色，n个珠子  
int ans;  
  
int gcd(int a,int b)  
{  
    return b==0?a:gcd(b,a%b);  
}  
  
int power(int p,int n)  
{  
    int ans=1;  
    while(n)  
    {  
        if(n&1)  
            ans*=p;  
        p*=p;  
        n/=2;  
    }  
    return ans;  
}  
  
int main()  
{  
    while(cin>>c>>n&&(c||n))  
    {  
        ans=0;  
        for(int i=1;i<=n;i++)  
            ans+=power(c,gcd(n,i));  
        if(n&1)//是奇数，有4n个包含(n/2+1)个循环节的循环群  
            ans+=n*power(c,n/2+1);  
        else  
            ans+=(power(c,n/2+1)+power(c,n/2))*(n/2);  
        ans/=2*n;//别忘了处以置换群的总个数  
        cout<<ans<<endl;  
    }  
    return 0;  
}  
