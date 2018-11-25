#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=5e4+1e2;

int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3];
int mid[maxn<<3];
double k[maxn<<3],b[maxn<<3];
int n,m,cnt;

inline double f(const double &k,const double &b,const int &x) {
	return k * ( x - 1 ) + b;
}
inline void build(int pos,int ll,int rr) {
	l[pos] = ll , r[pos] = rr;
	if( ll == rr )
		return;
	mid[pos] = ( ll + rr ) >> 1;
	build(lson[pos]=++cnt,ll,mid[pos]);
	build(rson[pos]=++cnt,mid[pos]+1,rr);
}
inline void update(int pos,double kk,double bb) {
	if( f(kk,bb,l[pos]) <= f(k[pos],b[pos],l[pos]) && f(kk,bb,r[pos]) <= f(k[pos],b[pos],r[pos]) )
		return;
	if( l[pos] == r[pos] ) {
		k[pos] = kk , b[pos] = bb;
		return;
	}
	if( kk > k[pos] ) {
		if( f(kk,bb,mid[pos]) > f(k[pos],b[pos],mid[pos]) ) {
			update(lson[pos],k[pos],b[pos]);
			k[pos] = kk , b[pos] = bb;
		}
		else
			update(rson[pos],kk,bb);
	}
	else {
		if( f(kk,bb,mid[pos]) > f(k[pos],b[pos],mid[pos]) ) {
			update(rson[pos],k[pos],b[pos]);
			k[pos] = kk , b[pos] = bb;
		}
		else
			update(lson[pos],kk,bb);
	}
}
inline double query(int pos,int tar) {
	if( l[pos] == r[pos] )
		return f(k[pos],b[pos],tar);
	if( tar <= mid[pos] )
		return max( f(k[pos],b[pos],tar) , query(lson[pos],tar) );
	else if( tar > mid[pos] )
		return max( f(k[pos],b[pos],tar) , query(rson[pos],tar) );
}

int main() {
	freopen("dat.txt","r",stdin);
	freopen("my.txt","w",stdout);
	static char com[20];
	static double qq,kk,bb;
	scanf("%d",&m) , n = 5e4;
	build(cnt=1,1,n);
	for(int i=1,p;i<=m;i++) {
		scanf("%s",com);
		if( *com == 'Q' ) {
			scanf("%d",&p);
			qq = query(1,p);
			//debug<<"qq = "<<qq<<endl;
			printf("%d\n",((int)qq)/100);
		}
		else {
			scanf("%lf%lf",&bb,&kk);
			update(1,kk,bb);
		}
	}
	return 0;
}
