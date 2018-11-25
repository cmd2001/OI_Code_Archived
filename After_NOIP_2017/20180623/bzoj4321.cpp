#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=1e3+1e2;
const int mod=7777777;

inline int add(const int &x,const int &y) {
    const int ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}

int f[maxn][maxn][2],n;

int main() {
    scanf("%d",&n) , f[1][0][0] = 1;
    for(int i=2;i<=n;i++) {
        for(int j=0;j<=n;j++) {
            f[i][j][0] = add(add(mul(f[i-1][j][0],i-j-2),mul(f[i-1][j][1],i-j-1)),add(mul(f[i-1][j+1][0],j+1),mul(f[i-1][j+1][1],j)));
            f[i][j][1] = f[i-1][j][1];
            if( j ) adde(f[i][j][1],add(mul(f[i-1][j-1][0],2),f[i-1][j-1][1]));
        }
    }
    printf("%d\n",f[n][0][0]);
    return 0;
}

