#include<cstdio>
typedef long long int lli;
const int maxn=2e3+1e2;
const int mod=1e9+7;

int f[maxn<<1][maxn<<1];
int n,m,k,t,ans;

inline int sub(const int &a,const int &b) {
    register int ret = a - b;
    return ret < 0 ? ret + mod : ret;
}
inline void adde(int &a,const int &b) {
    if( ( a += b ) >= mod ) a -= mod;
}

inline void getf() {
    f[0][0] = 1;
    for(int i=1;i<=t;i++) // t * k = n + m so these fors are O(n^2)
        for(int su=0;su<=n;su++)
            for(int ths=0;ths<k&&ths<=su;ths++)
                adde(f[i][su],f[i-1][su-ths]);
}
inline void calc() {
    for(int len=1;len<=t;len++)
        for(int su=0;su<=n;su++) {
            const int rel = sub(f[len][su],f[len-1][su]); // cut trailing zeros .
            const int wite = len * ( k - 1) + 1 - su; // calc white points .
            if( wite <= 0 || wite > m || ( n - su ) % ( k - 1 ) || ( m - wite ) % ( k - 1 ) ) continue; // illegal .
            adde(ans,rel);
        }
}

int main() {
    scanf("%d%d%d",&n,&m,&k) , t = ( n + m - 1 ) / ( k - 1 );
    if( !n || !m ) return puts("1"),0;
    getf() , calc() , printf("%d\n",ans);
    return 0;
}

