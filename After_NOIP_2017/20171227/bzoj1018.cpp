#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],fa[maxn<<3];
int linked[maxn<<3][2],ver[maxn],hor[maxn][2]; 
int sum[maxn<<3];

struct Node {
	int f[2][2];
	int* operator [] (const int &x) {
		return f[x];
	}
	Node() {
		memset(f,0,sizeof(f));
	}
}ns[maxn<<3];
int n,m,cnt;

inline Node merge(int* h,Node a,Node b) {
	Node ret;
	ret.f[0][0] = ( a[0][0]&h[0]&b[0][0] ) | ( a[0][1]&h[1]&b[1][0] );
	ret.f[1][1] = ( a[1][1]&h[1]&b[1][1] ) | ( a[1][0]&h[0]&b[0][1] );
	ret.f[0][1] = ( a[0][0]&h[0]&b[0][1] ) | ( a[0][1]&h[1]&b[1][1] );
	ret.f[1][0] = ( a[1][1]&h[1]&b[1][0] ) | ( a[1][0]&h[0]&b[0][0] );
	return ret;
}

inline void build(int pos,int ll,int rr) {
	l[pos] = ll , r[pos] = rr;
	if( ll == rr ) {
		ns[pos][0][0] = ns[pos][1][1] = 1;
		linked[pos][0] = linked[pos][1] = 1;
		return;
	}
	const int mid = ( ll + rr ) >> 1;
	build(lson[pos]=++cnt,ll,mid);
	build(rson[pos]=++cnt,mid+1,rr);
	fa[lson[pos]] = fa[rson[pos]] = pos;
}
inline void update_ver(int pos,int tar,int sta) {
	if( tar < l[pos] || r[pos] < tar )
		return;
	if( l[pos] == r[pos] ) {
		sum[pos] = ver[tar] = sta;
		ns[pos][0][1] = ns[pos][1][0] = sta;
		return;
	}
	const int mid = ( l[pos] + r[pos] ) >> 1;
	update_ver(lson[pos],tar,sta);
	update_ver(rson[pos],tar,sta);
	ns[pos] = merge(hor[mid],ns[lson[pos]],ns[rson[pos]]);
	sum[pos] = sum[lson[pos]] + sum[rson[pos]]; // remember this
}
inline void update_hor(int pos,int tar,int at,int sta) {
	if( tar < l[pos] || r[pos] < tar )
		return;
	if( l[pos] == r[pos] ) {
		hor[tar][at] = sta;
		return;
	}
	const int mid = ( l[pos] + r[pos] ) >> 1;
	update_hor(lson[pos],tar,at,sta);
	update_hor(rson[pos],tar,at,sta);
	ns[pos] = merge(hor[mid],ns[lson[pos]],ns[rson[pos]]);
	linked[pos][0] = linked[lson[pos]][0] & hor[mid][0] & linked[rson[pos]][0],
	linked[pos][1] = linked[lson[pos]][1] & hor[mid][1] & linked[rson[pos]][1];
}
inline Node querymid(int pos,int ll,int rr) {
	if( !pos )
		exit(0);
	if( ll <= l[pos] && r[pos] <= rr )
		return ns[pos];
	const int mid = ( l[pos] + r[pos] ) >> 1;
	if( rr <= mid )
		return querymid(lson[pos],ll,rr);
	if( ll > mid )
		return querymid(rson[pos],ll,rr);
	return merge(hor[mid],querymid(lson[pos],ll,rr),querymid(rson[pos],ll,rr));
}
inline int queryver(int pos,int ll,int rr) {
	if( rr < l[pos] || r[pos] < ll )
		return 0;
	if( ll <= l[pos] && r[pos] <= rr )
		return sum[pos];
	return queryver(lson[pos],ll,rr) + queryver(rson[pos],ll,rr);
}
inline int downleft(int pos,int at) {
	if( l[pos] == r[pos] )
		return l[pos];
	const int mid = ( l[pos] + r[pos] ) >> 1;
	if( hor[mid][at] && linked[rson[pos]][at] )
		return downleft(lson[pos],at);
	return downleft(rson[pos],at);
}
inline int leftup(int pos,int at) {
	if( pos == 1 )
		return 1;
	if( pos == lson[fa[pos]] )
		return leftup(fa[pos],at);
	const int fmid = l[pos] - 1;
	if( hor[fmid][at] ) {
		if( linked[lson[fa[pos]]][at] )
			return leftup(fa[pos],at);
		return downleft(lson[fa[pos]],at);
	}
	return l[pos];
}
inline int downright(int pos,int at) {
	if( l[pos] == r[pos] )
		return r[pos];
	const int mid = ( l[pos] + r[pos] ) >> 1;
	if( hor[mid][at] && linked[lson[pos]][at] )
		return downright(rson[pos],at);
	return downright(lson[pos],at);
}
inline int rightup(int pos,int at) {
	if( pos == 1 )
		return n;
	if( pos == rson[fa[pos]] )
		return rightup(fa[pos],at);
	const int fmid = r[pos];
	if( hor[fmid][at] ) {
		if( linked[rson[fa[pos]]][at] )
			return rightup(fa[pos],at);
		return downright(rson[fa[pos]],at);
	}
	return r[pos];
}
inline int findpos(int pos,int tar) {
	while( l[pos] != r[pos] ) {
		const int mid = ( l[pos] + r[pos] ) >> 1;
		if( tar <= mid )
			pos = lson[pos];
		else
			pos = rson[pos];
	}
	return pos;
}

inline void solve_case(int x,int y,int xx,int yy) {
	int sta = y , stb = yy , ans = 0;
	const int mostl = max( leftup(findpos(1,x),0) , leftup(findpos(1,x),1) );
	const int mostr = min( rightup(findpos(1,xx),0) , rightup(findpos(1,xx),1) );
	if( queryver(1,mostl,x) )
		sta = 3;
	if( queryver(1,xx,mostr) )
		stb = 3;
	Node md = querymid(1,x,xx);
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			if( ( sta & (1<<i) ) && ( stb & (1<<j) ) )
				ans |= md[i][j];
	puts(ans?"Y":"N");
}

char com[10];
int x,y,xx,yy;

inline void explain() {
	int sta = *com == 'O';
	if( y == yy )
		update_hor(1,x,y-1,sta);
	else if( x == xx ) {
		update_ver(1,x,sta);
	}
}

int main() {
	scanf("%d",&n);
	build(cnt=1,1,n);
	int cc = 0;
	while( scanf("%s",com) == 1 && *com != 'E' ) {
		scanf("%d%d%d%d",&y,&x,&yy,&xx);
		if( x > xx )
			swap(x,xx) , swap(y,yy);
		if( *com == 'A' )
			solve_case(x,y,xx,yy);
		else
			explain();
	}
	
	return 0;
	
}
