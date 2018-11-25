#include<cstdio>
#include<cctype>
typedef unsigned int uint;
typedef unsigned long long int ulli;
const uint maxn=5e6+1e2;

uint s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
uint deg[maxn],f[maxn],g[maxn],pfs[maxn],as[maxn],assq[maxn];
uint pi,ans,n,mod,inv,root;

inline uint add(const uint &a,const uint &b) {
    uint ret = a + b;
    return ret >= mod ? ret - mod : ret;
}
inline uint sub(const uint &a,const uint &b) {
    return a >= b ? a - b : a + mod - b;
}
inline uint mul(const uint &a,const uint &b) {
    return (ulli) a * b % mod;
}
inline void adde(uint &a,const uint &b) {
    a = add(a,b);
}
inline void sube(uint &a,const uint &b) {
    a = sub(a,b);
}
inline void mule(uint &a,const uint &b) {
    a = (ulli) a * b % mod;
}

inline uint fastpow(uint base,uint tim) {
    uint ret = 1;
    while(tim) {
        if( tim & 1 ) mule(ret,base);
        if( tim >>= 1 ) base = mul(base,base);
    }
    return ret;
}

inline void addedge(uint from,uint to,uint len) {
    static uint cnt;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dualedge(uint a,uint b,uint len) {
    addedge(a,b,len) , addedge(b,a,len);
}
inline void dfs1(uint pos,uint fa) {
    pfs[pos] = 1;
    bool isleaf = 1;
    for(uint at=s[pos],fs;at;at=nxt[at]) if( t[at] != fa ) {
        isleaf = 0 , dfs1(t[at],pos) , fs = mul(f[t[at]],l[at]);
        adde(f[pos],fs) , mule(pfs[pos],add(fs,1)) , adde(as[pos],fs) , adde(assq[pos],mul(fs,fs));
    }
    adde(f[pos],isleaf);
}
inline void dfs2(uint pos,uint fa,uint lat) {
    if( ~fa ) {
        g[pos] = mul(add(g[fa],sub(f[fa],mul(f[pos],lat))),lat);
        mule(pfs[pos],add(g[pos],1)) , adde(as[pos],g[pos]) , adde(assq[pos],mul(g[pos],g[pos]));
    }
    for(uint at=s[pos];at;at=nxt[at]) if( t[at] != fa ) dfs2(t[at],pos,l[at]);
}
inline void getans() {
    for(uint i=1;i<=n;i++) {
        if( deg[i] >= 3 ) adde(ans,sub(add(pfs[i],mul(assq[i],inv)),add(mul(mul(as[i],as[i]),inv),add(as[i],1))));
    }
}


namespace FastIO {
    inline unsigned char nextchar() {
        static const int BS = 1 << 22;
        static unsigned char buf[BS],*st,*ed;
        if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
        return st == ed ? 0 : *st++;
    }
    inline uint getint() {
        uint ret = 0 , ch;
        while( !isdigit(ch=nextchar()) );
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
}
using FastIO::getint;

int main() {
    if( getint() - 1 ) return 0;
    n = getint() , mod = getint() , root = -1 , pi = 1 , inv = fastpow(2,mod-2);
    for(uint i=1,a,b,d,e;i<n;i++) a = getint() , b = getint() , d = getint() , e = getint() , mule(pi,e) , dualedge(a,b,mul(d,fastpow(e,mod-2))) , ++deg[a] , ++deg[b];
    for(uint i=1;i<=n&&!~root;i++) if( deg[i] > 2 ) root = i;
    if( !~root ) return puts("0"),0;
    dfs1(root,-1) , dfs2(root,-1,0) , getans() , printf("%u\n",mul(ans,pi));
    return 0;
}
