#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e3+1e2;
const int mod=1e9+7;

lli facs[maxn],invs[maxn];
lli f[maxn];
int n,m;

inline lli fastpow(lli base,int tme) {
	lli ret =  1 , now = base;
	while( tme ) {
		if( tme & 1 )
			ret = ret * now % mod;
		now = now * now % mod;
		tme >>= 1;
	}
	return ret;
}

inline lli c(int n,int m) {
	return facs[n] * invs[m] % mod * invs[n-m] % mod;
}
inline int delk(int x) {
	return x&1 ? -1 : 1;
}

inline void pre() {
	invs[0] = facs[0] = 1;
	for(int i=1;i<=m;i++)
		facs[i] = facs[i-1] * i % mod;
	invs[m] = fastpow(facs[m],mod-2);
	for(int i=m-1;~i;i--)
		invs[i] = invs[i+1] * ( i + 1 ) % mod;
}

inline void calc() {
	f[0] = ( fastpow(m,n+1) - m  + mod ) % mod * fastpow(m-1,mod-2) % mod; 
	for(int i=1;i<=m;i++) {
		f[i] = fastpow(n,i) * fastpow(m,n+1) % mod;
		for(int j=0;j<i;j++)
			f[i] += c(i,j) * delk(i-j) * f[j] % mod,
			f[i] = ( f[i] % mod + mod ) % mod;
		f[i] = f[i] * fastpow(m-1,mod-2) % mod;
	}
}

int main() {
	scanf("%d%d",&n,&m);
	if( m == 1 ) {
		printf("%lld\n", (  ( (lli) n ) * ( n + 1 ) >> 1 ) % mod );
		return 0;
	}
	pre();
	calc();
	printf("%lld\n",f[m]);
	return 0;
}
