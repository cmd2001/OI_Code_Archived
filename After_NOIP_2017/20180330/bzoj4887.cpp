#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=7e1;
const int mod=2017;

int n;
struct Matrix {
    lli dat[maxn][maxn];
    Matrix() {
        memset(dat,0,sizeof(dat));
    }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=1;i<=n<<1;i++)
            for(int j=1;j<=n<<1;j++)
                for(int k=1;k<=n<<1;k++)
                    ( ret.dat[i][j] += a.dat[i][k] * b.dat[k][j] % mod ) %= mod;
        return ret;
    }
}trans,ini,ans;
lli full;

inline Matrix fastpow(Matrix base,int tim) {
    Matrix ret = base; --tim;
    while( tim ) {
        if( tim & 1 ) ret = ret * base;
        if( tim >>= 1 )  base = base * base;
    }
    return ret;
}

int main() {
    static int m,t;
    scanf("%d%d",&n,&m) , ini.dat[1][1] = ini.dat[1][n+1] = 1;
    for(int i=1;i<=n;i++) trans.dat[i][i] = trans.dat[i][i+n] = trans.dat[i+n][i+n] = 1;
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d",&a,&b);
        trans.dat[a][b] = trans.dat[b][a] = trans.dat[a][b+n] = trans.dat[b][a+n] = 1;
    }
    scanf("%d",&t) , ans = ini * fastpow(trans,t);
    for(int i=1;i<=n;i++) full = ( full + ans.dat[1][i+n] ) % mod;
    printf("%lld\n",full);
    return 0;
}