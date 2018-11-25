#include<iostream>
#include<cstdio>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=1.2e5+1e2;
const double eps = 1e-8;

double a2,b2,c2,ab,bc,ca;
double ina[maxn],inb[maxn],inc[maxn];

inline int dcmp(const double &x) {
    if( fabs(x) <= eps ) return 0;
    return x < 0 ? -1 : 1;
}

inline void insert(const double &a,const double &b,const double &c) {
    const double d = a * a + b * b;
    a2 += a * a / d , b2 += b * b / d , c2 += c * c / d ,
    ab += a * b / d , bc += b * c / d , ca += c * a / d ;
}
inline void remove(const double &a,const double &b,const double &c) {
    const double d = a * a + b * b;
    a2 -= a * a / d , b2 -= b * b / d , c2 -= c * c / d ,
    ab -= a * b / d , bc -= b * c / d , ca -= c * a / d;
}
inline void calcline(const double &x,const double &xx,const double &y,const double &yy,double &a,double &b,double &c) {
    if( ! dcmp( x - xx ) ) {
        a = 1 , b = 0 , c = -x;
    } else {
        const double dx = x - xx , dy = y - yy;
        const double kk = dy / dx , bb = y - x * kk;
        a = kk , b = -1 , c = bb;
    }
}
inline double query() {
    const double A = dcmp(b2) ? - ab / b2 : 0 , B = dcmp(b2) ? - bc / b2 : 0;
    const double U = a2 + 2 * A * ab + A * A * b2 ;
    const double V = 2 * ( A * B * b2 + A * bc + B * ab + ca );
    const double W = B * B * b2 + 2 * B * bc + c2 ;
    if( !dcmp(U) ) return W;
    const double x = - V /  ( 2 * U );
    return U * x * x + V * x + W;
}

int main() {
    static int n,siz,cnt;
    static double x , xx , y , yy , a , b , c , ans;
    scanf("%d",&n);
    for(int i=1,o,id;i<=n;i++) {
        scanf("%d",&o);
        if( !o ) {
            scanf("%lf%lf%lf%lf",&x,&y,&xx,&yy);
            calcline(x,xx,y,yy,a,b,c);
            ina[++cnt] = a , inb[cnt] = b , inc[cnt] = c;
            insert(a,b,c) , ++siz;
        } else if( o == 1 ) {
            scanf("%d",&id);
            remove(ina[id],inb[id],inc[id]) , --siz;
        } else if( o == 2 ) {
            if( !siz ) puts("0.00");
            else {
                ans = query();
                if( !dcmp(ans) ) puts("0.00");
                else printf("%0.2lf\n",ans);
            }
        }
    }
    return 0;
}
/*
120000
0 4.349444 -3.630058 4.349444 -2.082381
2
*/
