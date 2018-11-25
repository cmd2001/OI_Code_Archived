#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<vector>
#include<algorithm>
#define inf 1000000000
#define ll long long 
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int T,n,m;
const int p=10007;
int qpow(int a,int b)
{
	int ans;
	for(ans=1;b;b>>=1,a=a*a%p)
		if(b&1)ans=ans*a%p;
	return ans;
}
int getc(int n,int m)
{
	if(n<m)return 0;
	if(m>n-m)m=n-m;
	ll s1=1,s2=1;
	for(int i=0;i<m;i++)
	{
		s1=s1*(n-i)%p;
		s2=s2*(i+1)%p;
	}
	return s1*qpow(s2,p-2)%p;
}
int lucas(int n,int m)
{
	if(m==0)return 1;
	return getc(n%p,m%p)*lucas(n/p,m/p)%p;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();m=read();
		printf("%d\n",lucas(n,m));
	}
	return 0;
}
