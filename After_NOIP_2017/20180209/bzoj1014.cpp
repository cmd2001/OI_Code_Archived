#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define NDEBUG
#define ulli unsigned long long
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
const ulli base = 233;

char in[maxn];
ulli pows[maxn];
int len;

struct Splay {
    int ch[maxn][2],fa[maxn],siz[maxn],root,cnt;
    ulli dat[maxn],hsh[maxn];
    
    inline void update(int pos) {
        siz[pos] = 1 , hsh[pos] = 0;
        if( ch[pos][0] ) hsh[pos] = hsh[ch[pos][0]] , siz[pos] += siz[ch[pos][0]];
        hsh[pos] = hsh[pos] * base + dat[pos];
        if( ch[pos][1] ) hsh[pos] = hsh[pos] * pows[siz[ch[pos][1]]] + hsh[ch[pos][1]] , siz[pos] += siz[ch[pos][1]];
    }
    inline int gid(int x) {
        return x == ch[fa[x]][1];
    }
    inline void rotate(int x) {
        const int id = gid(x) , f = fa[x];
        fa[x] = fa[f];
        if( f != root ) ch[fa[f]][gid(f)] = x;
        else root = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        ch[x][id^1] = f , fa[f] = x;
        update(f) , update(x);
    }
    inline void splay(int pos) {
        while( root != pos ) {
            if( fa[fa[pos]] ) rotate(fa[pos]);
            rotate(pos);
        }
    }
    inline void mkrson(int pos) {
        while( pos != ch[root][1] ) {
            if( fa[pos] != ch[root][1] ) rotate(fa[pos]);
            rotate(pos);
        }
    }
    inline void addnode(int& x,int f,int dd) {
        x = ++cnt , fa[x] = f;
        siz[x] = 1 , hsh[x] = dat[x] = dd;
        for(int t=x;t;t=fa[t]) update(t);
        splay(x);
    }
    inline void firstnode(int d) {
        siz[root=cnt=1] = 1 , hsh[1] = dat[1] = d;
    }
    inline int kth(int k) {
        int pos = root;
        while( 1 ) {
            if( k <= siz[ch[pos][0]] ) pos = ch[pos][0];
            else if( k == siz[ch[pos][0]] + 1 ) return pos;
            else k -= siz[ch[pos][0]] + 1 , pos = ch[pos][1];
        }
    }
    inline int nxtroot() {
        int ret = ch[root][1];
        while( ch[ret][0] ) ret = ch[ret][0];
        return ret;
    }
    inline void insert(int tar,int d) { // insert to tar + 1 th.
        if( !tar ) {
            int pos = root;
            while( ch[pos][0] ) pos = ch[pos][0];
            addnode(ch[pos][0],pos,d);
        } else {
            int pos = kth(tar);
            splay(pos);
            int nxt = nxtroot();
            if( !nxt ) addnode(ch[pos][1],pos,d);
            else addnode(ch[nxt][0],nxt,d);
        }
    }
    inline void modify(int tar,int d) {
        int pos = kth(tar);
        splay(pos);
        dat[pos] = d;
        update(pos);
    }
    inline ulli query(int l,int r) {
        l = kth(l) , r = kth(r);
        if( l == r ) return dat[l];
        splay(r);
        if( !ch[r][1] ) {
            splay(l);
            return dat[l] * pows[siz[ch[root][1]]] + hsh[ch[root][1]];
        } else {
            int nxt = nxtroot();
            splay(l) , mkrson(nxt);
            return dat[l] * pows[siz[ch[nxt][0]]] + hsh[ch[nxt][0]];
        }
    }
}t;

inline bool judge(int l,int r,int len) {
    ulli ql = t.query(l,l+len-1) , qr = t.query(r,r+len-1);
    return ql == qr;
}
inline int bin(int a,int b) {
    int l = 0 , r = len - max(a,b) + 1, mid;
    if( judge(a,b,r) ) return r;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( judge(a,b,mid) ) l = mid;
        else r = mid;
    }
    return l;
}

inline void initpows() {
    *pows = 1;
    for(int i=1;i<=len;i++) pows[i] = pows[i-1] * base;
}

int main() {
    static char o[10],ins[10];
    static int n;
    scanf("%s",in+1) , len = strlen(in+1);
    initpows();
    t.firstnode(in[1]-'a'+1);
    for(int i=2;i<=len;i++)
        t.insert(i-1,in[i]-'a'+1);
    scanf("%d",&n);
    for(int i=1,a,b,x;i<=n;i++) {
        scanf("%s",o);
        if( *o == 'Q' ) {
            scanf("%d%d",&a,&b);
            printf("%d\n",bin(a,b));
        } else if( *o == 'I' ) {
            scanf("%d%s",&x,ins) , ++len;
            pows[len] = pows[len-1] * base;
            t.insert(x,*ins-'a'+1);
        } else if( *o == 'R' ) {
            scanf("%d%s",&x,ins);
            t.modify(x,*ins-'a'+1);
        }
    }
    return 0;
}
