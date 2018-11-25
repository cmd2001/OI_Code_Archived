#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

const int N = 1000 + 5;
int f[N][N];
int n, m;

int main() {
	freopen("egg.in", "r", stdin);
	freopen("egg.out", "w", stdout);
	scanf("%d%d", &n, &m);
	memset(f, 0x3f3f, sizeof(f));
	for (int i = 1; i <= n; ++i) {
		f[1][i] = i;
	}
	for (int i = 1; i <= m; ++i) {
		f[i][1] = 1;
		f[i][0] = 0;
	}
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			//f[i][j] = min(max(f[i - 1][n - j + 1], f[i][j - 1]) + 1, f[i - 1][j]);
		  for (int k = 1; k <= j; ++k) {
				f[i][j] = min(max(f[i - 1][j - k], f[i][k - 1]) + 1, f[i][j]);
			}
		}
	}
	printf("%d\n", f[m][n]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
// f[i][j] = min(max(f[i - 1][j - k] + f[i][k - 1]) + 1, f[i][j]);
