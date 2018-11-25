#include<cstdio>
#include<algorithm>
const int maxn=1e5+1e2,maxe=4e6+1e2;

int root;
struct Trie {
    int ch[maxe][2],siz[maxe],cnt;
    inline void insert(int &pos,int bit,const int &x) { // bit from 31 downto -1 .
        if( !pos ) { pos = ++cnt; } ++siz[pos];
        if( ~bit ) insert(ch[pos][(x>>bit)&1],bit-1,x);
    }
    inline int query(int pos,int bit,const int &x) {
        if( !~bit ) return 0;
        int ned = ( ( x >> bit ) & 1 ) ^ 1;
        if( siz[ch[pos][ned]] ) return query(ch[pos][ned],bit-1,x) | ( 1 << bit );
        else return query(ch[pos][ned^1],bit-1,x);
    }
    inline void reset() {
        for(int i=0;i<=cnt;i++) ch[i][0] = ch[i][1] = siz[i] = 0;
        cnt = 0;
    }
}trie;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1],cnt;
int dep[maxn],n;

inline void coredge(int from,int to,int len) {
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b,int len) {
    coredge(a,b,len) , coredge(b,a,len);
}
inline void dfs(int pos,int fa) {
    trie.insert(root,31,dep[pos]);
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) dep[t[at]] = dep[pos]^l[at] , dfs(t[at],pos);
}

inline void reset() {
    for(register int i=1;i<=n;i++) s[i] = 0;
    trie.reset() , root = cnt = 0;
}
int main() {
    static int ans;
    while( scanf("%d",&n) == 1 ) {
        reset() , ans = 0;
        for(int i=1,a,b,l;i<n;i++) scanf("%d%d%d",&a,&b,&l) , addedge(a,b,l);
        dfs(1,-1);
        for(int i=1;i<=n;i++) ans = std::max( ans , trie.query(root,31,dep[i]) );
        printf("%d\n",ans);
    }
    return 0;
}
