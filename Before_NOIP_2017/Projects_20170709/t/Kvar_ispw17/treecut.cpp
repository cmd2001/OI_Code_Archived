#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define N 10010
using namespace std;
int n, siz[N];
vector<int> v[N];
vector<int> ans;
int tot;

bool vis[N];
void dfs1(int x) {
//	int len = v[x].size();
//	if(len == 1) {
//		siz[x] = 1;
//		return;
//	}
	vis[x] = 1;
	siz[x] = 1;
	vector<int>::iterator it;
	for(it = v[x].begin(); it != v[x].end(); it++) {
		int y = *it;
		if(vis[y]) continue;
		dfs1(y);
		siz[x] += siz[y];
	}
}

void dfs2(int x) {
	int a = tot - siz[x];
	vector<int> b;
	vector<int>::iterator it;
	vis[x] = 1;
	for(it = v[x].begin(); it != v[x].end(); it++) {
		int y = *it;
		if(vis[y]) continue;
		b.push_back(siz[y]);
		dfs2(y);
	}
	if(a <= n/2){
		for(it = b.begin(); it != b.end(); it++) {
			if(*it > n/2) return;
		}
		ans.push_back(x);
	}
}

int main() {
	freopen("treecut.in", "r", stdin);
	freopen("treecut.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i < n; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		v[a].push_back(b);
		v[b].push_back(a);
	}
	dfs1(1);
	tot = siz[1];
	memset(vis, 0, sizeof vis);
	dfs2(1);
	vector<int>::iterator it;
	sort(ans.begin() , ans.end());
	for(it = ans.begin(); it != ans.end(); it++) {
		int t = *it;
		printf("%d\n", t);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

