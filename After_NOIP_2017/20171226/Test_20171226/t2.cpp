#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=5e+3+1e2,maxm=maxn*50;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm],nxt[maxm],f[maxm];
int dep[maxn];
char in[55][55];
int n,m,st,ed;

inline void coredge(int from,int to,int flow) {
	static int cnt = 1;
	t[++cnt] = to,
	f[cnt] = flow,
	nxt[cnt] = s[from],
	s[from] = cnt;
}
inline void addedge(int from,int to,int flow) {
	coredge(from,to,flow);
	coredge(to,from,0);
}

inline bool bfs() {
	memset(dep,-1,sizeof(dep));
	dep[st] = 0;
	queue<int> q;
	q.push(st);
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
	if( pos == ed )
		return flow;
	int ret = 0 , now = 0;
	for(int at=s[pos];at;at=nxt[at])
		if( f[at] && dep[t[at]] > dep[pos] ) {
			now = dfs(t[at],min(flow,f[at]));
			ret += now , flow -= now,
			f[at] -= now , f[at^1] += now;
			if( !flow )
				return ret;
		}
	if( !ret )
		dep[pos] = -1;
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

inline int cov(int xx,int yy,int sta=0) { // 0 means full point or in point , 1 means out point.
	return ( ( xx - 1 ) * m + yy ) * 2 - 1 + sta;
}
inline bool judge(int xx,int yy) {
	return xx > 0 && xx <= n && yy > 0 && yy <= m && in[xx][yy]=='.';
}
inline void explain() {
	st = cov(n,m,1) + 1 , ed = cov(n,m,1) + 2;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if( in[i][j] == '.' && ( ( i + j ) & 1 ) ) {
				if( i & 1 )
					addedge(st,cov(i,j),1);
				else
					addedge(cov(i,j),ed,1);
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if( in[i][j] == '.' && ! ( ( i + j ) & 1 ) ) {
				addedge(cov(i,j,0),cov(i,j,1),1);
				if( i & 1 ) {
					if( judge(i-1,j) )
						addedge(cov(i,j,1),cov(i-1,j),1);
					if( judge(i+1,j) )
						addedge(cov(i,j,1),cov(i+1,j),1);
					if( judge(i,j+1) )
						addedge(cov(i,j+1),cov(i,j,0),1);
					if( judge(i,j-1) )
						addedge(cov(i,j-1),cov(i,j,0),1);
				}
				else {
					if( judge(i-1,j) )
						addedge(cov(i-1,j),cov(i,j,0),1);
					if( judge(i+1,j) )
						addedge(cov(i+1,j),cov(i,j,0),1);
					if( judge(i,j+1) )
						addedge(cov(i,j,1),cov(i,j+1),1);
					if( judge(i,j-1) )
						addedge(cov(i,j,1),cov(i,j-1),1);
				}
			}
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",in[i]+1);
	
	explain();
	
	printf("%d\n",dinic());
	
	return 0;
}
