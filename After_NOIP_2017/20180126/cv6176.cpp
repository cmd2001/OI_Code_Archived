#include<cstdio>
#include<cctype>
#define lli long long int
const int maxn=3197152;
//const int mod=2013265921,g=31;
const lli mod=(17ll<<27)+1,g=3;

char in[maxn];
lli a[maxn],b[maxn];

inline void swap(lli &a,lli &b) {
    register lli t = a ;
    a = b , b = t;
}
inline lli fastpow(lli base,lli tme,lli mod) {
    register lli ret = 1 , now = base % mod;
    while( tme ) {
        if( tme & 1 ) ret = ret * now % mod;
        now = now * now % mod;
        tme >>= 1;
    }
    return ret;
}

inline void NTT(lli* dst,int n,int ope) {
    for(register int i=0,j=0;i<n;++i) {
        if( i < j ) swap( dst[i] , dst[j] );
        for(register int l = n >> 1 ; ( j ^= l ) < l ; l >>= 1 ) ;
    }
    for(register int len=2;len<=n;len<<=1) {
        register lli per = fastpow(g,mod/len,mod);
        if( !~ope ) per = fastpow(per,mod-2,mod);
        for(register int st=0;st<n;st+=len) {
            lli w = 1;
            for(register int pos=0;pos<len>>1;++pos) {
                const register lli u = dst[st+pos] , v = dst[st+pos+(len>>1)] * w % mod;
                dst[st+pos] = ( u + v ) % mod ,
                dst[st+pos+(len>>1)] = ( u - v + mod ) % mod;
                w = w * per % mod;
            }
        }
    }
    if( !~ope ) {
        const register lli inv = fastpow(n,mod-2,mod);
        for(register int i=0;i<n;++i)
            dst[i] =dst[i] * inv % mod;
    }
}

inline bool judchar(char ch) {
    return isdigit(ch) || isalpha(ch);
}
inline char nextchar() {
    #define BS (1<<21)
    static char buf[BS],*st=buf+BS,*ed=buf+BS;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
inline void getlin(char* dst,int &len) {
    char ch;
    while( !judchar(ch=getchar()) );
    do dst[len++]=ch; while( judchar(ch=getchar()) );
}
inline int cov(char x) {
    return isdigit(x) ? x - '0' : x - 'A' + 10 ;
}
inline char recov(lli x) {
    return x < 10 ? x + '0' : x - 10 + 'A';
}


int main() {
    static int la,lb,n,len=1;
    n = getint();
    getlin(in,la);
    for(register int i=0;i<la;++i)
        a[la-i-1] = cov(in[i]);
    getlin(in,lb);
    for(register int i=0;i<lb;++i)
        b[lb-i-1] = cov(in[i]);
    while( len < la + lb )
        len <<= 1;
    NTT(a,len,1) , NTT(b,len,1);
    for(register int i=0;i<len;++i)
        a[i] = a[i] * b[i] % mod;
    NTT(a,len,-1);
    for(register int i=0;i<len;++i)
        a[i+1] += a[i] / n , a[i] %= n;
    while( a[len] )
        a[len+1] += a[len] / n , a[len] %= n;
    while( len && !a[len-1] ) --len;
    if( !len ) putchar('0');
    for(register int i=len-1;~i;--i)
        putchar(recov(a[i]));
    putchar('\n');
    return 0;
}

