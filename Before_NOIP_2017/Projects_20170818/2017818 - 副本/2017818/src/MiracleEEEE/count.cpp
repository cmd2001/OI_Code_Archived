#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef long long ll;
int n;
ll p;
struct mat {
	ll s[17][17];
	inline void clear() {
		memset(s, 0, sizeof(s));
	}
	inline void unit() {
		clear();
		for (int i = 0; i < 16; ++i) {
			s[i][i] = 1;
		}
	}
};
mat t;
mat operator * (mat a, mat b) {
	mat c;
	c.clear();
	for (int k = 0; k < 16; ++k) {
		for (int i = 0; i < 16; ++i) {
			for (int j = 0; j < 16; ++j) {
				c.s[i][j] = (c.s[i][j] + a.s[i][k] * b.s[k][j] % p) % p;
			}
		}
	}
	return c;
}
inline bool check(int x) {
	int cnt = 0;
	for (int i = 0; i < 4; ++i) {
		if (!(x & (1 << i))) {
			++cnt;
		}
		else {
			if (cnt & 1) {
				return false;
			}
			cnt = 0;
		}
	}
	if (cnt & 1) {
		return false;
	}
	return true;
}
inline void init() {
	for (int i = 0; i <= 15; ++i) {
		for (int j = 0; j <= 15; ++j) {
			if ((i & j) == 0 && check(i | j)) {
				t.s[i][j] = 1;
			}
		}
	}
}
inline mat exp(mat a, int x) {
	mat u;
	u.unit();
	while (x) {
		if (x & 1) {
			u = u * a;
		}
		a = a * a;
		x >>= 1;
	}
	return u;
}
int main() {
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	init();
	while (scanf("%d%lld", &n, &p) && n + p) {
		mat ans = exp(t, n);
		printf("%lld\n", ans.s[0][0]);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
