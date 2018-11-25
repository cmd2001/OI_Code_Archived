//BZOJ1005STD.cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define mod 1000000
#define ll long long 
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}
    return x*f;
}
int n,m,tot,cnt;
int d[1005],num[1005],pri[1005];
int ans[1005],l=1;
inline bool jud(int x)
{
     for(int i=2;i<=sqrt(x);i++)
         if(x%i==0)return 0;
     return 1;
}
void getpri()
{
     for(int i=2;i<=1000;i++)
         if(jud(i))pri[++cnt]=i;
}
void solve(int a,int f)
{
	 for(int k=1;k<=a;k++)
	 {
	 	 int x=k;
         for(int i=1;i<=cnt;i++)
         {
             if(x<=1)break;
             while(x%pri[i]==0)
             {num[i]+=f;x/=pri[i];}
         }
	 }
}
void mul(int x)
{
	for(int i=1;i<=l;i++)
	    ans[i]*=x;
	for(int i=1;i<=l;i++)
	{
	    ans[i+1]+=ans[i]/mod;
	    ans[i]%=mod;
    }
    while(ans[l+1]>0)
	{l++;ans[l+1]+=ans[l]/mod;ans[l]%=mod;}
}
void print()
{
	for(int i=l;i>0;i--)
	    if(i==l)printf("%d",ans[i]);
		else printf("%06d",ans[i]);
}
int main()
{
     getpri();ans[1]=1;
     n=read();
     if(n==1)
     {
         int x=read();
         if(!x)printf("1");
         else printf("0");
         return 0;
     }
     for(int i=1;i<=n;i++)
     {
         d[i]=read();
         if(!d[i]){printf("0");return 0;}
         if(d[i]==-1)m++;
		 else {d[i]--;tot+=d[i];}
     }
     if(tot>n-2){printf("0");return 0;}
     solve(n-2,1);
     solve(n-2-tot,-1);
     for(int i=1;i<=n;i++)
         if(d[i])solve(d[i],-1);
     for(int i=1;i<=cnt;i++)
         while(num[i]--)
             mul(pri[i]);
     for(int i=1;i<=n-2-tot;i++)
         mul(m);
     print();
     return 0;
}
