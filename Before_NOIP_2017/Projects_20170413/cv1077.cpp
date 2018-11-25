#include<bits/stdc++.h>
using namespace std;
long long int a[110][110],n,m;
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%lld",&a[i][j]);
	for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[j][i]=a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
	scanf("%lld",&m);
	for(int i=1,x,y;i<=m;i++) scanf("%d%d",&x,&y),printf("%lld\n",a[x][y]);
	return 0;
}
