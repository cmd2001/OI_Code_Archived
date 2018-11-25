#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=1e5+1e2;
const double eps=1e-12;

inline int dcmp(const double &x) {
	if( fabs(x) <= eps )
		return 0;
	return x > 0 ? 1 : -1;
}

struct Point {
	double x,y;
}pts[maxn],cir;
double r;
int n;

inline double sq(const double &x) {
	return x * x;
}
inline double dis(const Point &a,const Point &b) {
	const double dx = a.x - b.x , dy = a.y - b.y;
	return sqrt(sq(dx) + sq(dy) );
}
inline Point circlecenter(const Point &a,const Point &b,const Point &c) {
	const double a1 = a.x - b.x , b1 = a.y - b.y , c1 = ( sq(a.x) + sq(a.y) - sq(b.x) - sq(b.y) ) / 2.0;
	const double a2 = a.x - c.x , b2 = a.y - c.y , c2 = ( sq(a.x) + sq(a.y) - sq(c.x) - sq(c.y) ) / 2.0;
	const double ty = ( c1 * a2 - c2 * a1 ) / ( b1 * a2 - b2 * a1 );
	const double tx = ( c1 * b2 - c2 * b1 ) / ( a1 * b2 - a2 * b1 );
	return (Point){tx,ty};
}
inline Point midpoint(const Point &a,const Point &b) {
	const double tx = ( a.x + b.x ) / 2.0;
	const double ty = ( a.y + b.y ) / 2.0;
	return (Point){tx,ty};
}

inline void getans() {
	cir = pts[1] , r = 0;
	for(int i=2;i<=n;i++)
		if( dis( pts[i] , cir ) > r + eps ) {
			cir = pts[i] , r = 0;
			for(int j=1;j<i;j++)
				if( dis( pts[j] , cir ) > r + eps ) {
					cir = midpoint( pts[i] , pts[j] ),
					r = dis( pts[i] , cir );
					for(int k=1;k<j;k++)
						if( dis( pts[k] , cir ) > r + eps ) {
							cir = circlecenter( pts[i] , pts[j] , pts[k] ),
							r = dis( pts[i] , cir );
						}
				}
		}
}

int main() {
	//freopen("dat.txt","r",stdin);
	while( scanf("%d",&n) == 1 && n ) {
		for(int i=1;i<=n;i++)
			scanf("%lf%lf",&pts[i].x,&pts[i].y);
		
    	random_shuffle(pts+1,pts+1+n);  
		getans();
		
		printf("%0.10lf\n%0.10lf %0.10lf\n",r,cir.x,cir.y);
	}
	
	return 0;
}
