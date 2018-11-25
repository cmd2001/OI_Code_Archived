#include<cstdio>
#include<algorithm>
#include<functional>
const int maxn=1e5+1e2,maxl=35,mod=10086;

int dat[maxl],pows[maxn],z,len;

inline bool insert(int x) {
    for(int i=31;~i;i--)
        if( x & ( 1ll << i ) ) {
            if( !dat[i] ) {
                dat[i] = x;
                return 1;
            }
            x ^= dat[i];
        }
    return 0;
}
inline void gauss() {
    for(int i=0;i<=31;i++)
        if( dat[i] ) {
            for(int j=0;j<=31;j++)
                if( i != j && dat[j] & ( 1ll << i ) )
                    dat[j] ^= dat[i];
        }
}

int main() {
    static int n,p,ans = 1,now = 0;
    scanf("%d",&n) , *pows = 1;
    for(int i=1;i<=n;i++) {
        scanf("%d",&p) , pows[i] = pows[i-1] * 2 % mod;
        if( !insert(p) ) ++z;
    }
    scanf("%d",&p);
    if( !p ) return puts("1"),0;
    gauss();
    std::sort(dat,dat+(len=31),std::greater<int>());
    while( !dat[len] ) --len;
    for(int i=0;i<=len;i++)
        if( ( now ^ dat[i] ) < p ) {
            now ^= dat[i] , ans += pows[len-i] , ans %= mod;
        }
    ans = ( (long long)ans * pows[z] % mod + 1 ) % mod;
    printf("%d\n",ans);
    return 0;
}

