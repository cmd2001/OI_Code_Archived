#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],dep[maxn],top[maxn],son[maxn],siz[maxn],id[maxn],cov[maxn];
int in[maxn],bin[maxn];
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],lazy[maxn<<3],cnt;
int n,m;

struct Node {
	int cl,cr,sum;
	friend Node operator + (const Node &a,const Node &b) {
		return (Node){a.cl,b.cr,a.sum+b.sum-(a.cr==b.cl)};
	}
	inline void fill(int c) {
		cl = cr = c , sum = 1;
	}
	inline Node reverse() {
		return (Node){cr,cl,sum};
    }
}ns[maxn<<3];

inline void build(int pos,int ll,int rr) {
	l[pos] = ll , r[pos] = rr;
	if( ll == rr ) {
		ns[pos].fill(bin[ll]);
		return;
	}
	const int mid = ( ll + rr ) >> 1;
	build(lson[pos]=++cnt,ll,mid);
	build(rson[pos]=++cnt,mid+1,rr);
	ns[pos] = ns[lson[pos]] + ns[rson[pos]];
}
inline void push(int pos) {
	if( lazy[pos] ) {
		if( lson[pos] ) {
			ns[lson[pos]].fill(lazy[pos]);
			lazy[lson[pos]] = lazy[pos];
		}
		if( rson[pos] ) {
			ns[rson[pos]].fill(lazy[pos]);
			lazy[rson[pos]] = lazy[pos];
		}
		lazy[pos] = 0;
	}
}
inline void update(int pos,int ll,int rr,int cc) {
	if( rr < l[pos] || r[pos] < ll )
		return;
	if( ll <= l[pos] && r[pos] <= rr ) {
		ns[pos].fill(lazy[pos]=cc);
		return;
	}
	push(pos);
	update(lson[pos],ll,rr,cc);
	update(rson[pos],ll,rr,cc);
	ns[pos] = ns[lson[pos]] + ns[rson[pos]];
}
inline Node query(int pos,int ll,int rr) {
	if( ll <= l[pos] && r[pos] <= rr )
		return ns[pos];
	const int mid = ( l[pos] + r[pos] ) >> 1;
	push(pos);
	if( rr <= mid )
		return query(lson[pos],ll,rr);
	else if( ll > mid )
		return query(rson[pos],ll,rr);
	return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
}

inline void addedge(int from,int to) {
	static int cnt = 0;
	t[++cnt] = to ,
	nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos) {
	siz[pos] = 1;
	for(int at=s[pos];at;at=nxt[at])
		if( t[at] != fa[pos] ) {
			dep[t[at]] = dep[pos] + 1,
			fa[t[at]] = pos;
			pre(t[at]);
			siz[pos] += siz[t[at]];
			if( siz[t[at]] > siz[son[pos]] )
				son[pos] = t[at];
		}
}
inline void dfs(int pos) {
	top[pos] = son[fa[pos]] == pos ? top[fa[pos]] : pos;
	id[pos] = top[pos] == top[fa[pos]] ? id[fa[pos]] + 1 : 1;
	for(int at=s[pos];at;at=nxt[at])
		if( t[at] != fa[pos] )
			dfs(t[at]);
	if( !son[pos] ) {
		for(int p=pos;;p=fa[p]) {
			bin[id[p]] = in[p];
			if( p == top[pos] )
				break;
		}
		cov[top[pos]] = ++cnt;
		build(cov[top[pos]],id[top[pos]],id[pos]);
	}
}
inline void chain(int a,int b,int cc) {
	while( top[a] != top[b] ) {
		if( dep[top[a]] > dep[top[b]] ) {
			update(cov[top[a]],id[top[a]],id[a],cc);
			a = fa[top[a]];
		}
		else {
			update(cov[top[b]],id[top[b]],id[b],cc);
			b = fa[top[b]];
		}
	}
	if( dep[a] > dep[b] )
		swap(a,b);
	update(cov[top[a]],id[a],id[b],cc);
}
inline Node getans(int a,int b) {
	if( dep[a] > dep[b] )
		swap(a,b);
	Node qa = query(cov[top[a]],id[a],id[a]) , qb = query(cov[top[b]],id[b],id[b]);
	while( top[a] != top[b] ) {
		if( dep[top[a]] > dep[top[b]] ) {
			qa = query(cov[top[a]],id[top[a]],id[a]) + qa;
			a = fa[top[a]];
		}
		else {
			qb = query(cov[top[b]],id[top[b]],id[b]) + qb;
			b = fa[top[b]];
		}
	}
	if( dep[a] > dep[b] )
		swap(a,b) ,
		swap(qa,qb);
	qb = query(cov[top[a]],id[a],id[b]) + qb;
	qa = qa.reverse() + qb;
	return qa;
}

int main() {
	static char com[10];
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",in+i);
	for(int i=1,a,b;i<n;i++) {
		scanf("%d%d",&a,&b);
		addedge(a,b) , addedge(b,a);
	}
	pre(1);
	dfs(1);
	for(int i=1,a,b,cc;i<=m;i++) {
		scanf("%s%d%d",com,&a,&b);
		if( *com == 'C' ) {
			scanf("%d",&cc);
			chain(a,b,cc);
		}
		else {
			Node ans = getans(a,b);
			printf("%d\n",ans.sum);
		}
	}
	
	return 0;
}
