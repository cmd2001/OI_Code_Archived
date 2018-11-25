#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define lli long long
#define int long long
#define debug cout
using namespace std;
const int maxn=1e6+1e2;
const int mod=1000000007;

int id[maxn],siz[maxn],sum[maxn];
vector<int> lim[maxn];
lli facs[maxn<<1],revs[maxn<<1];
lli ans = 1;
int n,m,t;

inline lli fastpow(lli base,int tme) {
    lli ret = 1;
    while( tme ) {
        if( tme & 1 )
            ret = ret * base % mod;
        base = base * base % mod;
        tme >>= 1;
    }
    return ret;
}
inline void gen() {
    *revs = *facs = 1;
    for(int i=1;i<=n<<1;i++) {
        facs[i] = facs[i-1] * i % mod ,
        revs[i] = revs[i-1] * fastpow(i,mod-2) % mod;
    }
}

inline lli c(int n,int m) {
    if( n < 0 || m < 0 || n - m < 0 )
        return 0;
    return facs[n] * revs[m] % mod * revs[n-m] % mod;
}

inline int count(int ss) {
    int ret = 0;
    while( ss )
        ret++ ,
        ss -= ( ss & -ss );
    return ret;
}
inline int calcsum(int ss,vector<int> lims) {
    int ret = 0;
    for(unsigned i=0;i<lims.size();i++)
        if( ss & ( 1 << i ) )
            ret += lims[i];
    return ret;
}
inline lli calcextra(int siz,int full) {
    return c(full+siz-1,siz-1);
}
inline lli calc(int siz,int full,vector<int> lims) {
    lli ret = calcextra(siz,full);
    int fs = ( 1 << lims.size() ) - 1;
    for(int ss=1;ss<=fs;ss++) {
        const int sum = calcsum(ss,lims);
        if( full - sum >= 0 ) {
            ret += ( ( count(ss) & 1 ) ? -1 : 1 ) * calcextra(siz,full-sum);
            ret = ( ret % mod + mod ) % mod;
        }
    }
    return ret;
}

signed main() {
    scanf("%lld%lld",&n,&m);
    for(int i=1,k,p;i<=m;i++) {
        scanf("%lld",&k);
        siz[i] = k;
        while( k-- ) {
            scanf("%lld",&p);
            id[p] = i;
        }
        scanf("%lld",sum+i);
    }
    scanf("%lld",&t);
    for(int i=1,r,L;i<=t;i++) {
        scanf("%lld%lld",&r,&L);
        lim[id[r]].push_back(L+1);
    }
    gen();
    
    for(int i=1;i<=m;i++)
        ans = ans * calc(siz[i],sum[i],lim[i]) % mod;
    
    printf("%lld\n",ans);
    
    return 0;
}