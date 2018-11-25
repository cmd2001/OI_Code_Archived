#include<bits/stdc++.h>
typedef long double ldb;
using namespace std;
const int maxn=1e2+1e1;

inline ldb sq(const ldb &x) {
    return x * x;
}

ldb x[maxn],y[maxn];

inline ldb _() {
    return (ldb) ( rand() % (int)1e7 ) / ( rand() % (int)1e7 + 1 );
}
inline ldb dis(int i,int j) {
    return sqrt( sq(x[i]-x[j]) + sq(y[i]-y[j]) );
}

int main() {
    static int n = 100;
    srand((unsigned long long)new char);
    printf("%d\n",n);
    for(int i=1;i<=n;i++) {
        x[i] = _() , y[i] = _();
        if( ! ( i & 1 ) ) x[i] = x[i>>1] , y[i] = y[i>>1];
    }
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) printf("%0.10Lf%c",dis(i,j),j!=n?' ':'\n');
    }
    return 0;
}