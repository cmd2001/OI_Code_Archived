#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=7e4+1e2;
const int inf=0x3f3f3f3f;
const int dx[] = {0,0,1,-1} , dy[] = {1,-1,0,0};

int in[42][42][42];
int s[maxn],t[maxn<<4],nxt[maxn<<4],f[maxn<<4];
int dep[maxn];
int p,q,r,z,st,ed;

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

inline int cov(int x,int y,int h) {
	return ( h - 1 ) * p * q + ( x - 1 ) * q + y;
}
inline bool judge(int x,int y) {
	return x>0 && x<=p && y>0 && y<=q;
}

int main() {
	scanf("%d%d%d%d",&p,&q,&r,&z);
	for(int i=1;i<=r;i++)
		for(int j=1;j<=p;j++)
			for(int k=1;k<=q;k++)
				scanf("%d",&in[i][j][k]);
	st = cov(p,q,r+1) + 1 , ed = st + 1;
	/*debug<<"st = "<<st<<"ed = "<<ed<<endl;debug<<endl;
	for(int dep=1;dep<=r+1;dep++) {
		for(int i=1;i<=p;i++) {
			for(int j=1;j<=q;j++)
				debug<<cov(i,j,dep)<<" ";
			debug<<endl;
		}
		debug<<endl;
	}*/
	for(int i=1;i<=p;i++)
		for(int j=1;j<=q;j++)
			addedge(st,cov(i,j,r+1),inf);
	for(int i=1;i<=p;i++)
		for(int j=1;j<=q;j++)
			addedge(cov(i,j,1),ed,inf);
	for(int dep=r;dep;dep--)
		for(int i=1;i<=p;i++)
			for(int j=1;j<=q;j++)
				addedge(cov(i,j,dep+1),cov(i,j,dep),in[dep][i][j]);
	for(int dep=1;dep+z<=r;dep++)
		for(int i=1;i<=p;i++)
			for(int j=1;j<=q;j++)
				for(int k=0;k<4;k++) {
					const int tx = i + dx[k] , ty = j + dy[k];
					if( judge(tx,ty) )
						addedge(cov(i,j,dep),cov(tx,ty,dep+z),inf);
				}
				
	printf("%d\n",dinic());
	
	return 0;
}

