#include<bits/stdc++.h>
using namespace std;
int main()
{
	static int l,m,ans=0;
	static bool vis[10100];
	scanf("%d%d",&l,&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		for(int j=a;j<=b;j++) vis[j]=1;
	}
	for(int i=0;i<=l;i++) ans+=!vis[i];
	cout<<ans<<endl;
}
