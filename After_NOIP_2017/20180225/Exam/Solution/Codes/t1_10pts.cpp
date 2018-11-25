#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
const int maxn=17;
const double eps=1e-8;

struct Node {
	double t;
	int u,v;
	Node() {}
	Node(double tt,int uu,int vv) { t = tt , u = uu , v = vv ; }
	friend bool operator < (const Node &a,const Node &b) {
		return a.t < b.t;
	}
}ns[maxn*maxn];

int x[maxn],v[maxn],used[maxn],vis[maxn],n,cnt,ans;

inline void gnode(int a,int b) {
	if( x[a] < x[b] && v[a] < v[b] ) return;
	ns[++cnt] = Node((double)(x[b]-x[a])/(v[a]-v[b]),a,b);
}
inline void check() {
	memcpy(vis+1,used+1,sizeof(int)*n);
	for(int i=1,j,tp;i<=cnt;i=j+1) {
		j = i , tp = 0;
		while( j < cnt && std::fabs(ns[j+1].t-ns[i].t) <= eps ) ++j;
		for(int k=i;k<=j;k++) tp |= ( vis[ns[k].u] | vis[ns[k].v] );
		for(int k=i;k<=j;k++) vis[ns[k].u] |= tp , vis[ns[k].v] |= tp;
	}
	for(int i=1;i<=n;i++) if( !vis[i] ) return;
	++ans;
}
inline void dfs(int pos) {
	if( pos > n ) return check();
	used[pos] = 0 , dfs( pos + 1 ) ,
	used[pos] = 1 , dfs( pos + 1 ) ;
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",x+i,v+i);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			gnode(i,j);
	std::sort(ns+1,ns+1+cnt);
	dfs(1);
	printf("%d\n",ans);
	return 0;
}

