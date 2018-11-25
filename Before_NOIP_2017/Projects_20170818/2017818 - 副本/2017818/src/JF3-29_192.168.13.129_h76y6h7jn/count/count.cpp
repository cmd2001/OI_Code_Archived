#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,Mod;
long long ans;
long long kuai(int a,int b)
{
	if(b==0) return 1;
	long long k=kuai(a,b/2);
	if(b%2==1) return (k*k*a)%Mod;
	else return (k*k)%Mod;
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	while(1)
	{
		scanf("%d%d",&n,&Mod);
		if(n==0) break;
		if(n==1)
		{
			printf("1\n");continue;
		}
		ans=kuai(5,n/2);
		ans%=Mod;
		int k=n/2+1;if(n>3) k++;
		if(n%2==0) k=n/2;
		k*=4;
		if(n>3)
		{
			ans+=k*5;ans%=Mod;ans-=10;
			if(ans<0) ans+=Mod;
		}
		else
		{
			ans+=k;ans%=Mod;ans-=2;
			if(ans<0) ans+=Mod;
		}
		printf("%lld\n",ans);
	}
	fclose(stdin);
	fclose(stdout);
}
