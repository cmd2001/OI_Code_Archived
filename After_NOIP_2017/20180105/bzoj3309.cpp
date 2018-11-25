#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e7+1e2;

lli sum[maxn];

inline void pre() {
	static int prime[maxn],most[maxn],pows[maxn],cnt;
	static char vis[maxn];
	
	for(lli i=2;i<maxn;i++) {
		if( !vis[i] ) {
			sum[i] = -1;
			prime[++cnt] = i;
			most[i] = 1 , pows[i] = i;
		}
		for(int j=1;j<=cnt&&i*prime[j]<maxn;j++) {
			const int tar = i * prime[j];
			vis[tar] = 1;
			most[tar] = 1 , pows[tar] = prime[j];
			sum[tar] = most[i] == 1 ? -sum[i] : 0;
			if( ! ( i % prime[j]) ) {
				most[tar] = most[i] + 1,
				pows[tar] = pows[i] * prime[j];
				sum[tar] = most[tar/pows[tar]] == most[tar] ? -sum[tar/pows[tar]] : 0;
				break;
			}
		}
	}
}

int main() {
	pre();
	for(int i=1;i<=10;i++)
		debug<<sum[i]<<" ";debug<<endl;
}
