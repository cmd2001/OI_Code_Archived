#include<bits/stdc++.h>
using namespace std;
const int maxn=30;

int f[maxn],n,ans;
bool vis[maxn];

inline bool judge()
{
	for(int i=1;i<n;i++) if(f[i<<1]>f[(i+1)<<1]) return 0;
	for(int i=1;i<n;i++) if(f[(i<<1)-1]>f[((i+1)<<1)-1]) return 0;
	for(int i=1;i<=n;i++) if(f[(i<<1)-1]>f[i<<1]) return 0;
	return 1;
}

void dfs(int dep)
{
	
	if(dep>(n<<1))
	{
		/*if(judge())
		{
			for(int i=1;i<=(n<<1);i++) printf("%d ",f[i]);
			puts("");
		}*/
		ans+=judge();
		return;
	}
	
	for(int i=1;i<=(n<<1)&&i<=dep+n;i++)
	{
		if(!vis[i])
		{
			vis[i]=1;
			f[dep]=i;
			if(dep>2&&f[dep]<f[dep-2]) {vis[i]=0;continue;}
			if((!(dep&1))&&f[dep]<f[dep-1]) {vis[i]=0;continue;}
			dfs(dep+1);
			vis[i]=0;
		}
	}
}

int main()
{
	cin>>n;
	
	dfs(1);
	
	cout<<ans<<endl;
	
	return 0;
}
			
