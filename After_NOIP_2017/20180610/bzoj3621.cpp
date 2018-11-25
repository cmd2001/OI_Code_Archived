#include<cstdio>
#include<algorithm>
#include<complex>
#include<cstdlib>
using namespace std;
typedef complex<double> Complex;
const double eps = 1e-4;

inline int fcmp(const double &x) {
    return fabs(x) <= eps ? 0 : x < 0 ? -1 : 1;
}

inline Complex getcomp() {
    static double r,i;
    scanf("%lf%lf",&r,&i);
    return Complex(r,i);
}
inline bool jez(const Complex &c) {
    return !fcmp(c.real()) && !fcmp(c.imag());
}
inline bool calc(Complex &a,Complex &b,Complex &c,Complex &aa,Complex &bb,Complex &cc) {
    Complex T = ( aa - bb ) / ( a - b ) , P = ( a * T - aa ) / ( T - Complex(1.0,0.0) );
    if( jez( ( c - P ) * T - ( cc - P ) ) ) return printf("%lf %lf\n",P.real(),P.imag()) , 1;
    return 0;
}

int main() {
    static int T,t[3];
    static Complex in[3],a,b,c;
    scanf("%d",&T);
    while(T--) {
        a = getcomp() , b = getcomp() , c = getcomp();
        for(int i=0;i<3;i++) in[i] = getcomp() , t[i] = i;
        while( !calc(a,b,c,in[t[0]],in[t[1]],in[t[2]]) && next_permutation(t,t+3) );
    }
    return 0;
}

