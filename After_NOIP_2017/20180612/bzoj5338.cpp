#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
const int maxn=1e5+1e2,maxe=4e6+1e2;

int rt_cha[maxn],rt_seg[maxn];

struct PersistentTrie {
    int ch[maxe][2],siz[maxe],cnt;
    inline void insert(int &pos,const int &pre,const int &x,int bit) { // bit from 31 downto 0 .
        siz[pos=++cnt] = siz[pre] + 1;
        if( !~bit ) return;
        int cur = ( x >> bit ) & 1;
        insert(ch[pos][cur],ch[pre][cur],x,bit-1) , ch[pos][cur^1] = ch[pre][cur^1];
    }
    inline int query(int pos,int pre,const int &x,int bit) {
        if( !~bit || pos == pre ) return 0;
        int cur = ( x >> bit ) & 1 ^ 1;
        if( siz[ch[pos][cur]] != siz[ch[pre][cur]] ) return query(ch[pos][cur],ch[pre][cur],x,bit-1) | ( 1 << bit );
        else return query(ch[pos][cur^1],ch[pre][cur^1],x,bit-1);
    }
}cha,seg;

int in[maxn];
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],siz[maxn],dep[maxn],son[maxn],top[maxn],dfn[maxn],rit[maxn],dd;

inline void coredge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}

inline void pre(int pos) {
    siz[pos] = 1 , cha.insert(rt_cha[pos],rt_cha[fa[pos]],in[pos],31);
    rit[pos] = dfn[pos] = ++dd , seg.insert(rt_seg[dd],rt_seg[dd-1],in[pos],31);
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1 , pre(t[at]) , rit[pos] = rit[t[at]];
        siz[pos] += siz[t[at]] , son[pos] = siz[t[at]] > siz[son[pos]] ? t[at] : son[pos];
    }
}
inline void dfs(int pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) dfs(t[at]);
}
inline int lca(int x,int y) {
    while( top[x] != top[y] ) dep[top[x]] > dep[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
    return dep[x] < dep[y] ? x : y;
}

inline int query_subtree(int pos,int val) {
    return seg.query(rt_seg[rit[pos]],rt_seg[dfn[pos]-1],val,31);
}
inline int query_chain(int x,int y,int val) {
    int l = lca(x,y);
    return max( cha.query(rt_cha[x],rt_cha[fa[l]],val,31) , cha.query(rt_cha[y],rt_cha[fa[l]],val,31) );
}

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    static int n,q;
    n = getint() , q = getint();
    for(int i=1;i<=n;i++) in[i] = getint();
    for(int i=1;i<n;i++) addedge(getint(),getint());
    pre(1) , dfs(1);
    for(int i=1,tpe,x,y;i<=q;i++) {
        tpe = getint() , x = getint() ,y = getint();
        printf("%d\n",tpe==1?query_subtree(x,y):query_chain(x,y,getint()));
    }
    return 0;
}
