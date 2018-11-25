#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<math.h>
using namespace std;
int n,m,t,out,mx,ans,tot,num[10]={6,2,5,5,4,5,6,3,7,5};
char c,s[30];
int main()
{
	freopen("DigitalCounter.in","r",stdin);
	freopen("DigitalCounter.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",s);
	for(int i=0;i<n;i++)m*=10,m+=(s[i]-'0');
	t=m+1;
	for(int i=1;i<=n;i++)
	{
		int x=m%10;
		m=m/10;
		tot+=num[x];
	}
	for(int i=1;i<=n;i++)
	{
		mx*=10;
		mx+=9;
	}
	while(1)
	{
		ans=0;
		m=t;
		for(int i=1;i<=n;i++)
		{
			int x=m%10;
			m=m/10;
			ans+=num[x];
		}
		if(ans==tot)break;
		out++;
		if(t==mx)t=0;
		else t++;
	}
	printf("%d\n",out+1);
	fclose(stdin);
	fclose(stdout);
}



