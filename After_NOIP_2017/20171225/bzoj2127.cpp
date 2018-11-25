#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e4+1e2;
const lli inf=0x3f3f3f3f3f3fLL;

int s[maxn<<1],t[maxn<<6],nxt[maxn<<6];
lli f[maxn<<6];
lli a[105][105],b[105][105];
int dep[maxn<<1];
lli ans;
int n,m,st,ed;

inline void coreaddedge(int from,int to,lli flow) {
	static int cnt = 1;
	t[++cnt] = to,
	f[cnt] = flow,
	nxt[cnt] = s[from],
	s[from] = cnt;
	//debug<<"edge added from = "<<from<<"to = "<<to<<"flow = "<<flow<<endl;
}
inline void singledge(int from,int to,lli flow) {
	/*if( to == ed )
		debug<<"from = "<<from<<endl;*/
	coreaddedge(from,to,flow);
	coreaddedge(to,from,0);
}
inline void doubledge(int from,int to,lli flow) {
	coreaddedge(from,to,flow);
	coreaddedge(to,from,flow);
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
inline lli dfs(int pos,lli flow) {
	//debug<<"pos = "<<pos<<"flow = "<<flow<<endl;
	if( pos == ed )
		return flow;
	lli ret = 0 , now = 0;
	for(int at=s[pos];at;at=nxt[at])
		if( dep[t[at]] > dep[pos] && f[at] ) {
			now = dfs(t[at],min(flow,f[at]));
			ret += now , flow -= now,
			f[at] -= now , f[at^1] += now;
			if( !flow )
				return ret;
		}
	//debug<<"ret = "<<ret<<endl;
	if( !ret )
		dep[pos] = -1;
	return ret;
}
inline lli dinic() {
	lli ret = 0 , now = 0;
	while( bfs() ) {
		//debug<<dep[ed]<<endl;
		while( now = dfs(st,inf) ) {
			//debug<<"now = "<<now<<endl;
			ret += now;
		}
	}
	return ret;
}

inline int cov(int xx,int yy) {
	return ( xx - 1 ) * m + yy;
}

inline void build() {
	static lli flow;
	st = cov( n , m ) + 1 , ed = cov( n , m ) + 2;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {
			scanf("%lld",&flow);
			ans += flow;
			singledge(st,cov(i,j),flow<<1);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {
			scanf("%lld",&flow);
			ans += flow;
			singledge(cov(i,j),ed,flow<<1);
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++) {
			scanf("%lld",&flow);
			ans += flow;
			a[i][j] += flow , a[i+1][j] += flow;
			doubledge(cov(i,j),cov(i+1,j),flow);
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++) {
			scanf("%lld",&flow);
			ans += flow;
			b[i][j] += flow , b[i+1][j] += flow;
			doubledge(cov(i,j),cov(i+1,j),flow);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++) {
			scanf("%lld",&flow);
			ans += flow;
			a[i][j] += flow , a[i][j+1] += flow;
			doubledge(cov(i,j),cov(i,j+1),flow);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++) {
			scanf("%lld",&flow);
			ans += flow;
			b[i][j] += flow , b[i][j+1] += flow;
			doubledge(cov(i,j),cov(i,j+1),flow);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {
			singledge(st,cov(i,j),a[i][j]);
			singledge(cov(i,j),ed,b[i][j]);
		}
}

int main() {
	scanf("%d%d",&n,&m);
	build();
	//debug<<"st = "<<st<<"ed = "<<ed<<endl;
	//debug<<"full ans = "<<ans<<endl;
	//debug<<"dinic = "<<dinic()<<endl;
	ans -= dinic() >> 1;
	printf("%lld\n",ans);
	
	return 0;
}



