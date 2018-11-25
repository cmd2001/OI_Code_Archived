#pragma GCC optimize(3)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int cmp;
struct Point {
	int d[2],id; // 0 means x , 1 means y .
	friend bool operator < (const Point &a,const Point &b) {
		return a.d[cmp] < b.d[cmp];
	}
}ps[maxn],nv[maxn];
int lson[maxn],rson[maxn],mx[maxn][2],mi[maxn][2],lazy[maxn],cnt;
int inx[maxn],iny[maxn],ind[maxn],ans[maxn];

inline void fill(int pos,const Point &p) {
	nv[pos] = p;
	for(int i=0;i<2;i++)
		mx[pos][i] = mi[pos][i] = p.d[i];
}
inline void update(int fa,int son) {
	if( !son ) return;
	for(int i=0;i<2;i++)
		mx[fa][i] = max( mx[fa][i] , mx[son][i] ) ,
		mi[fa][i] = min( mi[fa][i] , mi[son][i] );
}
inline void build(int pos,int dir,int l,int r) {
	const int mid = ( l + r ) >> 1;
	cmp = dir;
	nth_element(ps+l,ps+mid,ps+r+1);
	fill(pos,ps[mid]);
	if( l < mid ) build(lson[pos]=++cnt,dir^1,l,mid-1);
	if( mid < r ) build(rson[pos]=++cnt,dir^1,mid+1,r);
	update(pos,lson[pos]) , update(pos,rson[pos]);
}
inline bool insqr(int p,int sx,int tx,int sy,int ty) {
	return sx <= mi[p][0] && mx[p][0] <= tx
		&& sy <= mi[p][1] && mx[p][1] <= ty;
}
inline bool insqr(const Point &p,int sx,int tx,int sy,int ty) {
	return sx <= p.d[0] && p.d[0] <= tx
		&& sy <= p.d[1] && p.d[1] <= ty;
}
inline bool outsqr(int p,int sx,int tx,int sy,int ty) {
	return mx[p][0] < sx || tx < mi[p][0]
		|| mx[p][1] < sy || ty < mi[p][1];
}
inline void update(int pos,int sx,int tx,int sy,int ty) {
	if( !pos || outsqr(pos,sx,tx,sy,ty) ) return;
	if( insqr(pos,sx,tx,sy,ty) ) {
		++lazy[pos];
		return;
	}
	if( insqr(nv[pos],sx,tx,sy,ty) ) ans[nv[pos].id]++;
	update(lson[pos],sx,tx,sy,ty) , update(rson[pos],sx,tx,sy,ty);
}
inline void dfs(int pos) {
	ans[nv[pos].id] += lazy[pos];
	if( lson[pos] ) lazy[lson[pos]] += lazy[pos] , dfs(lson[pos]);
	if( rson[pos] ) lazy[rson[pos]] += lazy[pos] , dfs(rson[pos]);
}

int main() {
	freopen("berhatton.in","r",stdin);
	freopen("berhatton.out","w",stdout);
	static int n,k,cn;
	scanf("%d%d",&n,&k);
	for(int i=1,x,y;i<=n;i++) {
		scanf("%d%d%d",&x,&y,ind+i);
		inx[i] = x + y , iny[i] = x - y;
		ps[i] = (Point){ { inx[i] , iny[i] } , i };
	}
	build(cnt=1,0,1,n);
	for(int i=1;i<=n;i++) {
		update(1,
		max((lli)inx[i]-ind[i],-2147483648ll),
		min((lli)inx[i]+ind[i],2147483647ll),
		max((lli)iny[i]-ind[i],-2147483648ll),
		min((lli)iny[i]+ind[i],2147483647ll));
	}
	dfs(1);
	for(int i=1;i<=n;i++) cn += ( ans[i] > k );
	printf("%d\n",cn);
	for(int i=1;i<=n;i++) if( ans[i] > k ) printf("%d ",i);
	puts("");
	fclose(stdout);
	return 0;
}
