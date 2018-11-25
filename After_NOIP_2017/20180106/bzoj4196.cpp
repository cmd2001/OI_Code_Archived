#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e6+1e2,lim=1e6;
const int mod = 1000000007;

lli mu[maxn],mem[maxn];
int n;

inline void pre() {
	static int prime[maxn],cnt;
	static char vis[maxn];
	mu[1] = 1;
	for(lli i=2;i<=lim;i++) {
		if( !vis[i] ) {
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
			const int tar = i * prime[j];
			vis[tar] = 1;
			if( ! (  i % prime[j] ) ) {
				mu[tar] = 0;
				break;
			}
			mu[tar] = -mu[i];
		}
	}
	for(int i=1;i<=lim;i++)
		mu[i] += mu[i-1];
}
inline lli getmu(int p) {
	return p<=lim ? mu[p] : mem[n/p];
}
inline void sieve() {
	int t = ( n + lim - 1 ) / lim;
	while( t ) {
		const int m = n / t;
		mem[t] = 1;
		for(lli i=2,j;i<=m;i=j+1) {
			j = m / ( m / i );
			mem[t] -= ( j - i + 1 ) * ( getmu(m/j) ) % mod;
		}
		mem[t] %= mod;
		t--;
	}
}
inline lli sum(lli n) {
	lli ret = 0;
	for(lli i=1,j;i<=n;i=j+1) {
		j = n / ( n / i );
		ret += ( j - i + 1 ) * ( n / i ) % mod,
		ret %= mod;
	}
	return ret * ret % mod;
}
inline lli f(lli n) {
	lli ret = 0;
	for(lli i=1,j;i<=n;i=j+1) {
		j = n / ( n / i );
		ret += ( getmu(j) - getmu(i-1) ) * sum( n / i ) % mod;
		ret = ( ret % mod + mod ) % mod;
	}
	return ret;
}

int main() {
	scanf("%d",&n);
	pre();
	sieve();
	printf("%lld\n",f(n));
	return 0;
}
