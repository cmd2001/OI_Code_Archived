#include<iostream>
#include<cstdio>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e6+1e2;
const int mod=1e9+7;

lli sum[maxn];
int k;

inline lli fastpow(lli base) {
	int tme = k;
	lli ret = 1;
	while( tme ) {
		if( tme & 1 )
			ret = ret * base % mod;
		base = base * base % mod;
		tme >>= 1;
	}
	return ret;
}
inline void init() {
	static int pows[maxn],prime[maxn],cnt;
	static char vis[maxn];
	pows[1] = sum[1] = 1;
	for(lli i=2;i<maxn;i++) {
		if( !vis[i] ) {
			prime[++cnt] = i;
			pows[i] = fastpow(i);
			sum[i] = pows[i] - 1;
		}
		for(int j=1;j<=maxn&&i*prime[j]<maxn;j++) {
			const int tar = i * prime[j];
			vis[tar] = 1 ;
			if( ! ( i % prime[j] ) ) {
				sum[tar] = sum[i] * pows[prime[j]] % mod;
				break;
			}
			sum[tar] = sum[i] * sum[prime[j]] % mod;
		}
	}
	for(int i=1;i<maxn;i++)
		sum[i] += sum[i-1];
}

inline lli calc(lli n,lli m) {
	lli ret = 0 , lim = min(n,m);
	for(lli i=1,j;i<=lim;i=j+1) {
		j = min( n / ( n / i ) , m / ( m / i ) );
		ret += ( ( sum[j] - sum[i-1] ) % mod + mod ) % mod * ( n / i ) % mod * ( m / i ) % mod;
		ret = ( ret % mod + mod ) % mod;
	}
	return ret;
}

int main() {
	static int T,n,m;
	scanf("%d%d",&T,&k);
	init();
	while( T-- ) {
		scanf("%d%d",&n,&m);
		printf("%lld\n",calc(n,m));
	}
	return 0;
}

