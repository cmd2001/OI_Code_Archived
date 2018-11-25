#include<cstdio>
#define int long long
using namespace std;
int dp[10][91][91][91];
int power[11]={1LL,10LL,100LL,1000LL,10000LL,100000LL,1000000LL,10000000LL,100000000LL,1000000000LL,10000000000LL};
void dodp()
{
	int i,j,k,l,p;
	for(i=0;i<10;i++)
	{
		for(j=1;j<90;j++)
		{
			dp[0][i][j][i%j]=1;
		}
	}
	for(i=1;i<10;i++)
	{
		for(p=0;p<10;p++)
		{
			for(j=p;j<=i*9+p;j++)
			{
				for(k=1;k<90;k++)
				{
					for(l=0;l<k;l++)
					{
						dp[i][j][k][l]+=dp[i-1][j-p][k][((l-p*power[i]%k)%k+k)%k];
					}
				}
			}
		}
	}
}
int getans(int on)
{
	int i,j,k,p,l,ret=0,num=0,sum=0,top,mod;
	if(on<10) return on;
	for(i=9;i;i--)
	{
		top=on/power[i]%10;
		for(p=0;p<top;p++)
		{
			for(j=(sum+p?0:1);j<=i*9;j++)
			{
				mod=sum+p+j;
//				printf("%d\n",mod);
				ret+=dp[i-1][j][mod][(mod-(num+p*power[i])%mod)%mod];
			}
		}
		sum+=top;
		num+=top*power[i];
	}
	top=on%10;
	for(i=0;i<=top;i++)
	{
		if((num+i)%(sum+i)==0) ret++;
	}
	return ret;
}
signed main()
{
	int i,j,n,m,l,r;
	dodp();
	while(scanf("%lld%lld",&l,&r)!=EOF)
	{
		printf("%lld\n",getans(r)-getans(l-1));
	}
	return 0;
}
