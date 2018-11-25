#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
long long ans;
long long tot;
long long a[5];
long long state[100][5];
long long dp[5][35];
bool chec()
{
	for(long long i=1;i<=4;i++)
	{
		if(a[i]==1){
			if(a[i+1]!=1) return 0;
			else i++;
		}
	}
	return 1;
}
bool jdge(long long x,long long y)
{
	for(long long i=1;i<=4;i++)
	{
		if((!state[y][i])&&(state[x][i]!=2)) return 0;
		if((state[x][i]==2)&&(state[y][i])) return 0;
	}
	return 1;
}
void dfs(long long x)
{
	if(x==5)
	{
		if(chec())
		{
			tot++;
			for(long long i=1;i<=4;i++)
			state[tot][i]=a[i];
		}
		return ;
	}
	for(long long i=0;i<=2;i++)
	{
		a[x]=i;
		dfs(x+1);
		a[x]=0;
	}
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	dfs(1);
	long long n,m;
	while(1)
	{
		for(int i=1;i<=tot;i++)
		{
			int flag=0;
			for(int j=1;j<=4;j++)
			{
				if(!state[i][j]) {
					flag=1;
					dp[1][i]=0;
					break;
				}
			}
			if(!flag)	 dp[1][i]=1;
	//		  cout<<i<<" ";
		}
//		for(long long i=1;i<=tot;i++) cout<<dp[1][i]<<" ";
		cin>>n>>m;
		//m;
		if(!n&&!m) break;
		for(int i=2;i<=n;i++)
		{
			for(int j=1;j<=tot;j++)
			{
				dp[i%2][j]=0;
				for(int k=1;k<=tot;k++)
				{
					if(jdge(k,j))
					{
				//		if(j==15) cout<<k<<" ";
						dp[i%2][j]=(dp[i%2][j]+dp[!(i%2)][k])%m;
					}
				}
			}
		}
		ans=0;
		for(int i=1;i<=tot;i++)
		{
//			cout<<i<<" "<<dp[n%2][i]<<endl;
			int flag=0;
			for(int j=1;j<=4;j++)
			{
				if(state[i][j]==2) {
					flag=1;
					break;
				}
			}
			if(!flag) ans=(ans+dp[n%2][i])%m;
		}
		cout<<ans<<endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
