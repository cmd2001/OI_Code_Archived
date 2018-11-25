#include<bits/stdc++.h>
using namespace std;
const int maxn=3e2+1e1;

inline int _(int r) {
	return rand() % r + 1;
}
set<int> s[maxn];
int ini[maxn];

int main() {
	srand((unsigned long long)new char);
	static int n = 5;
	for(int i=1;i<=n;i++) ini[i] = i;
	random_shuffle(ini+1,ini+1+n);
	for(int i=1,t;i<=n;i++) {
		t = _(n) , s[i].insert(ini[i]);
		while(t--) s[i].insert(_(n));
	}
	printf("%d\n",n);
	for(int i=1;i<=n;i++) {
		printf("%d ",s[i].size());
		for(set<int>::iterator it=s[i].begin();it!=s[i].end();it++) printf("%d ",*it);
		puts("");
	}
	for(int i=1;i<=n;i++) printf("%d ",((rand()&1)?1:-1)*_(10));
	return 0;
}
