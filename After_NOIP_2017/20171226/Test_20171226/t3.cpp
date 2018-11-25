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
	lli dat[maxn<<3],sum[maxn<<3],slm[maxn<<3],mxu[maxn<<3],lam;
	int cnt;
	
	inline void build(int pos,int ll,int rr) {
		l[pos] = ll , r[pos] = rr , slm[pos] = 1;
		if( ll == rr )
			return;
		const int mid = ( ll + rr ) >> 1;
		build(lson[pos]=++cnt,ll,mid);
		build(rson[pos]=++cnt,mid+1,rr);
	}
	inline void update(int pos,int tar,lli x) {
		if( tar < l[pos] || r[pos] < tar )
			return;
		if( l[pos] == r[pos] && tar == l[pos] ) {
			dat[pos] = max( dat[pos] , x );
			if( dat[pos] >= lam )
				slm[pos] = 0;
			if( !slm[pos] )
				sum[pos] = dat[pos];
			mxu[pos] = slm[pos] ? dat[pos] : -1;
			return;
		}
		update(lson[pos],tar,x);
		update(rson[pos],tar,x);
		sum[pos] = sum[lson[pos]] + sum[rson[pos]];
		slm[pos] = slm[lson[pos]] + slm[rson[pos]];
		mxu[pos] = max( mxu[lson[pos]] , mxu[rson[pos]] );
	}
	inline void upgrade(int pos) {
		if( ( !slm[pos] ) || mxu[pos] < lam )
			return;
		if( l[pos] == r[pos] ) {
			slm[pos] = 0;
			sum[pos] = dat[pos];
			mxu[pos] = -1;
			return;
		}
		upgrade(lson[pos]);
		upgrade(rson[pos]);
		sum[pos] = sum[lson[pos]] + sum[rson[pos]];
		slm[pos] = slm[lson[pos]] + slm[rson[pos]];
		mxu[pos] = max( mxu[lson[pos]] , mxu[rson[pos]] );
	}
	inline void setlam(lli x) {
		lam = x;
		upgrade(1);
	}
	inline lli query(int pos,int ll,int rr) {
		if( rr < l[pos] || r[pos] < ll )
			return 0;
		if( ll <= l[pos] && r[pos] <= rr )
			return sum[pos] + slm[pos] * lam;
		return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
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

inline void getans() {
	for(int i=1;i<=n;i++) {
		const lli len = ns[i].z - ns[i-1].z;
		seg.setlam(mxy[i]);
		lli full = ( xx - mxx[i] ) * yy;
		lli minus = seg.query(1,mxx[i]+1,xx);
		if( i != 1 )
			ans += ( full - minus ) * len;
		if( full != minus )
			debug<<"mxx = "<<mxx[i]<<"mxy = "<<mxy[i]<<endl,
			debug<<"full = "<<full<<"minus = "<<minus<<endl,
			debug<<"len = "<<len<<endl;
		seg.update(1,ns[i].x,ns[i].y);
	}
}
inline void init() {
	sort(ns+1,ns+1+n);
	ns[++n] = (Node){zz,0,0};
	for(int i=n;i;i--)
		mxx[i] = max( mxx[i+1] , ns[i].x ),
		mxy[i] = max( mxy[i+1] , ns[i].y );
	seg.build(seg.cnt=1,1,xx);
	seg.setlam(0x3f3f3f3f);
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

