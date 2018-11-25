#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e4+1e2;

double f[maxn],g[maxn];
int n;

inline void dp() {
    for(int i=n-1;~i;i--) {
        f[i] = f[i+1] + 1.0 * n / ( n - i );
        g[i] = ( i * f[i] + n ) / ( n - i ) + g[i+1] + f[i+1];
    }
}

int main() {
    scanf("%d",&n);
    dp();
    printf("%0.2lf\n",g[0]);
    return 0;
}
