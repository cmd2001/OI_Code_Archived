#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e6+1e1;

int sum[maxn],len[maxn];
int lim[maxn];

int n,m,t;

namespace PartOne {
    const int maxo=1e1+1e1;
    int eles[maxo][maxo],num[maxo];
    int t,ans;

    inline bool judge() {
        for(int i=1;i<=m;i++) {
            int ss = 0;
            for(int j=1;j<=len[i];j++)
                ss += num[eles[i][j]];
            if( ss != sum[i] )
                return 0;
        }
        return 1;
    }

    inline void dfs(int pos) {
        if( pos > n ) {
            ans += judge();
            return;
        }
        for(int i=0;i<=lim[pos];i++) {
            num[pos] = i;
            dfs(pos+1);
        }
    }

    void main() {
        dfs(1);
        printf("%d\n",ans);
    }
}

namespace PartTwo {
    #define lli long long int
    const int mod = 1000000007;
    
    lli facs[maxn<<1],revs[maxn<<1];
    
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
        return facs[n] * revs[m] % mod * revs[n-m] % mod;
    }
    
    void main() {
        gen();
        lli ans = 1;
        for(int i=1;i<=m;i++) {
            ans = ans * c(sum[i]+len[i]-1,len[i]-1) % mod;
        }
        printf("%lld\n",ans);
    }
    
}

inline void ncan() {
    using PartOne::eles;
    for(int i=1;i<=m;i++) {
        scanf("%d",len+i);
        for(int j=1;j<=len[i];j++)
            scanf("%d",eles[i]+j);
        scanf("%d",sum+i);
        for(int j=1;j<=len[i];j++)
            lim[eles[i][j]] = sum[i];
    }
    scanf("%d",&t);
    for(int i=1,r,L;i<=t;i++) {
        scanf("%d%d",&r,&L);
        lim[r] = min( L , lim[r] );
    }
    for(int i=1;i<=n;i++)
        if( lim[i] > 8 ) {
            PartTwo::main();
            return;
        }
    PartOne::main();
}

int main() {
    scanf("%d%d",&n,&m);
    if( n <= 8 ) {
        ncan();
    }
    
    else {
        for(int i=1;i<=m;i++) {
            scanf("%d",len+i);
            for(int j=1;j<=len[i];j++)
                scanf("%*d");
            scanf("%d",sum+i);
        }
        scanf("%d",&t);
        while( t-- )
            scanf("%*d%*d");
        PartTwo::main();
    }
    
    return 0;
}
