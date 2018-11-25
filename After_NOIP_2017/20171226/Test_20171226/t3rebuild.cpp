#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e5+1e2;

struct SegmentTree {
	int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3];
	lli sum[maxn<<3],dat[maxn<<3],mxu[maxn<<3],sizl[maxn<<3],lam;
	int cnt;
	
	inline void build(int pos,int ll,int rr) {
		l[pos] = ll , r[pos] = rr , sizl[pos] = 1;
		if( ll == rr )
			return;
		const int mid = ( ll + rr ) >> 1;
		build(lson[pos]=++cnt,ll,mid);
		build(rson[pos]=++cnt,mid+1,rr);
	}
	inline void update(int pos,int tar,lli x) {
		if( tar < l[pos] || r[pos] < tar )
			return;
		if( l[pos] == r[pos] && l[pos] == tar ) {
			dat[pos] = max( dat[pos] , x );
			if( dat[pos] >= lam )
				sum[pos] = dat[pos] ,
				sizl[pos] = 0;
			
		}
	}
}seg;
struct Node {
	lli z;
	int x,y;
	friend bool operator < (const Node &a,const Node &b) {
		return a.z < b.z;
	}
}ns[maxn];

int n;
lli zz,xx,yy,ans;
int mxx[maxn],mxy[maxn];

inline void init() {
	sort(ns+1,ns+1+n);
	ns[++n] = (Node){zz,0,0};
	for(int i=n;i;i--)
		mxx[i] = max( mxx[i+1] , ns[i].x ),
		mxy[i] = max( mxy[i+1] , ns[i].y );
	seg.build(seg.cnt=1,1,xx);
}

int main() {
	scanf("%d%lld%lld%lld",&n,&zz,&xx,&yy);
	for(int i=1;i<=n;i++)
		scanf("%lld%d%d",&ns[i].z,&ns[i].x,&ns[i].y);
	
	init();
	
	getans();
	
	printf("%lld\n",ans);
	
	return 0;
}

