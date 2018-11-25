#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=5e5+1e2;

int in[maxn],f[maxn],g[maxn];

inline void solve1(int pl,int pr,int ql,int qr) {
	if( pl > pr || ql > qr ) return;
	if( pl == pr ) {
		for(int i=ql;i<=qr&&i<=pr;i++)
			f[pl] = max( (double)f[pl] , in[i] + ceil( sqrt( pl - i ) ) );
		return;
	}
	const int pmid = ( pl + pr ) >> 1 ;
	int qmid;
	double m = 0;
	for(int j=ql;j<=qr&&j<=pmid;j++)
		if( in[j] + sqrt( pmid - j ) > m ) {
			m = in[j] + sqrt( pmid - j );
			qmid = j;
		}
	f[pmid] = in[qmid] + ceil( sqrt( pmid - qmid ) ) ;
	solve1(pl,pmid-1,ql,qmid);
	solve1(pmid+1,pr,qmid,qr);
}
inline void solve2(int pl,int pr,int ql,int qr) {
	if( pl > pr || ql > qr ) return;
	if( pl == pr ) {
		for(int i=qr;i>=ql&&i>=pl;i--)
			g[pl] = max( (double)g[pl] , in[i] + ceil( sqrt( i - pl) ) );
		return;
	}
	const int pmid = ( pl + pr ) >> 1 ;
	int qmid;
	double m = 0;
	for(int j=qr;j>=ql&&j>=pmid;j--)
		if( in[j] + sqrt( j - pmid ) > m ) {
			m = in[j] + sqrt( j - pmid );
			qmid = j;
		}
	g[pmid] = in[qmid] + ceil( sqrt( qmid - pmid ) );
	solve2(pl,pmid-1,ql,qmid);
	solve2(pmid+1,pr,qmid,qr);
}

int main() {
	static int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",in+i);
	solve1(1,n,1,n);
	solve2(1,n,1,n);
	
	for(int i=1;i<=n;i++)
		printf("%d\n",max( f[i] , g[i] ) - in[i] );
	return 0;
}

