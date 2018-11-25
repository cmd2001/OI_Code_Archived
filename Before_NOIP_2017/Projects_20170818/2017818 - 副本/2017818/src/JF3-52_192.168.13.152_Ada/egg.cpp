#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1005;
const long long INF=99999999999999;
long long dp[maxn][maxn];
int n, m;

void init() {
	for(int i=2; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			dp[i][j]=INF;
	for(int j=1; j<=m; ++j)
		dp[1][j]=1;
	for(int i=1; i<=n; ++i)
		dp[i][1]=n;
}

int main() {
	freopen("egg.in", "r", stdin);
	freopen("egg.out", "w", stdout);
	scanf("%d%d", &n, &m);
	int x=0, i=1;
	init();
	while(x<=45) {
		int to=x*(x+1)/2;
		while(i<=to&&i<maxn) dp[i++][2]=x;
		x++;
	}
	for(int i=2; i<=n; ++i)
		for(int j=3; j<=m; ++j)
			for(int k=1; k<=i; ++k)
				dp[i][j]=min(dp[i][j], 1+max(dp[i-k][m], dp[k-1][m-1]));
	printf("%lld\n", dp[n][m]);
	fclose(stdin);
	return 0;
}
