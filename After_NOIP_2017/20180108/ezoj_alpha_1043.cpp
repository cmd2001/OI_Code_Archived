#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e7+1e2,lim=1e7;
const int mod=998244353;

lli sum[maxn],mem[maxn];
unsigned char vis[maxn];
lli n;

inline void pre() {
	static int prime[maxn],cnt;
	static unsigned char vis[maxn];
	
	sum[1] = 1;
	for(lli i=2;i<=lim;i++) {
		if( !vis[i] ) {
			prime[++cnt] = i ,
			sum[i] = -1;
		}
		//debug<<"i = "<<i<<endl;
		for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
			vis[i*prime[j]] = 1;
			if( ! ( i % prime[j] ) ) {
				sum[i*prime[j]] = 0;
				break;
			}
			sum[i*prime[j]] = -sum[i];
		}
	}
	for(int i=1;i<=lim;i++)
		sum[i] += sum[i-1];
}
inline lli query(lli p) {
	if( p <= lim )
		return sum[p];
	int tar = n / p;
	if( vis[tar] )
		return mem[tar];
	mem[tar] = 1;
	for(lli i=2,j;i<=p;i=j+1) {
		j = p / ( p / i );
		mem[tar] -= ( j - i + 1 ) % mod * ( ( query(j) - query(i-1) ) % mod ) % mod;
		mem[tar] %= mod;
	}
	vis[tar] = 1;
	return mem[tar];
}
inline lli trisum(lli x) {
	x %= mod;
	return ( ( x * ( x + 1 ) >> 1 ) % mod ) * ( ( x * ( x + 1 ) >> 1 ) % mod ) % mod;
}
inline lli linsum(lli x) {
	x %= mod;
	return ( x * ( x + 1 ) >> 1 ) % mod;
}
inline lli sumr(lli x) { // should we reset vis ?
	lli ret = 0;
	for(lli i=1,j;i<=x;i=j+1) {
		j = n / ( n / i );
		ret += ( ( trisum(j) - trisum(i-1) ) % mod + mod ) % mod * query( x / i ) % mod;
		ret %= mod;
	}
	return ( ret + mod ) % mod;
}
inline lli getans() {
	lli ret = 0;
	for(lli i=1,j;i<=n;i=j+1) {
		j = n / ( n / i );
		ret += linsum(n/i) * linsum(n/i) % mod * ( ( sumr(j) - sumr(i-1) ) % mod ) % mod;
		debug<<"i = "<<i<<"j = "<<j<<"delta sum = "<<sumr(j)-sumr(i-1)<<endl;
		debug<<"sq linsum = "<<linsum(n/i) * linsum(n/i)<<endl;
		ret %= mod;
	}
	return ( ret + mod ) % mod;
}

int main() {
	pre();
	scanf("%lld",&n);
	printf("%lld\n",getans());
	return 0;
}


