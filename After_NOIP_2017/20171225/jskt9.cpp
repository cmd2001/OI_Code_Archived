#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e3+1e2,maxm=1e5+1e2;
const lli inf = 0x3f3f3f3f3f3fLL;

int s[maxn<<1],t[maxm<<1],nxt[maxm<<1];
lli f[maxm<<1];
int dep[maxn];
int n,m,st,ed;

inline void coreaddedge(int from,int to,lli flow) {
	static int cnt = 1;
	t[++cnt] = to,
	f[cnt] = flow,
	nxt[cnt] = s[from],
	s[from] = cnt;
}
inline void singledge(int from,int to,lli flow) {
	coreaddedge(from,to,flow);
	coreaddedge(to,from,0);
}
inline void doubledge(int from,int to,lli flow) {
	//debug<<"from = "<<from<<"to = "<<to<<endl;
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
inline lli dinic() {
	lli ret = 0 , now = 0;
	while( bfs() ) {
		while( now = dfs(st,inf) )
			ret += now;
	}
	return ret;
}

int main() {
	scanf("%d%d",&n,&m);
	st = 1 , ed = n;
	for(int i=1,u,v,d;i<=m;i++) {
		lli w;
		scanf("%d%d%lld%d",&u,&v,&w,&d);
		w = w * ( m + 1 ) + 1;
		++u , ++v;
		if( !d )
			singledge(u,v,w);
		else
			doubledge(u,v,w);
	}
	printf("%lld\n",dinic()%(m+1));
	//cout<<dinic()<<endl;
	return 0;
}
