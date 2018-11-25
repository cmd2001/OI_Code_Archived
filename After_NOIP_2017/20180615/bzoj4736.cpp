#include<cstdio>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=4e5+1e2,maxm=3e5+1e2,maxt=1e5+1e2;
const int inf=0x3f3f3f3f;

int u[maxm],v[maxm];
int n,m;

struct LCT {
    int ch[maxn][2],fa[maxn],rev[maxn];
    lli su[maxn],len[maxn];
    struct Node {
        int h,id;
        friend bool operator < (const Node &a,const Node &b) {
            return a.h < b.h;
        }
    }ns[maxn],mi[maxn];

    inline void maintain(int pos) {
        su[pos] = su[ch[pos][0]] + su[ch[pos][1]] + len[pos];
        mi[pos] = min( ns[pos] , min( mi[ch[pos][0]] , mi[ch[pos][1] ] ) );
    }
    inline void apply(int pos) {
        if( !pos ) return;
        swap(ch[pos][0],ch[pos][1]) , rev[pos] ^= 1;
    }
    inline void push(int pos) {
        if( rev[pos] ) apply(ch[pos][0]) , apply(ch[pos][1]) , rev[pos] = 0;
    }
    inline bool isroot(int pos) {
        return pos != ch[fa[pos]][0] && pos != ch[fa[pos]][1];
    }
    inline int gid(int pos) {
        return pos == ch[fa[pos]][1];
    }
    inline void rotate(int x) {
        const int f = fa[x] , id = gid(x);
        fa[x] = fa[f];
        if( !isroot(f) ) ch[fa[f]][gid(f)] = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        ch[x][id^1] = f , fa[f] = x;
        maintain(f) , maintain(x);
    }
    inline void pushchain(int pos) {
        if( !isroot(pos) ) pushchain(fa[pos]);
        push(pos);
    }
    inline void splay(int x) {
        pushchain(x);
        while( !isroot(x) ) {
            if( !isroot(fa[x]) ) rotate(gid(x)==gid(fa[x])?fa[x]:x);
            rotate(x);
        }
    }
    inline void access(int x) {
        int t = 0;
        while(x) {
            splay(x) , ch[x][1] = t , maintain(x);
            t = x , x = fa[x];
        }
    }
    inline void makeroot(int x) {
        access(x) , splay(x) , apply(x);
    }
    inline void link(int x,int y) {
        makeroot(x) , fa[x] = y;
    }
    inline void cut(int x,int y) {
        makeroot(x) , access(y) , splay(y);
        ch[y][0] = fa[x] = 0 , maintain(y);
    }
    inline void update(int x,int ll) {
        splay(x) , len[x] = ll , maintain(x);
    }
    inline lli query_su(int x,int y) {
        makeroot(x) , access(y) , splay(y);
        return su[y];
    }
    inline Node query_mi(int x,int y) {
        makeroot(x) , access(y) , splay(y);
        return mi[y];
    }
    inline void init() {
        for(int i=0;i<=n;i++) mi[i] = ns[i] = (Node){inf,0};
    }
    inline void ins(int pos,int id,int h,int l) {
        ns[pos] = mi[pos] = (Node){h,id} , su[pos] = len[pos] = l;
    }
}lct;
typedef LCT::Node Node;

struct UnionFindSet {
    int fa[maxt];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline bool merge(int x,int y) {
        return ( x = findfa(x) ) == ( y = findfa(y) ) ? 0 : fa[x] = y;
    }
    inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

inline int cov(int t) {
    return t + n;
}

int main() {
    static char o[10];
    scanf("%d%d",&n,&m) , lct.init() , ufs.init();
    for(int i=1,id,uu,vv,t,l;i<=m;i++) {
        scanf("%s",o);
        if( *o == 'f' ) {
            scanf("%d",&id) , ++id , scanf("%d%d%d%d",u+id,v+id,&t,&l) , lct.ins(cov(id),id,t,l) , ++u[id] , ++v[id];
            if( ufs.merge(u[id],v[id]) ) lct.link(u[id],cov(id)) , lct.link(v[id],cov(id));
            else {
                Node nd = lct.query_mi(u[id],v[id]);
                if( t < nd.h ) continue;
                const int mi = nd.id;
                lct.cut(u[mi],cov(mi)) , lct.cut(v[mi],cov(mi)) , lct.link(u[id],cov(id)) , lct.link(v[id],cov(id));
            }
        } else if( *o == 'm' ) {
            scanf("%d%d",&uu,&vv) , ++uu , ++vv;
            if( ufs.findfa(uu) != ufs.findfa(vv) ) puts("-1");
            else printf("%lld\n",lct.query_su(uu,vv));
        }
        else if( *o == 'c' ) scanf("%d%d",&id,&t) , lct.update(cov(++id),t);
    }
    return 0;
}
