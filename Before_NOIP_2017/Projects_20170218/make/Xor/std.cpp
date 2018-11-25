#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int in[10100],n,ans,x;
int cntone(int x)
{
	int ret=0;
	while(x)
	{
		if(x&1) ++ret;
		x>>=1;
	}
	return ret;
}
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
	printf("%d\n",cntone(ans));
	return 0;
}
