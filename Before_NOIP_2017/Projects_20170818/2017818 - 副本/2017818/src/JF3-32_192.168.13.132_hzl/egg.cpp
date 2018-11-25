#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1000 + 10, maxm = 1000 + 10, INF = 0x3f3f3f3f;
int f[maxn][maxm];
long long dp(int n, int m){
	if(!n) return 0;
	if(m == 1) return n;
	if(n == 1) return 1;
	if(f[n][m] != INF) return f[n][m];
	int temp = ceil(log2(n + 1));
	if(m >= temp) return f[n][m] = temp;
	for(int i = n; i; i--){
		int t = max(dp(i - 1, m - 1), dp(n - i, m)) + 1;
		f[n][m] = min(f[n][m], t);
	}
	return f[n][m];
}
int main(){
	freopen("egg.in", "r", stdin);
	freopen("egg.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	memset(f, 0x3f, sizeof f);
	cout << dp(n, m) << endl;
	return 0;
}
