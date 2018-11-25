#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=5e3+1e2,maxl=52;
const int inf=0x3f3f3f3f;

char in[maxl][maxl];
int s[maxn],t[maxn<<2],nxt[maxn<<2],f[maxn<<2],dep[maxn];
int xid[maxl][maxl],yid[maxl][maxl],xcnt,ycnt;
int n,m,st,ed;

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
			if( f[at] && !~dep[t[at]] ) {
				dep[t[at]] = dep[pos] + 1;
				q.push(t[at]);
			}
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
		while( now = dfs(st,inf) )
			ret += now;
	}
	return ret;
}

inline void gen() {
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if( in[i][j] != '#') {
				if( in[i][j-1] == '*' || in[i][j-1] == 'x' )
					xid[i][j] = xid[i][j-1];
				else xid[i][j] = ++xcnt;
				if( in[i-1][j] == '*' || in[i-1][j] == 'x' )
					yid[i][j] = yid[i-1][j];
				else yid[i][j] = ++ycnt;
			}
}

inline int covy(int p) {
	return xcnt + p;
}

inline void build() {
	st = xcnt + ycnt + 1 , ed = st + 1;
	for(int i=1;i<=xcnt;i++)
		singledge(st,i,1);
	for(int j=1;j<=ycnt;j++)
		singledge(covy(j),ed,1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if( in[i][j] == '*' )
				singledge(xid[i][j],covy(yid[i][j]),1);
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",in[i]+1);
	gen();
	build();
	printf("%d\n",dinic());
	return 0;
}
