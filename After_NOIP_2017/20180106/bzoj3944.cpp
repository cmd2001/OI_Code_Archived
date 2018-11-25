#pragma GCC optimize(2)
#include<cstdio>
#define lli long long int
#define uint unsigned int
using namespace std;
const uint maxn=1677025,maxm=1295;

lli phi[maxn],mu[maxn];
lli memphi[maxm],memmu[maxm];
unsigned char visphi[maxn],vismu[maxm];
uint t,n;

inline void reset(unsigned char* dst,uint len) {
	uint ite = ( len + 7 ) >> 3;
	switch( len & 7u ) {
		case 0 : do{ *dst++ = 0;
		case 7 : *dst++ = 0;
		case 6 : *dst++ = 0;
		case 5 : *dst++ = 0;
		case 4 : *dst++ = 0;
		case 3 : *dst++ = 0;
		case 2 : *dst++ = 0;
		case 1 : *dst++ = 0; }while(--ite);
	}
}

inline void gen() {
	static uint prime[maxn/2],cnt;
	static unsigned char vis[maxn];
	
	phi[1] = mu[1] = 1;
	for(uint i=2;i<maxn;i++) {
		if( !vis[i] ) {
			prime[++cnt] = i,
			phi[i] = i - 1 , mu[i] = -1;
		}
		for(uint j=1;j<=cnt&&((unsigned lli)i)*prime[j]<maxn;j++) {
			const uint tar = i*prime[j];
			vis[tar] = 1;
			if( ! ( i % prime[j] ) ) {
				phi[tar] = phi[i] * prime[j] , mu[tar] = 0;
				break;
			}
			phi[tar] = phi[i] * ( prime[j] - 1 ) , mu[tar] = -mu[i];
		}
	}
	for(uint i=1;i<maxn;i++)
		phi[i] += phi[i-1] , mu[i] += mu[i-1];
}

inline lli sumphi(uint x) {
	if( x < maxn )
		return phi[x];
	uint mp = n / x;
	if( visphi[mp] )
		return memphi[mp];
	lli ret = ( (lli) x ) * ( x + 1 ) >> 1;
	for(uint i=2,j;i<=x;i=j+1) {
		j = x / ( x / i );
		ret -= ( (lli) ( j - i + 1 ) ) * sumphi( x / i );
	}
	visphi[mp] = 1;
	return memphi[mp] = ret;
}
inline lli summu(uint x) {
	if( x < maxn )
		return mu[x];
	uint mp = n / x;
	if( vismu[mp] )
		return memmu[mp];
	lli ret = 1;
	for(uint i=2,j;i<=x;i=j+1) {
		j = x / ( x / i );
		ret -= ( (lli) ( j - i + 1 ) ) * summu( x / i );
	}
	vismu[mp] = 1;
	return memmu[mp] = ret;
}

inline uint getint() {
	uint ret = 0 , ch = getchar();
	while( ch < '0' || ch > '9' )
		ch = getchar();
	while( '0' <= ch && ch <= '9' )
		ret = ret * 10 + ( ch - '0' ),
		ch = getchar();
	return ret;
}

int main() {
	gen();
	t = getint();
	while( t-- ) {
		reset(visphi,maxm);
		reset(vismu,maxm);
		n = getint();
		printf("%lld %lld\n",sumphi(n),summu(n));
	}
	return 0;
}
