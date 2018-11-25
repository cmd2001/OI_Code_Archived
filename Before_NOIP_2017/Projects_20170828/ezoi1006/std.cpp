#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
using namespace std;
const int N=610,M=N*N;
const int mod=1000000007;
int n,m,k;
long long a[N][N],f[N];
int ar[N],br[N],to[N];
int rd[N],q[N],h,t;
int head[N],ver[M],nxt[M],from[M],tot;
int cd[N];
void add(int u,int v)
{
	rd[v]++;cd[u]++;
	tot++;nxt[tot]=head[u],from[tot]=u,ver[tot]=v,head[u]=tot;
}
void solve(int x)
{
	memset(rd,0,sizeof(rd));h=1,t=0;
	memset(f,0,sizeof(f));
	for(int i=1;i<=tot;i++)rd[ver[i]]++;
	for(int i=1;i<=k;i++)q[++t]=ar[i];
	f[ar[x]]=1;
	while(h<=t)
	{
		int u=q[h++];
		for(int i=head[u];i;i=nxt[i])
		{
			int v=ver[i];
			f[v]=(f[v]+f[u])%mod;
			rd[v]--;
			if(!rd[v])q[++t]=v;
		}
	}
	for(int i=1;i<=k;i++)a[x][i]=f[br[i]];
}
long long qpo(long long x,int n)
{
	long long su=1;
	while(n)
	{
		if(n&1)su=su*x%mod;
		x=x*x%mod;
		n>>=1;
	}
	return su;
}
long long gauss()
{
	long long ans=1;
//	for(int i=1;i<=k;i++)
//	{
//		for(int j=1;j<=k;j++)cout<<a[i][j]<<" ";
//		cout<<endl;
//	}
	for(int i=1;i<=k;i++)
	{
		int j;
		for(j=i;j<=k;j++)if(a[i][j])break;
		if(j==k+1)return 0;
		ans=(ans*a[i][i])%mod;long long inv=qpo(a[i][i],mod-2);
		for(j=i;j<=k;j++)a[i][j]=a[i][j]*inv%mod;
		for(j=i+1;j<=k;j++)if(a[j][i])
		{
			for(int r=k;r>=i;r--)a[j][r]=(a[j][r]-a[i][r]*a[j][i])%mod;
		}
//	for(int i=1;i<=k;i++)
//	{
//		for(int j=1;j<=k;j++)cout<<a[i][j]<<" ";
//		cout<<endl;
//	}cout<<endl;
	}
	return (ans%mod+mod)%mod;
}
bool ok()
{
//	for(int i=1;i<=n;i++)if(rd[i]==0)cout<<i<<" ";cout<<endl;
//	for(int i=1;i<=n;i++)if(cd[i]==0)cout<<i<<" ";cout<<endl;
	for(int i=1;i<=k;i++)if(rd[ar[i]]!=0)return false;
	for(int i=1;i<=k;i++)if(cd[br[i]]!=0)return false;
	int cnta=0;
	for(int i=1;i<=n;i++)if(!rd[i])cnta++;
	if(cnta!=k)return false;
	cnta=0;
	for(int i=1;i<=n;i++)if(!cd[i])cnta++;
	if(cnta!=k)return false;
	memset(rd,0,sizeof(rd));
	memset(cd,0,sizeof(cd));
	return true;
}
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++)scanf("%d",&ar[i]);
	for(int i=1;i<=k;i++)scanf("%d",&br[i]);
	while(m--)
	{
		int aa,bb;scanf("%d%d",&aa,&bb);
		add(aa,bb);
	}
	if(!ok())
	{
		cout<<"false"<<endl;
		return 0;
	}
	for(int i=1;i<=k;i++)solve(i);
	long long ans=gauss();
	cout<<ans<<endl;
	return 0;
}
