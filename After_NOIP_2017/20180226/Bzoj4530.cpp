#include<cstdio>
#include<algorithm>
const int maxn=1e5+1e2;

struct LinkCutTree {
    int ch[maxn][2],fa[maxn],sum[maxn],fake[maxn],rev[maxn];
    inline void apply(int pos) {
        if( !pos ) return;
        rev[pos] ^= 1 , std::swap(ch[pos][0],ch[pos][1]);
    }
    inline void push(int pos) {
        if( !rev[pos] ) return;
        apply(ch[pos][0]) , apply(ch[pos][1]);
        rev[pos] = 0;
    }
    inline void upgrade(int pos) {
        sum[pos] = fake[pos] + 1;
        if( ch[pos][0] ) sum[pos] += sum[ch[pos][0]];
        if( ch[pos][1] ) sum[pos] += sum[ch[pos][1]];
    }
    inline bool isrt(int pos) {
        return pos != ch[fa[pos]][0] && pos != ch[fa[pos]][1];
    }
    inline int gid(int pos) {
        return pos == ch[fa[pos]][1];
    }
    inline void rotate(int x) {
        const int f = fa[x] , id = gid(x);
        fa[x] = fa[f];
        if( !isrt(f) ) ch[fa[f]][gid(f)] = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        ch[x][id^1] = f , fa[f] = x;
        upgrade(f) , upgrade(x);
    }
    inline void pushchain(int x) {
        if( !isrt(x) ) pushchain(fa[x]);
        push(x);
    }
    inline void splay(int x) {
        pushchain(x);
        while( !isrt(x) ) {
            if( !isrt(fa[x]) ) rotate(fa[x]);
            rotate(x);
        }
    }
    inline void access(int x) {
        int t = 0;
        while(x) {
            splay(x) , fake[x] += sum[ch[x][1]] - sum[t] , ch[x][1] = t , upgrade(x);
            t = x , x = fa[x];
        }
    }
    inline void mkrt(int x) {
        access(x) , splay(x) , apply(x);
    }
    inline void link(int x,int y) {
        mkrt(x) , mkrt(y);
        fa[x] = y , fake[y] += sum[x] , upgrade(y);
    }
    inline long long query(int x,int y) {
        mkrt(x) , mkrt(y);
        return (long long)sum[x] * (sum[y]-sum[x]);
    }
    inline void init(int n) {
        for(int i=1;i<=n;i++) sum[i] = 1;
    }
}t;

int main() {
    static int n,m;
    char o[10];
    scanf("%d%d",&n,&m) , t.init(n);
    for(int i=1,x,y;i<=m;i++) {
        scanf("%s%d%d",o,&x,&y);
        if( *o == 'A' ) t.link(x,y);
        else printf("%lld\n",t.query(x,y));
    }
    return 0;
}

