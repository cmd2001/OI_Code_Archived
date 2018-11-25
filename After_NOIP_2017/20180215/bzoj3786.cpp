#pragma GCC optimize(3)
#include<cstdio>
#include<cctype>
#define lli long long int
const int maxn=2e5+1e2;

int st,ed;

struct Splay {
    int ch[maxn][2],fa[maxn],tpe[maxn],siz[maxn],cnt,root;
    lli sum[maxn],dat[maxn],lazy[maxn];
    
    inline void set(int pos,lli add) {
        if( !pos ) return;
        dat[pos] += tpe[pos] * add , sum[pos] += siz[pos] * add , lazy[pos] += add;
    }
    inline void push(int pos) {
        if( !lazy[pos] ) return;
        set(ch[pos][0],lazy[pos]) ,
        set(ch[pos][1],lazy[pos]) ,
        lazy[pos] = 0;
    }
    inline void up(int fa,int son) {
        if( !son ) return;
        siz[fa] += siz[son] , sum[fa] += sum[son];
    }
    inline void upgrade(int pos) {
        siz[pos] = tpe[pos] , sum[pos] = dat[pos];
        up(pos,ch[pos][0]) ,
        up(pos,ch[pos][1]) ;
    }
    inline int gid(int x) {
        return x == ch[fa[x]][1];
    }
    inline void rotate(int x) {
        const int f = fa[x] , id = gid(x);
        push(f) , push(x);
        fa[x] = fa[f];
        if( fa[f] ) ch[fa[f]][gid(f)] = x;
        else root = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        ch[x][id^1] = f , fa[f] = x;
        upgrade(f) , upgrade(x);
    }
    inline void splay(int pos) {
        while( pos != root ) {
            if( fa[fa[pos]] ) rotate(fa[pos]);
            rotate(pos);
        }
    }
    inline void upchain(int pos) {
        while( pos != root ) {
            upgrade(pos) , pos = fa[pos];
        }
    }
    inline int insert(int tp,int va) {
        if( !root ) {
            root = ++cnt , tpe[root] = tp , sum[root] = dat[root] = tp * va;
            return root;
        }
        int ret = ++cnt , now = root;
        tpe[ret] = tp , sum[ret] = dat[ret] = tp * va;
        while( ch[now][1] ) now = ch[now][1];
        ch[now][1] = ret , fa[ret] = now;
        upchain(ret);
        splay(ret);
        return ret;
    }
    inline void mkrson(int pos) {
        while( pos != ch[root][1] ) {
            if( fa[pos] != ch[root][1] ) rotate(fa[pos]);
            rotate(pos);
        }
    }
    inline void pushchain(int pos) {
        if( pos != root ) pushchain(fa[pos]);
        push(pos);
    }
    inline int getprv(int pos) {
        if( pos == st ) return -1;
        if( ch[pos][0] ) {
            int ret = ch[pos][0];
            while( ch[ret][1] ) ret = ch[ret][1];
            return ret;
        }
        while( pos == ch[fa[pos]][0] ) pos = fa[pos];
        return fa[pos];
    }
    inline int getnxt(int pos) {
        if( pos == ed ) return -1;
        if( ch[pos][1] ) {
            int ret = ch[pos][1];
            while( ch[ret][0] ) ret = ch[ret][0];
            return ret;
        }
        while( pos == ch[fa[pos]][1] ) pos = fa[pos];
        return fa[pos];
    }
    inline void update(int posl,int posr,lli add) {
        int prv = getprv(posl) , nxt = getnxt(posr);
        if( !~prv && !~nxt ) {
            set(root,add);
            return;
        }
        splay(prv) , mkrson(nxt);
        int pos = ch[ch[root][1]][0];
        set(pos,add);
        splay(pos);
    }
    inline int segment(int posl,int posr) { // assert posl != in[1] && posr != out[1] .
        int prv = getprv(posl) , nxt = getnxt(posr);
        splay(prv) , mkrson(nxt);
        return ch[ch[root][1]][0];
    }
    inline void move(int posl,int posr,int nfa) {
        int pos = segment(posl,posr);
        pushchain(fa[pos]);
        ch[fa[pos]][gid(pos)] = 0 , fa[pos] = 0;
        splay(nfa);
        int tar = ch[nfa][1];
        while( ch[tar][0] ) tar = ch[tar][0];
        pushchain(tar);
        ch[tar][0] = pos , fa[pos] = tar;
        splay(pos);
    }
    inline lli query(int pos) {
        int nxt = getnxt(pos);
        splay(nxt);
        return sum[ch[root][0]];
    }
}T;

int s[maxn>>1],t[maxn],nxt[maxn];
int in[maxn>>1],out[maxn>>1];
int w[maxn>>1];

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos) {
    in[pos] = T.insert(1,w[pos]);
    for(int at=s[pos];at;at=nxt[at])
        dfs(t[at]);
    out[pos] = T.insert(-1,w[pos]);
}

inline char nextchar() {
    const static int BS = 1 << 21;
    static char buf[BS],*st=buf+BS,*ed=buf+BS;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}
inline char realchar() {
    char ret;
    while( !isalpha(ret=nextchar()) ) ;
    return ret;
}
int main() {
    static int n,m;
    static char o;
    n = getint();
    for(int i=2,f;i<=n;i++) {
        f = getint();
        addedge(f,i);
    }
    for(int i=1;i<=n;i++) w[i] = getint();
    dfs(1) , st = in[1] , ed = out[1];
    m = getint();
    for(int i=1,p,x;i<=m;i++) {
        o = realchar() , p = getint();
        if( o == 'Q' ) printf("%lld\n",T.query(in[p]));
        else {
            x = getint();
            if( o == 'F' ) T.update(in[p],out[p],x);
            else T.move(in[p],out[p],in[x]);
        }
    }
    return 0;
}
