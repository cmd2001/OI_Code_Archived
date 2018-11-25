#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=71,maxk=102;
const int mod=1e9+7;

int f[maxn][2][2][2][2],fac[maxk],inv[maxk]; // f[considered_bit][rem][==n][==m][same]
int bn[maxn],bm[maxn],k;
lli n,m;

inline int getinv(int base) {
    int ret = 1 , tim = k - 2;
    while(tim) {
        if( tim & 1 ) ret = ret * base % k;
        if( tim >>= 1 ) base = base * base % k;
    }
    return ret;
}
inline bool c(int n,int m) {
    if( n < m ) return 0;
    return fac[n] * inv[m] * inv[n-m] % k;
}

inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}

inline int cutbit(int* dst,lli x) {
    int len = 0; memset(dst,0,maxn<<2);
    while(x) dst[++len] = x % k , x /= k;
    return len;
}

int main() {
    static int T,len,ans;
    scanf("%d%d",&T,&k);
    *fac = 1; for(int i=1;i<k;i++) fac[i] = fac[i-1] * i % k;
    inv[k-1] = getinv(fac[k-1]); for(int i=k-1;i;i--) inv[i-1] = inv[i] * i % k;
    while(T--) {
        scanf("%lld%lld",&n,&m) , len = max( cutbit(bn,n) , cutbit(bm,m) ) , memset(f,0,sizeof(f)) , ans = 0;
        for(int i=0;i<=bn[len];i++) for(int j=0;j<=bm[len]&&j<=i;j++) adde(f[len][c(i,j)][i==bn[len]][j==bm[len]][j==i],1);
        for(int i=len,lin,lim;i>1;i--) for(int rem=0;rem<2;rem++) for(int sn=0;sn<2;sn++) for(int sm=0;sm<2;sm++) for(int al=0;al<2;al++) if( f[i][rem][sn][sm][al] ) {
            lin = sn ? bn[i-1] : k - 1 , lim = sm ? bm[i-1] : k - 1;
            for(int cn=0;cn<=lin;cn++) for(int cm=0,cc=al?min(cn,lim):lim;cm<=cc;cm++) adde(f[i-1][rem*c(cn,cm)][sn&&cn==bn[i-1]][sm&&cm==bm[i-1]][al&&cn==cm],f[i][rem][sn][sm][al]);
        }
        for(int sn=0;sn<2;sn++) for(int sm=0;sm<2;sm++) for(int al=0;al<2;al++) adde(ans,f[1][0][sn][sm][al]);
        printf("%d\n",ans);
    }
    return 0;
}
