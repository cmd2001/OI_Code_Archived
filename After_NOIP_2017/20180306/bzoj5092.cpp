#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=3e5+1e2,maxm=4e6+1e2,lim=2097152;

int in[maxn],f[maxm];

inline void pre() {
    for(int b=0;b<=20;b++)
        for(int i=0;i<lim;i++)
            if( ! ( i & ( 1 << b ) ) ) f[i] = std::min( f[i] , f[i|(1<<b)] );
}

int main() {
    static int n;
    scanf("%d",&n) , memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++) {
        scanf("%d",in+i) , 
        in[i] ^= in[i-1] , 
        f[in[i]] = std::min( f[in[i]] , i );
    }
    pre();
    for(int i=1,cur;i<=n;i++) {
        cur = 0;
        for(int b=20;~b;b--) if( ! ( in[i] & ( 1 << b ) ) ) {
            if( f[cur|(1<<b)] <= i ) cur |= ( 1 << b );
        }
        printf("%d\n",(in[i]^cur)+cur);
    }
    return 0;
}
