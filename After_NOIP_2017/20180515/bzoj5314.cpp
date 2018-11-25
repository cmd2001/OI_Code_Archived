#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
typedef unsigned long long int ulli;
const unsigned maxn=1e5+1e2,maxe=1e2+1e1;
const unsigned mod=1e9+7;

unsigned s[maxn],t[maxn<<1],nxt[maxn<<1],siz[maxn];
unsigned f[maxn][maxe][2][2],tp[maxe][2][2];
unsigned n,k;

__inline void add(unsigned& dst,const unsigned &x) {
    dst = ( dst + x ) % mod;
}
__inline unsigned mul(const unsigned &x,const unsigned &y) {
    return (ulli) x * y % mod;
}

__inline void addedge(unsigned from,unsigned to) {
    static unsigned cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}

inline void dfs(unsigned pos,unsigned fa) {
    siz[pos] = f[pos][0][0][0] = f[pos][1][1][0] = 1;
    for(unsigned at=s[pos];at;at=nxt[at]) if( t[at] != fa ) { // sizeof(unsigned[2][2]) * (siz[pos]+1)
        dfs(t[at],pos) , memcpy(tp,f[pos],(siz[pos]+1)<<4) , memset(f[pos],0,(siz[pos]+1)<<4);
        for(register unsigned i=0;i<=siz[pos];i++) for(register unsigned j=0;j<=siz[t[at]]&&i+j<=k;j++) {
            add( f[pos][i+j][0][0] , mul( tp[i][0][0] , f[t[at]][j][0][1] ) ) ,
            add( f[pos][i+j][0][1] , mul( tp[i][0][0] , f[t[at]][j][1][1] ) + mul( tp[i][0][1] , f[t[at]][j][0][1] + f[t[at]][j][1][1] ) ) ,
            add( f[pos][i+j][1][0] , mul( tp[i][1][0] , f[t[at]][j][0][0] + f[t[at]][j][0][1] ) ) ,
            add( f[pos][i+j][1][1] , mul( tp[i][1][0] , f[t[at]][j][1][0] + f[t[at]][j][1][1] ) + mul( tp[i][1][1] , f[t[at]][j][0][0] + f[t[at]][j][0][1] + f[t[at]][j][1][0] + f[t[at]][j][1][1] ) );
        }
        siz[pos] = std::min( k , siz[pos] + siz[t[at]] );
    }
}

 
__inline unsigned char nextchar() {
    static const int BS = 1 << 21;
    static unsigned char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? 0 : *st++;
}
__inline unsigned getint() {
    unsigned ret = 0 , ch;
    while( !isdigit(ch=nextchar()) ) ;
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    n = getint() , k = getint();
    for(register unsigned i=1,a,b;i<n;i++) a = getint() , b = getint() , addedge(a,b) , addedge(b,a);
    dfs(1,-1) , printf("%u\n",(f[1][k][0][1]+f[1][k][1][1])%mod);
    return 0;
}
