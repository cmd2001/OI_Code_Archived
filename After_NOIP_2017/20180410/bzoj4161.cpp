#pragma GCC optimize(3)
#include<cstdio>
#include<cstring>
#include<cctype>
typedef long long int lli;
const int maxn=4e3+1e2+3;
const int mod=1e9+7;

inline void add(int &a,const int &b) {
    a += b;
    if( a >= mod ) a -= mod;
}
inline void sub(int &a,const int &b) {
    a -= b;
    if( a < 0 ) a += mod;
}
inline int mul(const int &a,const int &b) {
    return (lli) a * b % mod;
}

int in[maxn],a[maxn];
int n,k;

int trans[maxn],ans[maxn],base[maxn],tp[maxn];

inline void mul(const int* a,const int* b) { // multi a and b into tp moding trans .
    memset(tp,0,sizeof(int)*(2*k+1));
    for(int i=0;i<=k;i++) for(int j=0;j<=k;j++)  add(tp[i+j],mul(a[i],b[j]));
    for(int i=k<<1;i>=k;i--) if( tp[i] ) for(int j=k;~j;j--) sub(tp[i-j],mul(tp[i],trans[k-j]));
}

inline void fastpow(int tim) {
    base[1] = ans[0] = 1;
    while(tim) {
        if( tim & 1 ) mul(ans,base) , memcpy(ans,tp,sizeof(int)*(k+1));
        if( tim >>= 1 ) mul(base,base) , memcpy(base,tp,sizeof(int)*(k+1));
    }
}

inline void pre() {
    for(int i=k;i<k<<1;i++) for(int j=1;j<=k;j++) add(in[i],mul(in[i-j],a[j]));
}

inline int getans() {
    trans[k] = 1; for(int i=1;i<=k;i++) trans[k-i] = mod - a[i];
    fastpow(n-k);
    int ret = 0;
    for(int i=0;i<k;i++) add(ret,mul(ans[i],in[i+k]));
    return ret;
}

inline int getint() {
    int ret = 0 , fx = 1 , ch;
    while( !isdigit(ch=getchar()) ) fx = ch == '-' ? -fx : fx;
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret * fx;
}
int main() {
    n = getint() , k = getint();
    for(int i=1;i<=k;i++) a[i] = getint() , add(a[i],mod);
    for(int i=0;i<k;i++) in[i] = getint() , add(in[i],mod);
    pre() , printf("%d\n",getans());
    return 0;
}
