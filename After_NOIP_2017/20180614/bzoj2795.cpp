#include<cstdio>
typedef long long int lli;
typedef unsigned long long int ulli;
const int maxn=5e5+1e2;
const ulli base = 31;

char in[maxn];
int miv[maxn];
int n;

inline void sieve() {
    static int prime[maxn],cnt;
    static bool vis[maxn];
    for(int i=2;i<=n;i++) {
        if( !vis[i] ) prime[++cnt] = i , miv[i] = i;
        for(int j=1;(lli)i*prime[j]<=n;j++) {
            const int t = i * prime[j];
            vis[t] = 1 , miv[t] = prime[j];
            if( ! ( i % prime[j] ) ) break;
        }
    }
}

ulli h[maxn],pows[maxn];

inline ulli seg(int l,int r) {
    return h[r] - h[l-1] * pows[r-l+1];
}
inline void inithsh() {
    *pows = 1;
    for(int i=1;i<=n;i++) h[i] = h[i-1] * base + in[i] - 'a' , pows[i] = pows[i-1] * base;
}

inline int calc(int l,int r,int len) {
    for(int i=len;i!=1;) {
        const int t = miv[i];
        while( ! ( len % t ) && seg(l,r-len/t) == seg(l+len/t,r) ) len /= t;
        while( ! ( i % t ) ) i /= t;
    }
    return len;
}

int main() {
    static int m;
    scanf("%d%s%d",&n,in+1,&m) , inithsh() , sieve();
    for(int i=1,l,r;i<=m;i++) scanf("%d%d",&l,&r) , printf("%d\n",calc(l,r,r-l+1));
    return 0;
}

