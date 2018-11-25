#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#define N 100
using namespace std;
const int dir[4][2] = {0,1,0,-1,1,0,-1,0};

bool map[N][N];
bool vis[N][N];
int n, m;
int mxx, mnx, mxy, mny, cnt, ans1, ans2;

bool check(int x, int y) {
	if(!vis[x][y] && x >= 1 && x <= n && y >= 1 && y <= m && map[x][y]) return true;
	else return false;
}

void dfs(int x, int y) {
	if(!check(x, y)) return;
	/*for(int i =1; i <= n; i++) {
		for(int j = 1; j <= m; j++) printf("%d ", vis[i][j]);
		puts("");
	}
	system("cls");
	*/
	vis[x][y] = 1;
	cnt++;
	mxx = max(mxx, x);
	mnx = min(mnx, x);
	mxy = max(mxy, y);
	mny = min(mny, y);
	for(int i = 0; i < 4; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		dfs(nx, ny);
	}
}

int main() {
	freopen("satel.in", "r", stdin);
	freopen("satel.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			char op;
			cin >> op;
			if(op == '#') map[i][j] = 1;
			else map[i][j] = 0;
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(!check(i ,j)) continue;
			cnt = 0;
			mxx = mxy = 0;
			mnx = mny = 0x7f7f7f;
			dfs(i, j);
			int a = mxx - mnx + 1;
			int b = mxy - mny + 1;
			if(cnt == a * b) ans1++;
			else ans2++;
		}
	}
	printf("%d\n%d\n", ans1, ans2);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
