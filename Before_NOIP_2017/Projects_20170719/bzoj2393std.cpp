#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm> 
#define ll long long 
#define N 2001
using namespace std;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
int l,r;
int t,n,m,ans;
ll a[N],b[N];
bool vis[N];
void pre(int x,int y)
{
	if(x>t||y>r)return;
	if(x>0)a[++m]=y;
	pre(x+1,y*10+2);
	pre(x+1,y*10+9);
}
void dfs(int x,int y,ll z)
{
	if(x>n)
	{
		if(y&1)ans+=r/z-(l-1)/z;
		else if(y)ans-=r/z-(l-1)/z;
		return;
	}
	dfs(x+1,y,z);
	ll next=a[x]*z/gcd(a[x],z);
	if(next<=r)
	   dfs(x+1,y+1,next);
}
int main()
{
	scanf("%d%d",&l,&r);
	t=(int)(log(r)/log(10))+1;
	pre(0,0);
	sort(a+1,a+m+1);
	for(int i=1;i<=m;i++)
	   if(!vis[i])
	   {
	   	   b[++n]=a[i];
	   	   for(int j=i+1;j<=m;j++)
	   	       if(!(a[j]%a[i]))
	   	           vis[j]=1;
	   }
	for(int i=1;i<=n;i++)
	   a[n-i+1]=b[i];
	dfs(1,0,1);
	printf("%lld",ans);
	return 0;
}
