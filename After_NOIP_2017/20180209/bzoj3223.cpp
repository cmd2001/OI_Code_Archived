#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

struct Splay {
    int ch[maxn][2],fa[maxn],root,cnt;
    int dat[maxn],rev[maxn],siz[maxn];
    
    inline void mrk(int pos) {
        if( !pos ) return;
        rev[pos] ^= 1;
    }
    inline void push(int pos) {
        if( !rev[pos] ) return;
        swap(ch[pos][0],ch[pos][1]);
        mrk(ch[pos][0]) , mrk(ch[pos][1]);
        rev[pos] = 0;
    }
    inline void update(int pos) {
        siz[pos] = 1;
        if( ch[pos][0] ) siz[pos] += siz[ch[pos][0]];
        if( ch[pos][1] ) siz[pos] += siz[ch[pos][1]];
    }
    inline int gid(int x) {
        return x == ch[fa[x]][1];
    }
    inline void rotate(int x) {
        if( fa[fa[x]] ) push(fa[fa[x]]);
        push(fa[x]) , push(x);
        const int id = gid(x) , f = fa[x];
        fa[x] = fa[f];
        if( f != root ) ch[fa[f]][gid(f)] = x;
        else root = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        ch[x][id^1] = f , fa[f] = x;
        update(x) , update(f);
    }
    inline void splay(int x) {
        while( x != root ) {
            if( fa[fa[x]] ) rotate(fa[x]);
            rotate(x);
        }
    }
    inline void mkrson(int x) {
        while( x != ch[root][1] ) {
            if( fa[x] != ch[root][1] ) rotate(fa[x]);
            rotate(x);
        }
    }
    inline int kth(int k) {
        int now = root;
        while( 1 ) {
            push(now);
            if( k <= siz[ch[now][0]] ) now = ch[now][0];
            else if( k == siz[ch[now][0]] + 1 ) return now;
            else k -= siz[ch[now][0]] + 1 , now = ch[now][1];
        }
    }
    inline int nxtroot() {
        int ret = ch[root][1];
        while( push(ret),ch[ret][0] ) ret = ch[ret][0];
        return ret;
    }
    inline void addnode(int &pos,int f,int x) {
        pos = ++cnt , dat[pos] = x , siz[pos] = 1 , fa[pos] = f;
        for(int t=pos;t;t=fa[t]) update(t);
        splay(pos);
    }
    inline void insert(int tar,int x) {
        int pos = kth(tar);
        splay(pos);
        if( !ch[pos][1] ) {
            addnode(ch[pos][1],pos,x);
        } else {
            pos = nxtroot();
            addnode(ch[pos][0],pos,x);
        }
    }
    inline void work(int l,int r) {
        r += 2;
        l = kth(l) , r = kth(r);
        splay(l) , mkrson(r);
        mrk(ch[ch[root][1]][0]);
    }
    inline void dfs(int pos) {
        push(pos);
        if( ch[pos][0] ) dfs(ch[pos][0]);
        if( dat[pos] ) printf("%d ",dat[pos]);
        if( ch[pos][1] ) dfs(ch[pos][1]);
    }
    Splay() {
        dat[root=cnt=1] = 0 , siz[root] = 1;
        insert(1,0);
    }
}t;

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        t.insert(i,i);
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d",&a,&b);
        t.work(a,b);
    }
    t.dfs(t.root);
    puts("");
    return 0;
}
