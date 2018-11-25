#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int w[12] = {6,2,5,5,4,5,6,3,7,5};
const int x[12] = {-1,1,7,4,2,0,8,-1,-1};
int n, a[16], s;
long long  dp[16][10][100];
int main() {
	freopen("DigitalCounter.in", "r", stdin);
	freopen("DigitalCounter.out", "w", stdout);
	scanf("%d", &n);
	long long in = 0;
	long long m = 0;
	for(int i = n; i >= 1; i--) {
		m *= 10;
		char op; cin >> op;
		a[i] = op - '0';
		s += w[a[i]];
	}
	for(int i = n; i >= 1; i--)  in = in * 10 + a[i];
	for(int i = 0; i <= 9; i++) {
		dp[1][i][w[i]]++;
	}
//	for(int i = 0; i <= 9; i++) {
//		printf("dp[1][%d][%d] = %d\n", i, w[i], dp[1][i][w[i]]);
//	}
	for(int i = 2; i <= n; i++) {
		for(int k = 0; k <= 150; k++) {
			for(int j = 0; j <= 9; j++) {
				for(int p = 0; p <= 9; p++) {
					if(k-w[p]-w[j] >= 0) {
						dp[i][j][k] += dp[i-1][p][k-w[p]-w[j]];
					}
				}
//				if(dp[i][j][k])printf("dp[%d][%d][%d] = %lld\n", i, j, k, dp[i][j][k]);
			}
		} 
	}
	int ans[16];
	for(int i = n; i >= 1; i--) {
		for(int j = 0; j <= 9; j++) {
			ans[i] = 0;
//			printf("%d %d %d = %d\n", i ,j, s, dp[i][j][s]);
			if(dp[i][j][s] > 1) {
				if(j == 0) s -= w[j], ans[i] = j;
				else s -= w[j-1], ans[i] = j-1;
				break;
			}
			if(dp[i][j][s] == 1) {
				ans[i] = j;
				for(int k = i - 1; k >= 1; k--) {
					ans[k] = x[s-w[ans[k+1]]];
					s -= w[ans[k+1]];
				}
				goto out;
			} 
		}
	}
	out:
	long long ot = 0;
	for(int i = n; i >= 1; i--)	ot = ot * 10 + ans[i];
	cout << ot - in << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
