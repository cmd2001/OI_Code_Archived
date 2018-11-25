#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=7,lim=2e3;

inline lli gcd(lli x,lli y) {
    if( !x || !y ) return x | y;
    register lli t;
    while( ( t = x % y ) ) x = y , y = t;
    return y;
}

lli in[maxn],way[maxn],ans[maxn][maxn];
lli ope[maxn*maxn*maxn],sou[maxn*maxn*maxn],tar[maxn*maxn*maxn],mul[maxn*maxn*maxn];
int n,fs,cnt,lastnum;

inline bool judge() {
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if( abs(ans[i][j]) > lim ) return 0;
    return 1;
}
inline bool solve_sta(int ss) {
    memset(ans,0,sizeof(ans));
    int pi = 1; ans[1][1] = 1;
    for(int i=2;i<=n;i++) {
        if( ss & ( 1 << ( i - 2 ) ) ) ans[i][i] = -1;
        else ans[i][i] = 1;
        pi *= ans[i][i];
    }
    if( pi != lastnum ) return 0;
    for(int i=cnt;i;i--) {
        if( ope[i] == 1 ) { // swap
            for(int j=1;j<=n;j++) swap(ans[sou[i]][j],ans[tar[i]][j]);
        } else {
            for(int j=1;j<=n;j++) ans[tar[i]][j] += ans[sou[i]][j] * mul[i];
        }
    }
    return judge();
}
inline bool getway() {
    static int lasti=1,lastj=0;
    cnt = 0 , lastnum = 1;
    for(int i=1;i<=n;i++) way[i] = in[i];
    for(;lasti<=n;lasti++,lastj=0) {
        for(lastj++;lastj<=n;lastj++) if( lasti != lastj && gcd(in[lasti],in[lastj]) == 1 ) {
            while( way[lasti] && way[lastj] ) {
                if( way[lasti] > way[lastj] ) ope[++cnt] = 1 , sou[cnt] = lasti , tar[cnt] = lastj , lastnum *= -1 , swap(way[lasti],way[lastj]);
                int t = way[lastj] / way[lasti];
                ope[++cnt] = 0 , sou[cnt] = lasti , tar[cnt] = lastj , mul[cnt] = t , way[lastj] %= way[lasti];
            }
            if( !way[lasti] ) ope[++cnt] = 1 , sou[cnt] = lasti , tar[cnt] = lastj , lastnum *= -1 , swap(way[lasti],way[lastj]);
            if( lasti != 1 ) ope[++cnt] = 1 , sou[cnt] = lasti , tar[cnt] = 1 , lastnum *= 1;
            for(int j=2;j<=n;j++) if( way[j] ) ope[++cnt] = 0 , sou[cnt] = 1 , tar[cnt] = j , mul[cnt] = way[j] , way[j] = 0;
            return 1;
        }
    }
    return 0;
}

int main() {
    freopen("final.in","r",stdin);
    freopen("final.out","w",stdout);
    scanf("%d",&n) , fs = 1 << ( n - 1 );
    for(int i=1;i<=n;i++) scanf("%lld",in+i);
    while(getway()) for(int ss=0;ss<fs;ss++) if( solve_sta(ss) ) {
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) printf("%lld%c",ans[j][i],j!=n?' ':'\n');
        return 0;
    }
    puts("no solution");
    return 0;
}

