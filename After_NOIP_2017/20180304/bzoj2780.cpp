#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=3.6e5+1e2,maxp=1e5+1e2;
 
 
int cov[maxn]; // covert string number to ACauto Node.
 
namespace ACauto {
    struct Queue {
        int dat[maxn],st,ed;
        inline bool empty() {
            return st == ed;
        }
        inline void push(int x) {
            dat[ed++] = x;
        }
        inline int pop() {
            return dat[st++];
        }
    }q;
     
    int ch[maxn][26],fail[maxn],root,cnt;
     
    inline int NewNode() {
        return ++cnt;
    }
    inline void insert(char* str,int len,int id) {
        int now = root;
        for(int i=1;i<=len;i++) {
            const int t = str[i] - 'a';
            if( !ch[now][t] )
                ch[now][t] = NewNode();
            now = ch[now][t];
        }
        cov[id] = now;
    }
    inline void buildfail() {
        fail[root] = root;
        for(int i=0;i<26;i++)
            if( ch[root][i] ) {
                fail[ch[root][i]] = root;
                q.push(ch[root][i]);
            }
            else
                ch[root][i] = root;
        while( !q.empty() ) {
            const int pos = q.pop();
            for(int i=0;i<26;i++) {
                if( ch[pos][i] ) {
                    fail[ch[pos][i]] = ch[fail[pos]][i];
                    q.push(ch[pos][i]);
                }
                else
                    ch[pos][i] = ch[fail[pos]][i];
            }
        }
    }
    inline void init() {
        root = NewNode();
    }
}
namespace Tree {
    struct BinaryIndexTree {
        int dat[maxn],siz;
         
        #define lowbit(x) (x&-x)
         
        inline void update(int pos,int x) {
            while( pos <= siz )
                dat[pos] += x,
                pos += lowbit(pos);
        }
        inline int query(int pos) {
            int ret = 0;
            while( pos )
                ret += dat[pos],
                pos -= lowbit(pos);
            return ret;
        }
        inline void resize(int ss) {
            siz = ss;
        }
    }bit;
     
    int s[maxn],t[maxn<<1],nxt[maxn<<1],dfn[maxn],mxr[maxn];
    int siz[maxn],dep[maxn],fa[maxn],son[maxn],top[maxn];
     
    inline void addedge(int from,int to) {
        static int cnt = 0;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void pre(int pos) {
        static int dd = 0;
        siz[pos] = 1 , mxr[pos] = dfn[pos] = ++dd;
        for(int at=s[pos];at;at=nxt[at])
            if( t[at] != fa[pos] ) {
                fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1;
                pre(t[at]); mxr[pos] = mxr[t[at]];
                siz[pos] += siz[t[at]] , son[pos] = siz[t[at]] > son[pos] ? t[at] : son[pos];
            }
    }
    inline void dfs(int pos) {
        top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
        for(int at=s[pos];at;at=nxt[at])
            if( t[at] != fa[pos] )
                dfs(t[at]);
    }
     
    inline int lca(int x,int y) {
        while( top[x] != top[y] ) {
            if( dep[top[x]] > dep[top[y]] )
                x = fa[top[x]];
            else y = fa[top[y]];
        }
        return dep[x] < dep[y] ? x : y;
    }
}
 
struct QNode {
    int pos;
    friend bool operator < (const QNode &a,const QNode &b) {
        using Tree::dfn;
        return dfn[a.pos] < dfn[b.pos];
    }
}ns[maxn];
int nc;
 
inline void pir(char* s,int len) {
    using ACauto::ch; using ACauto::root;
    nc = 0;
    int pos = root;
    for(int i=1;i<=len;i++) {
         int t = s[i] - 'a';
         pos = ch[pos][t];
         if( pos != root )
            ns[++nc] = (QNode){pos};
    }
}
 
inline void insert(char* s,int len) {
    using Tree::dfn; using Tree::bit; using Tree::lca;
    pir(s,len);
    sort(ns+1,ns+1+nc);
    for(int i=1;i<=nc;i++) bit.update(dfn[ns[i].pos],1);
    for(int i=2;i<=nc;i++) {
        int l = lca(ns[i].pos,ns[i-1].pos);
        bit.update(dfn[l],-1);
    }
}
 
inline void trans() {
    using ACauto::fail; using ACauto::cnt;
    using Tree::bit; using Tree::addedge;
     
    bit.resize(cnt);
    for(int i=2;i<=cnt;i++)
        addedge(fail[i],i);
     
    Tree::pre(1);
    Tree::dfs(1);
}
 
inline int query(int x) {
    using Tree::bit; using Tree::dfn; using Tree::mxr;
    return bit.query(mxr[x]) - bit.query(dfn[x]-1);
}
 
inline void getstr(char* dst,int& len) {
    char ch; len = 0;
    do ch=getchar(); while(!isalpha(ch));
    do dst[++len] = ch; while(isalpha(ch=getchar()));
    dst[len+1] = '\0';
}
inline int getint() {
    int ret = 0 , ch;
    do ch=getchar(); while(!isdigit(ch));
    do ret=ret*10+ch-'0'; while(isdigit(ch=getchar()));
    return ret;
}

char tmps[maxp];
int sts[maxp];

int main() {
    static int n,m,len;
    static char buf[maxn];
    
    ACauto::init();
    
    n = getint() , m = getint();
    sts[1] = 1;
    for(int i=1;i<=n;i++) {
        scanf("%s",tmps+sts[i]);
        sts[i+1] = sts[i] + strlen(tmps+sts[i]);
    }
    for(int i=1;i<=m;i++) {
        scanf("%s",buf+1) , len = strlen(buf+1);
        ACauto::insert(buf,len,i);
    }
    ACauto::buildfail(); trans();
    for(int i=1;i<=n;i++) {
        insert(tmps+sts[i]-1,sts[i+1]-sts[i]);
    }
    for(int i=1;i<=m;i++) printf("%d\n",query(cov[i]));
    return 0;
}
