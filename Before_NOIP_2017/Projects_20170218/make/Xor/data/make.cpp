#include<bits/stdc++.h>
using namespace std;
int in[10100],n,ans,x;
char inf[50],otf[50];
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
	srand(time(NULL));
	for(int i=1;i<=20;i++)
	{
		sprintf(inf,"xor%d.in",i);
		sprintf(otf,"xor%d.ans",i);
		freopen(inf,"w",stdout);
		n=x=ans=0;
		memset(in,0,sizeof(in));
		n=rand()%5000;
		if(i>10)
		{
			while(n<=5000) n=rand()%10000;
		}
		printf("%d\n",n);
		for(int at=1;at<=n;at++)
		{
			in[at]=rand(); 
			printf("%d\n",in[at]);
		}
		freopen(otf,"w",stdout);
		{ 
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
		} 
	}
	return 0;
}
		
