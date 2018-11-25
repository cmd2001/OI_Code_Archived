#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int in[10100],n,ans,x;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",in+i);
	for(int l=31;l>=0;l--)
	{
		for(int j=1;j<=n;j++)
		{
			if((in[j]>>l)&1)
			{
				for(int k=1;k<=n;k++)
				{
					if(j!=k&&(in[k]>>l)&1) in[k]^=in[j];
				}
			}
			if(!((ans>>l)&1)) ans^=in[j];
			in[j]=0;
		}
	} 
	printf("%d\n",ans);
	return 0;
}
