#pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
#include<cctype>
const unsigned maxn=2e3+1e2;
const unsigned mod=1e9+7;

inline void add(unsigned &x,const unsigned &y) {
    if( ( x += y ) >= mod ) x -= mod;
}
inline void sub(unsigned &x,const unsigned &y) {
    if( x < y ) x += mod;
    x -= y;
}
inline unsigned mul(const unsigned &x,const unsigned &y) {
    return (unsigned long long) x * y % mod;
}

int in[maxn],srt[maxn];
unsigned n,len;

struct BinaryIndexTree {
    unsigned dat[maxn];
    #define lowbit(x) (x&-x);
    inline void update(unsigned pos,unsigned x) {
        while( pos <= len ) add(dat[pos],x) , pos += lowbit(pos);
    }
    inline unsigned query(unsigned pos) {
        unsigned ret = 0;
        while(pos) add(ret,dat[pos]) , pos -= lowbit(pos);
        return ret;
    }
}bit[maxn];

unsigned f[maxn][maxn],g[maxn],fac[maxn],ans;
char buf[1<<20],*st=buf,*ed=buf;

__inline char nextchar() {
    return st == ed ? -1 : *st++;
}
__inline int getint() {
    int ret = 0 , fix = 1 , ch;
    while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret * fix;
}

int main() {
    ed = buf + fread(st=buf,1,1<<20,stdin) , n = getint() , *fac = 1;
    for(unsigned i=1;i<=n;i++) in[i] = getint() , srt[i] = in[i] , fac[i] = mul(fac[i-1],i);
    std::sort(srt+1,srt+1+n) , len = std::unique(srt+1,srt+1+n) - srt - 1 , bit[0].update(1,1);
    for(unsigned i=1;i<=n;i++) in[i] = std::lower_bound(srt+1,srt+1+len,in[i]) - srt;
    for(unsigned i=1;i<=n;i++) for(unsigned j=i;j;j--) f[i][j] = bit[j-1].query(in[i]) ,bit[j].update(in[i],f[i][j]);
    for(unsigned i=1;i<=n;i++) for(unsigned j=1;j<=n;j++) add(g[j],f[i][j]);
    for(unsigned i=1;i<n;i++) add(ans,mul(g[i],fac[n-i])) , sub(ans,mul(g[i+1],mul(fac[n-i-1],i+1)));
    printf("%u\n",ans);
    return 0;
}
