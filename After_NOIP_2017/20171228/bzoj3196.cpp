#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define lowbit(x) (x&-x)
#define debug cout
using namespace std;
const int maxn=5e4+1e2,maxm=8e6+1e2;

int lson[maxm],rson[maxm];
short siz[maxm];
int root[maxn],bit[maxn],cnt;
lli ope[maxn][4],srt[maxn<<1],val[maxn];
int n,m,len;

inline void insert(int pos,int ll,int rr,int tar,int add) {
	siz[pos] += add;
	if( ll == rr )
		return;
	const int mid = ( ll + rr ) >> 1;
	if( tar <= mid ) {
		if( !lson[pos] )
			lson[pos] = ++cnt;
		insert(lson[pos],ll,mid,tar,add);
	}
	else {
		if( !rson[pos] )
			rson[pos] = ++cnt;
		insert(rson[pos],mid+1,rr,tar,add);
	}
}
inline int countfull(int pos) {
	int ret = 0;
	while( pos )
		ret += siz[bit[pos]],
		pos -= lowbit(pos);
	return ret;
}
inline int countlson(int pos) {
	int ret = 0;
	while( pos )
		ret += siz[lson[bit[pos]]],
		pos -= lowbit(pos);
	return ret;
}
inline void setroot(int pos) {
	while( pos )
		bit[pos] = root[pos],
		pos -= lowbit(pos);
}
inline void setlson(int pos) {
	while( pos )
		bit[pos] = lson[bit[pos]],
		pos -= lowbit(pos);
}
inline void setrson(int pos) {
	while( pos )
		bit[pos] = rson[bit[pos]],
		pos -= lowbit(pos);
}
inline int queryless(int ll,int rr,int st,int ed,int tar) {
	if( ll == rr ) {
		if( ll < tar )
			return countfull(ed) - countfull(st);
		return 0;
	}
	const int mid = ( ll + rr ) >> 1;
	if( tar <= mid ) {
		setlson(ed) , setlson(st);
		return queryless(ll,mid,st,ed,tar);
	}
	else {
		int ss = countlson(ed) - countlson(st);
		setrson(ed) , setrson(st);
		return ss + queryless(mid+1,rr,st,ed,tar);
	}
}
inline int queryequ(int ll,int rr,int st,int ed,int tar) {
	if( ll == rr )
		return countfull(ed) - countfull(st);
	const int mid = ( ll + rr ) >> 1;
	if( tar <= mid ) {
		setlson(ed) , setlson(st);
		return queryequ(ll,mid,st,ed,tar);
	}
	else {
		setrson(ed) , setrson(st);
		return queryequ(mid+1,rr,st,ed,tar);
	}
}
inline int kth(int ll,int rr,int st,int ed,int k) {
	if( ll == rr )
		return ll;
	const int mid = ( ll + rr ) >> 1;
	int ss = countlson(ed) - countlson(st);
	if( k <= ss ) {
		setlson(ed) , setlson(st);
		return kth(ll,mid,st,ed,k);
	}
	else {
		setrson(ed) , setrson(st);
		return kth(mid+1,rr,st,ed,k-ss);
	}
}

inline void init() {
	sort(srt+1,srt+1+len);
	len = unique(srt+1,srt+1+len) - srt - 1;
	for(int i=1;i<=n;i++)
		val[i] = lower_bound(srt+1,srt+1+len,val[i]) - srt;
	for(int i=1;i<=m;i++)
		if( ope[i][0] != 2 )
			ope[i][3] = lower_bound(srt+1,srt+1+len,ope[i][3]) - srt;
	for(int i=1;i<=n;i++)
		root[i] = ++cnt;
	for(int i=1;i<=n;i++) {
		for(int j=i;j<=n;j+=lowbit(j))
			insert(root[j],1,len,val[i],1);
	}
}

inline void work() {
	static lli ans;
	for(int i=1;i<=m;i++) {
		if( ope[i][0] != 3 )
			setroot(ope[i][2]) , setroot(ope[i][1]-1);
		if( ope[i][0] == 1 ) {
			ans = queryless(1,len,ope[i][1]-1,ope[i][2],ope[i][3]) + 1;
		}
		else if( ope[i][0] == 2 ) {
			ans = kth(1,len,ope[i][1]-1,ope[i][2],ope[i][3]);
			ans = srt[ans];
		}
		else if( ope[i][0] == 3 ) {
			for(int j=ope[i][1];j<=n;j+=lowbit(j)) {
				insert(root[j],1,len,val[ope[i][1]],-1);
			}
			val[ope[i][1]] = ope[i][3];
			for(int j=ope[i][1];j<=n;j+=lowbit(j))
				insert(root[j],1,len,val[ope[i][1]],1);
		}
		else if( ope[i][0] == 4 ) {
			int less = queryless(1,len,ope[i][1]-1,ope[i][2],ope[i][3]);
			setroot(ope[i][2]) , setroot(ope[i][1]-1);
			ans = kth(1,len,ope[i][1]-1,ope[i][2],less);
			ans = srt[ans];
		}
		else if( ope[i][0] == 5 ) {
			int less = queryless(1,len,ope[i][1]-1,ope[i][2],ope[i][3]);
			setroot(ope[i][2]) , setroot(ope[i][1]-1);
			int equ = queryequ(1,len,ope[i][1]-1,ope[i][2],ope[i][3]);
			setroot(ope[i][2]) , setroot(ope[i][1]-1);
			ans = kth(1,len,ope[i][1]-1,ope[i][2],less+equ+1);
			ans = srt[ans];
		}
		if( ope[i][0] != 3 )
			printf("%lld\n",ans);
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",val+i),
		srt[++len] = val[i];
	for(int i=1;i<=m;i++) {
		scanf("%lld",&ope[i][0]);
		if( ope[i][0] == 3 )
			scanf("%lld%lld",&ope[i][1],&ope[i][3]);
		else
			scanf("%lld%lld%lld",&ope[i][1],&ope[i][2],&ope[i][3]);
		if( ope[i][0] != 2 )
			srt[++len] = ope[i][3];
	}
	
	init();
	work();
	
	return 0;
}
