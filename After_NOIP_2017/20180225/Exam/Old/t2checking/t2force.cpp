#include<bits/stdc++.h>
using namespace std;
const int maxn=32;

bitset<maxn> in[maxn];
int v[maxn];
int n,ans;

inline void dfs(int pos,int val,int siz,bitset<maxn> sta) {
	if( pos > n ) {
		if( siz == sta.count() ) ans = min(ans,val);
		return;
	}
	dfs(pos+1,val,siz,sta);
	dfs(pos+1,val+v[pos],siz+1,sta|in[pos]);
}

int main() {
	scanf("%d",&n);
	for(int i=1,t,x;i<=n;i++) {
		scanf("%d",&t);
		while( t-- ) {
			scanf("%d",&x);
			in[i][x] = 1;
		}
	}
	for(int i=1;i<=n;i++) scanf("%d",v+i);
	dfs(1,0,0,in[0]);
	printf("%d\n",ans);
	return 0;
}
