#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=3e2+1e1,maxm=maxn*maxn;
const int inf=0x3f3f3f3f;

int s[maxn<<1],t[maxm<<2],nxt[maxm<<2],f[maxm<<2];
int dep[maxn<<1];
char in[53][53];
int n,m,k,cnt,st,ed;

inline void core_addedge(int from,int to,int flow) {
	t[++cnt] = to,
	f[cnt] = flow,
	nxt[cnt] = s[from],
	s[from] = cnt;
}
inline void addedge(int from,int to,int flow) {
	core_addedge(from,to,flow);
	core_addedge(to,from,0);
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

inline int cov(int id,int sta) { // id means person , sta means statement , (0,1) means like && dislike.
	return id * 2 - 1 + sta;
}
inline void reset() {
	memset(s,0,sizeof(s));
	cnt = 1;
}
inline void build(int now) {
	reset();
	st = cov(n<<1,1) + 1 , ed = cov(n<<1,1) + 2;
	for(int i=1;i<=n;i++) {
		addedge(st,cov(i,0),now);
		addedge(cov(i,0),cov(i,1),k);
	}
	for(int i=n+1;i<=n<<1;i++) {
		addedge(cov(i,0),ed,now);
		addedge(cov(i,1),cov(i,0),k);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) {
			const int sta = ! (in[i][j] == 'Y');
			addedge(cov(i,sta),cov(j+n,sta),1);
		}
}
inline bool judge(int now) {
	build(now);
	return dinic() == now * n;
}

inline int getans() {
	int ll = 0 , rr = n + 1 , mid;
	while( rr != ll + 1 ) {
		mid = ( ll + rr ) >> 1;
		if( judge(mid) )
			ll = mid;
		else
			rr = mid;
	}
	return ll;
}

int main() {
	//freopen("dat.txt","r",stdin);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%s",in[i]+1);
	
	printf("%d\n",getans());
	
	return 0;
}

