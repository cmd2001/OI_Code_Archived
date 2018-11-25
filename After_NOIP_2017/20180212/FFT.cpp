#include<bits/stdc++.h>
using namespace std;
const int maxn=262145;
const double pi = acos(-1.0);

typedef complex<double> Comp;
Comp x[maxn],y[maxn];

inline void FFT(Comp* dst,int n,int ope) {
	for(int i=0,j=0;i<n;i++) {
		if( i < j ) swap( dst[i] , dst[j] );
		for(int t=n>>1;(j^=t)<t;t>>=1) ;
	}
	for(int len=2;len<=n;len<<=1) {
		const int h = len >> 1;
		const Comp per = Comp( cos( pi * ope / h ) , sin( pi * ope / h ) );
		for(int st=0;st<n;st+=len) {
			Comp w = 1;
			for(int pos=0;pos<h;pos++) {
				const Comp u = dst[st+pos] , v = dst[st+pos+h] * w;
				dst[st+pos] = u + v;
				dst[st+pos+h] = u - v;
				w *= per;
			}
		}
	}
}

int main() {
	static int n,m,len=1;
	scanf("%d%d",&n,&m) , ++n , ++m;
	for(int i=0,p;i<n;i++) {
		scanf("%d",&p) , x[i] = Comp(p,0);
	}
	for(int i=0,p;i<m;i++) {
		scanf("%d",&p) , y[i] = Comp(p,0);
	}
	while( len <= n + m ) len <<= 1;
	FFT(x,len,1) , FFT(y,len,1);
	for(int i=0;i<len;i++) x[i] *= y[i];
	FFT(x,len,-1);
	int l = n + m - 1;
	for(int i=0;i<l;i++) {
		long long p = x[i].real()/len + 0.2;
		printf("%lld%c",p,"\n "[i!=l-1]);
	}
	return 0;
}
