#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int num[10]={6,2,5,5,4,5,6,3,7,5};
char a[20];
int main()
{
	freopen("DigitalCounter.in","r",stdin);
	freopen("DigitalCounter.out","w",stdout);
	int n,i,m=0,fz,ans=0,in[20];
	scanf("%d%c",&n,&a[0]);
	for(i=n;i>=1;i--)
	{
		scanf("%c",&a[i]);
		a[i]-='0';
		in[i]=a[i];
		m+=num[in[i]];
	}
	while(1)
	{
		ans++;
		in[1]++;
		fz=0;
		for(i=1;i<n;i++)
		{
			if(in[i]==10)
			{
				in[i]=0;
				in[i+1]++;
			}
			fz+=num[in[i]];
		}
		if(in[n]==10)
		{
			memset(in,0,sizeof(in));
		}
		else
		{
			fz+=num[in[n]];
		}
		if(fz==m)	break;
	}
	printf("%d",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
