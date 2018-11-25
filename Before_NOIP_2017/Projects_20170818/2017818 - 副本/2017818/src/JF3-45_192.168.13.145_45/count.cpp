#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
ll a[100010];
int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	while(n&&m){
		memset(a,0,sizeof(a));
		a[1]=1; a[2]=5%m; a[3]=11%m; a[4]=36%m; a[5]=95%m;
		for(int i=5;i<=n;i++) a[i]=(a[i-1]+a[i-2]*5+a[i-3]-a[i-4]+m)%m;
		printf("%lld\n",a[n]%m);
		scanf("%d%d",&n,&m);
	}
	return 0;
}
