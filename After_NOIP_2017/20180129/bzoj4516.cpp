#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
const int maxn=2e5+1e2;

map<int,int> ch[maxn];
int fa[maxn],len[maxn],root,last,cnt;
long long ans;

inline int NewNode(int ll) {
	len[++cnt] = ll;
	return cnt;
}
inline void extend(int x) {
	int p = last;
	int np = NewNode(len[p]+1);
	while( p && ch[p].find(x) == ch[p].end() ) ch[p][x] = np , p = fa[p];
	if( !p ) fa[np] = root;
	else {
		int q = ch[p][x];
		if( len[q] == len[p] + 1 ) fa[np] = q;
		else {
			int nq = NewNode(len[p]+1);
			ch[nq] = ch[q];
			fa[nq] = fa[q] , fa[q] = fa[np] = nq;
			while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
		}
	}
	last = np;
	ans += len[last] - len[fa[last]];
}

int main() {
	static int n,x;
	scanf("%d",&n);
	last = root = NewNode(0);
	for(int i=1;i<=n;i++) {
		scanf("%d",&x);
		extend(x);
		printf("%lld\n",ans);
	}
	return 0;
}
