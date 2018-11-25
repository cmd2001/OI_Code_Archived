#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;

inline lli sum(lli x) {
	return x * ( x + 1 ) >> 1;
}
inline lli calc(lli a,lli b,lli c,lli n) {
	//debug<<"a = "<<a<<"b = "<<b<<"c = "<<c<<"n = "<<n<<endl;
	if( !a )
		return c / b * n;
	if( c < 0 ) {
		lli t = ( - c + b - 1 ) / b;
		return calc( a , b , t * b + c , n ) - t * n;
	}
	if( c >= b ) {
		return c / b * n + calc( a , b , c % b , n );
	}
	if( a >= b )
		return a / b * sum(n) + calc( a % b , b , c , n );
	lli mx = ( c + a * n ) / b;
	return mx * ( n + 1 ) - calc( b , a , -c + a - 1 , mx);
}

int main() {
	static lli a,b,c,ans;
	scanf("%lld%lld%lld",&a,&b,&c);
	ans = ( c / a + 1 ) + ( c / b + 1 ) - 1 + calc( a , b , c % a - a , c / a );
	printf("%lld\n",ans);
	return 0;
}
