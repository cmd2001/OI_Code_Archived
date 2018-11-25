#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cstdlib>
#define debug cout
using namespace std;
const int maxn=40*40+1e1,maxm=maxn*maxn;
const int inf=0x3f3f3f3f;

int s[maxn<<1],t[maxm<<1],nxt[maxm<<1],f[maxm<<1];
int dep[maxn<<1];
char in[25][25];
int n,m,c,st,ed,ans;

inline void addedge(int from,int to,int flow) {
	static int cnt = 1;
	t[++cnt] = to,
	f[cnt] = flow,
	nxt[cnt] = s[from],
	s[from] = cnt;
}

inline bool bfs() {
	memset(dep,-1,sizeof(dep));
	queue<int> q;
	q.push(st);
	dep[st] = 0;
	while( q.size() ) {
		const int pos = q.front();
		//debug<<"pos = "<<pos<<endl;
		q.pop();
		for(int at=s[pos];at;at=nxt[at])
			if( f[at] && dep[t[at]] == -1 ) {
				dep[t[at]] = dep[pos] + 1,
				q.push(t[at]);
			}
	}
	//debug<<"st = "<<st<<"ed = "<<ed<<"deped = "<<dep[ed]<<endl;
	return dep[ed] != -1;
}
inline int dfs(int pos,int flow) {
	//debug<<"pos = "<<pos<<endl;
	if( pos == ed )
		return flow;
	int ret = 0 , now = 0;
	for(int at=s[pos];at;at=nxt[at]) 
		if( f[at] && dep[t[at]] > dep[pos]) {
		while( now = dfs(t[at],min(flow,f[at])) ) {
			ret += now,
			flow -= now,
			f[at] -= now,
			f[at^1] += now;
			if( !flow )
				return ret;
		}
	}
	//debug<<"ret = "<<ret<<endl;
	return ret;
}
inline int dinic() {
	int ret = 0 , now = 0;
	while( bfs() ) {
		while( now = dfs(st,inf) ) {
			//debug<<"now = "<<now<<endl;
			ret += now;
		}
	}
	return ret;
}

inline int cov(int xx,int yy,int sta) { // 0 means in point , 1 means out point;
	return ( ( xx - 1 ) * m + yy  ) * 2 + sta - 1;
}
inline void explain() {
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if( in[i][j] - '0' ) {
				addedge(cov(i,j,0),cov(i,j,1),in[i][j]-'0');
				addedge(cov(i,j,1),cov(i,j,0),0);
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int xx=1;xx<=n;xx++)
				for(int yy=1;yy<=m;yy++) {
					if( i == xx && j == yy )
						continue;
					if( abs(i-xx) + abs(j-yy) <= c ) {
						addedge(cov(i,j,1),cov(xx,yy,0),inf);
						addedge(cov(xx,yy,0),cov(i,j,1),0);
					}
				}
}
inline bool judge(int xx,int yy) {
	if( xx <= c || yy <= c || n - xx + 1 <= c || m - yy + 1 <= c )
		return 1;
	return 0;
}
inline void init() {
	st = cov(n,m,1) + 1 , ed = cov(n,m,1) + 2;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {
			if( judge(i,j) ) {
				//debug<<"i = "<<i<<"j = "<<j<<endl;
				addedge(cov(i,j,1),ed,inf);
				addedge(ed,cov(i,j,1),0);
			}
			/*else
				debug<<"not i = "<<i<<"j = "<<j<<endl;*/
			if( in[i][j] == 'L' ) {
				++ans;
				addedge(st,cov(i,j,0),1),
				addedge(cov(i,j,0),st,0);
			}
		}
}
inline void readin() {
	for(int i=1;i<=n;i++)
		scanf("%s",in[i]+1);
}

int main() {
	scanf("%d%d%d",&n,&m,&c);
	
	readin();
	explain();
	readin();
	init();
	//debug<<"inited"<<endl;
	
	
	printf("%d\n",ans-=dinic());
	
	return 0;
}
