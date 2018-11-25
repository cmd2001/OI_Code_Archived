#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e7+1e2,lim=2e7;
const int mod=998244353,rev=166374059;

lli sum[maxn],mem[maxn];
lli n;

inline void pre() {
	static int prime[maxn],cnt;
	
	sum[1] = 1;
	for(lli i=2;i<=lim;i++) {
		if( !sum[i] ) {
			prime[++cnt] = i,
			sum[i] = i - 1;
		}
		for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
			if( ! ( i % prime[j] ) ) {
				sum[i*prime[j]] = sum[i] * prime[j] % mod;
				break;
			}
			sum[i*prime[j]] = sum[i] * ( prime[j] - 1 ) % mod;
		}
	}
	for(int i=1;i<=lim;i++) {
		sum[i] = sum[i] * i % mod * i % mod,
		sum[i] += sum[i-1],
		sum[i] %= mod;
	}
}

inline lli ss(lli x) {
	x %= mod;
	return ( x * ( x + 1 ) >> 1 )% mod;
}
inline lli sumsq(lli x) {
	x %= mod;
	return x * ( x + 1 ) % mod * ( x * 2 % mod + 1 ) % mod * rev % mod;
}
inline lli query(lli p) {
	if( p <= lim )
		return sum[p];
	else
		return mem[n/p];
}
inline void sieve() {
	int t = ( n + lim - 1 ) / lim;
	while( t ) {
		const lli m = n / t;
		mem[t] = ss(m) * ss(m) % mod;
		for(lli i=2,j;i<=m;i=j+1) {
			j = m / ( m / i );
			mem[t] -= ( ( sumsq(j) - sumsq(i-1) ) % mod + mod ) % mod * query(m/i) % mod,
			mem[t] %= mod;
		}
		mem[t] = ( mem[t] % mod + mod ) % mod;
		t--;
	}
}


inline lli getans() {
	lli ret = 0;
	for(lli i=1,j;i<=n;i=j+1) {
		j = n / ( n / i );
		ret += ss(n/i) * ss(n/i) % mod * ( ( ( query(j) - query(i-1) ) % mod + mod ) % mod ) % mod;
		ret = ret % mod;
	}
	return ( ret + mod ) % mod;
}

int main() {
	pre();
	scanf("%lld",&n);
	sieve();
	printf("%lld\n",getans());
	return 0;
}
