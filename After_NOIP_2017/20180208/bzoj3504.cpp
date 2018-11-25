#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=100,maxe=maxn*maxn;
const int inf=0x3f3f3f3f;

char in[maxn][maxn];
int s[maxn],t[maxe<<1],nxt[maxe<<1],f[maxe<<1],dep[maxn];
int n,cnt,st,ed;

inline void coredge(int from,int to,int flow) {
	t[++cnt] = to , f[cnt] = flow ,
	nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow) {
	coredge(from,to,flow) , coredge(to,from,0);
}
inline void doubledge(int from,int to,int flow) {
	coredge(from,to,flow) , coredge(to,from,flow);
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
	while( bfs() )
		while( now = dfs(st,inf) )
			ret += now;
	return ret;
}
inline void reset() {
	memset(s,0,sizeof(s)) , cnt = 1;
}
inline bool judge(int a1,int a2,int b1,int b2,int aa,int bb) {
	reset();
	singledge(st,a1,aa) , singledge(a2,ed,aa) ,
	singledge(st,b1,bb) , singledge(b2,ed,bb) ;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if( in[i][j] == 'N' ) doubledge(i,j,inf);
			else if( in[i][j] == 'O' ) doubledge(i,j,1);
	return dinic() == aa + bb;
}
int main() {
	static int a1,a2,b1,b2,aa,bb;
	while( scanf("%d",&n) == 1 ) {
		st = n + 1 , ed = st + 1;
		scanf("%d%d%d%d%d%d",&a1,&a2,&aa,&b1,&b2,&bb) ,
		++a1 , ++a2 , ++b1 , ++b2;
		for(int i=1;i<=n;i++)
			scanf("%s",in[i]+1);
		if( !judge(a1,a2,b1,b2,aa,bb) || !judge(a1,a2,b2,b1,aa,bb) ) puts("No");
		else puts("Yes");
	}
	return 0;
}


