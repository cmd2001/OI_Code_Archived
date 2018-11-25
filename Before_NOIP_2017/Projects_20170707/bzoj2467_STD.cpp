#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
#define MOD 2007  
using namespace std;  
int Quick_Power(int x,int y)  
{  
    int re=1;  
    while(y)  
    {  
        if(y&1)re*=x,re%=MOD;  
        x*=x,x%=MOD;  
        y>>=1;  
    }  
    return re;  
}  
int main()  
{  
    int n,T;  
    for(cin>>T;T;T--)  
    {  
        scanf("%d",&n);  
        printf("%d\n", 4*n%MOD*Quick_Power(5,n-1)%MOD );  
    }  
}  
