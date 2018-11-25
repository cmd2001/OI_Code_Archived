#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <iostream>

using namespace std; 

const int N = 19;
int G[N][N];
int n;
unsigned int fac[(1 << N) + 5];
struct checker
{
	bool vis[N];
	queue<int> que;
	int col[N];
	int cnt;
	inline void bfs(int x) {
		cnt = 0;
		memset(col, -1, sizeof(col));
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; ++i) {
			if (x & (1 << i)) {
				que.push(i + 1);
				break;
			}
		}
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			if (vis[u]) {
				continue;
			}
			vis[u] = 1;
			int c = 0;
			for (int i = 1; i <= n; ++i) {
				if (i != u && x & (1 << (i - 1)) && G[u][i]) {
					if (vis[i]) {
						c |= 1 << col[i];
					}
					else {
						que.push(i);
					}
				}
			}
			for (int i = 0; i < n; ++i) {
				if (!(c & (1 << i))) {
					col[u] = i;
					cnt = max(cnt, col[u] + 1);
					break;
				}
			}
		}
	} 
	inline unsigned int solve(int x) {
		bfs(x);
		return cnt;
	}
}f;
int main() {
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("\n");
		for (int j = 1; j <= n; ++j) {
		  G[i][j] = getchar() - '0';
		} 
	}
	fac[0] = 1;
	for (int i = 1; i < (1 << n); ++i) {
		fac[i] = fac[i - 1] * 233;
	} 
	unsigned int ans = 0;
	for (int i = 1; i < (1 << n); ++i) {
		ans += f.solve(i) * fac[i];
	}
	cout << ans << endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
