#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=1e5+1e2;

int o[maxn],bit[32];
lli t[maxn],ans;
int n,m,len,lim=1;

inline lli f(int mask,lli x) {
    for(int i=1;i<=n;i++) {
        if( o[i] == 1 ) x &= ( t[i] & mask );
        else if( o[i] == 2 ) x |= ( t[i] & mask );
        else if( o[i] == 3 ) x ^= ( t[i] & mask );
    }
    return x;
}

int main() {
    static char in[10];
    scanf("%d%d",&n,&m);
    while(m) t[++len] = m & 1 , m >>= 1;
    for(int i=1;i<=n;i++) scanf("%s%lld",in,t+i) , o[i] = *in == 'A' ? 1 : *in == 'O' ? 2 : 3;
    for(int i=32;i;i--) {
        lli f0 = f(1<<(i-1),0) , f1 = f(1<<(i-1),1<<(i-1));
        if( i > len ) ans |= f0;
        else ans |= std::max( f0 , f1 );
    }
    printf("%lld\n",ans);
    return 0;
}