#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=3e2+1e1,maxe=maxn*maxn;
const int inf = 0x3f3f3f3f;

int val[maxn],n,st,ed,ans;

namespace Bingraph {
	int in[maxn][maxn],fa[maxn];
	bool vis[maxn];
	
	inline bool dfs(int pos) { // pos is left point which has value .
		for(int i=1;i<=n;i++) if( in[pos][i] && !vis[i] ) {
			vis[i] = 1;
			if( !fa[i] || dfs(fa[i]) ) {
				fa[i] = pos;
				return 1;
			}
		}
		return 0;
	}
	inline void pir() {
		for(int i=1;i<=n;i++) {
			memset(vis,0,sizeof(vis));
			dfs(i);
		}
	}
}

namespace Flow {
	int s[maxn],t[maxe<<2],nxt[maxe<<2],f[maxe<<2],dep[maxn];
	
	inline void coredge(int from,int to,int flow) {
		static int cnt = 1;
		t[++cnt] = to , f[cnt] = flow ,
		nxt[cnt] = s[from] , s[from] = cnt;
	}
	inline void singledge(int from,int to,int flow) {
		coredge(from,to,flow) , coredge(to,from,0);
	}
	inline bool bfs() {
		memset(dep,-1,sizeof(dep)) , dep[st] = 0;
		queue<int> q; q.push(st);
		while( q.size() ) {
			const int pos = q.front(); q.pop();
			for(int at=s[pos];at;at=nxt[at])
				if( f[at] && !~dep[t[at]] )
					dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
		}
		return ~dep[ed];
	}
	inline int dfs(int pos,int flow) {
		if( pos == ed ) return flow;
		int ret = 0 , now = 0;
		for(int at=s[pos];at;at=nxt[at])
			if( f[at] && dep[t[at]] > dep[pos] ) {
				now = dfs(t[at],min(flow,f[at]));
				ret += now , flow -= now ,
				f[at] -= now , f[at^1] += now;
				if( !flow ) return ret;
			}
		if( !ret ) dep[pos] = -1;
		return ret;
	}
	inline int dinic() {
		int ret = 0 , now = 0;
		while( bfs() ) {
			while( now = dfs(st,inf) ) ret += now;
		}
		return ret;
	}
}

inline void build() {
	using namespace Flow;
	using namespace Bingraph;
	st = n + 1 , ed = st + 1;
	for(int i=1;i<=n;i++) val[i] = -val[i];
	for(int i=1;i<=n;i++) {
		if( val[i] > 0 ) {
			ans += val[i];
			singledge(st,i,val[i]);
		} else singledge(i,ed,-val[i]);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if( in[i][j] ) {
				singledge(i,fa[j],inf);
			}
}

int main() {
	freopen("z.in","r",stdin);
	freopen("z.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,t,x;i<=n;i++) {
		scanf("%d",&t);
		while( t-- ) {
			scanf("%d",&x);
			Bingraph::in[i][x] = 1;
		}
	}
	for(int i=1;i<=n;i++) scanf("%d",val+i);
	Bingraph::pir();
	build();
	ans -= Flow::dinic();
	printf("%d\n",-ans);
	fclose(stdout);
	return 0;
}
