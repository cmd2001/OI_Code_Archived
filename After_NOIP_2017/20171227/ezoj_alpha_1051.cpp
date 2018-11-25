#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

double a,b,c,d;
double delta,z1,z2;
double fl,fz1,fz2,fr;
double ans1,ans2,ans3;

inline double f(const double &x) {
	return x * x * x * a + x * x * b + x * c + d;
}
inline void getz() {
	const double aa = 3.0 * a , bb = 2.0 * b , cc = c;
	double delta = bb * bb - 4 * aa * cc;
	delta = sqrt(delta);
	z1 = ( - bb - delta ) / ( 2 * aa ),
	z2 = ( - bb + delta ) / ( 2 * aa );
}
inline double binary_up(double ll,double rr) {
	double mid;
	for(int i=1;i<=1000;i++) {
		mid = ( ll + rr ) / 2.0;
		if( f(mid) < 0 )
			ll = mid;
		else
			rr = mid;
	}
	return ll;
}
inline double binary_down(double ll,double rr) {
	double mid;
	for(int i=1;i<=1000;i++) {
		mid = ( ll + rr ) / 2.0;
		if( f(mid) < 0 )
			rr = mid;
		else ll = mid;
	}
	return rr;
}

int main() {
	scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
	getz();
	fl = f(-100.0) , fz1 = f(z1) , fz2 = f(z2) , fr = f(100);
	if( fl > fz1 )
		ans1 = binary_down(-100.0,z1);
	else
		ans1 = binary_up(-100.0,z1);
	if( fz1 > fz2 )
		ans2 = binary_down(z1,z2);
	else
		ans2 = binary_up(z1,z2);
	if( fz2 > fr )
		ans3 = binary_down(z2,100.0);
	else
		ans3 = binary_up(z2,100.0);
	
	printf("%0.2lf %0.2lf %0.2lf\n",ans1,ans2,ans3);
	
	return 0;
}
