#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=100;
const int mod=1e9+7;

lli f[maxn][maxn];
int k;

inline lli rev(int base) {
    lli now = base , ret = 1 , tme = mod - 2;
    while(tme) {
        if( tme & 1 )
            ret = ret * now % mod;
        now = now * now % mod;
        tme >>= 1;
    }
    debug<<"base = "<<base<<"ret = "<<ret<<endl;
    return ret;
}

inline lli slowpow(lli base,int tme) {
    lli ret = 1;
    for(int t=tme;t;t--)
        ret = ret * base % mod;
    return ret;
}
inline lli g(lli x) {
    lli ret = 0;
    for(int i=1;i<=x;i++)
        ret =  ( ret + slowpow(i,k-1) ) % mod;
    //debug<<"x = "<<x<<"ret = "<<ret<<endl;
    return ret;
}

inline void gen() {
    for(int i=1;i<=k+1;i++) {
        for(int j=0;j<=k;j++)
            f[i][j] = slowpow(i,j);
        f[i][k+1] = g(i);
    }
    for(int i=0;i<=k;i++)
        for(int j=0;j<=k+1;j++)
            f[i][j] = f[i+1][j];
}

inline void gauss() {
    for(int i=0;i<=k;i++) {
        int e = -1;
        for(int j=i;j<=k;j++)
            if( f[j][i] ) {
                e = j;
                break;
            }
        if( !~e ) {
            puts("Unable to find a solution;");
            exit(0);
        }
        debug<<"i = "<<i<<"e = "<<e<<endl;
        if( e != i ) {
            for(int j=0;j<=k+1;j++)
                swap(f[i][j],f[e][j]);
            e = i;
        }
        lli r = rev(f[i][i]);
        debug<<"fii = "<<f[i][i]<<"rev = "<<r<<endl;
        for(int j=0;j<=k+1;j++)
            f[i][j] = f[i][j] * r % mod;
        for(int j=0;j<=k+1;j++)
            debug<<f[i][j]<<" ";debug<<endl;
        for(int j=0;j<=k;j++)
            if( j != i && f[j][i] ) {
                const lli del = f[j][i];
                for(int t=0;t<=k+1;t++)
                    f[j][t] = ( ( f[j][t] - f[i][t] * del % mod ) % mod + mod ) % mod;
            }
    }
}

inline void print() {
    for(int i=0;i<=k;i++) {
        for(int j=0;j<=k+1;j++) debug<<f[i][j]<<" ";debug<<endl;
    }
}
int main() {
    char com[100];
    scanf("%d",&k);
    sprintf(com,"dat%d.txt",k);
    ++k;
    gen();
    print();
    gauss();
    debug<<"Ans = "<<endl;
    print();
    freopen(com,"w",stdout);
    printf("{");
    for(int i=0;i<=k;i++)
        printf("%lld%c",f[i][k+1],i!=k?',':'}');
}