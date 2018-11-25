#pragma GCC optimize(2)
#include<cstdio>
#include<cctype>
const unsigned maxn=3e6+1e2,maxk=1e3+1e2;

unsigned s[maxn],t[maxn],nxt[maxn],cnt,fs;
unsigned fa[maxn],siz[maxn],dep[maxn],son[maxn],top[maxn];
unsigned dat[maxk][maxk],len[maxk],qs;

__inline void addedge(const unsigned &from,const unsigned &to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(unsigned pos) {
    siz[pos] = 1;
    for(unsigned at=s[pos];at;at=nxt[at]) {
        dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos , pre(t[at]) , siz[pos] += siz[t[at]] ,
        son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
    }
}
inline void dfs(unsigned pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    for(unsigned at=s[pos];at;at=nxt[at]) dfs(t[at]);
}
__inline unsigned lca(unsigned x,unsigned y) {
    while( top[x] != top[y] ) dep[top[x]] > dep[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
    return dep[x] < dep[y] ? x : y;
}

__inline unsigned char nextchar() {
    static const unsigned BS = 1 << 22;
    static unsigned char buf[BS],*st=buf+BS,*ed=st;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
__inline unsigned char realchar() {
    unsigned char c;
    while( !isalpha(c=nextchar()) );
    return c;
}
__inline unsigned getint() {
    unsigned ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    unsigned n;
    n = getint() , fs = 1;
    for(unsigned i=1,o;i<=n;i++) {
        o = realchar();
        if( o == 'A' ) addedge(getint(),++fs);
        else if( o == 'Q' ) {
            len[++qs] = getint();
            for(unsigned j=1;j<=len[qs];j++) dat[qs][j] = getint();
        }
    }
    pre(1) , dfs(1);
    for(unsigned i=1;i<=qs;i++) {
        unsigned ans = dat[i][1];
        for(unsigned j=2;j<=len[i];j++) ans = lca(ans,dat[i][j]);
        printf("%u\n",ans);
    }
    return 0;
}
