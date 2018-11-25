#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define debug cout
using namespace std;
const int maxn=2e2+1e1,maxm=maxn*maxn,maxe=55;
const int inf=0x3f3f3f3f;

int k[maxe],sum[maxn],n,full;
int st,ed;

struct Elevator {
	int h,x,y;
	friend bool operator < (const Elevator &a,const Elevator &b) {
		if( a.h != b.h ) return a.h < b.h;
		if( a.x != b.x ) return a.x < b.x;
		return a.y < b.y;
	}
	friend bool operator == (const Elevator &a,const Elevator &b) {
		return a.h == b.h && a.x == b.x && a.y == b.y;
	}
};
vector<Elevator> v;

namespace Flow {
	int s[maxn],t[maxm<<1],nxt[maxm<<1],f[maxm<<1],dep[maxn];
	
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
			for(int at=s[pos];at;at=nxt[at]) {
				if( f[at] && !~dep[t[at]] ) dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
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
			while( ( now = dfs(st,inf) ) ) ret += now;
		}
		return ret;
	}
}

inline int covdep(int dep,int pos) {
	return sum[dep-1] + pos;
}
inline int cov(int id,int tpe) { // tpe == 0 means out point , 1 means in point
	return id * 2 + tpe - 1;
}

inline void pre() {
	sort(v.begin(),v.end());
	unsigned len = unique(v.begin(),v.end()) - v.begin();
	for(int i=1;i<=n;i++) sum[i] = sum[i-1] + k[i];
	full = sum[n] , st = full * 2 + 1 , ed = full * 2 + 2;
	for(unsigned i=0;i<len;i++) {
		const int x = covdep(v[i].h,v[i].x);
		const int y = covdep(v[i].h!=n?v[i].h+1:1,v[i].y);
		if( v[i].h & 1 ) {
			Flow::singledge(cov(x,1),cov(y,0),1);
		} else {
			Flow::singledge(cov(y,1),cov(x,0),1);
		}
	}
	for(int i=1;i<=full;i++)
		Flow::singledge(cov(i,0),cov(i,1),1);
	for(int i=1;i<=n;i++)
		if( i & 1 ) {
			for(int j=1;j<=k[i];j++)
				Flow::singledge( st , cov(sum[i-1]+j,0) , 1 );
		} else {
			for(int j=1;j<=k[i];j++)
				Flow::singledge( cov(sum[i-1]+j,1) , ed , 1 );
		}
}

int main() {
	freopen("mall.in","r",stdin);
	freopen("mall.out","w",stdout);
	static int h,x,y,ans;
	scanf("%d",&n);
	int t = 0;
	while( scanf("%d%d%d",&x,&y,&h) == 3 ) {
		v.push_back((Elevator){h,x,y});
		k[h] = max( k[h] , x ) , k[h!=n?h+1:1] = max( k[h!=n?h+1:1] , y );
		++t;
	}
	pre();
	ans = full - Flow::dinic();
	printf("%d\n",ans);
	fclose(stdout);
	return 0;
}

