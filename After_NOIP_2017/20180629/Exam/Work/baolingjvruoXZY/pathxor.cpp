#pragma GCC optimize("Ofast","no-stack-protector")
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<utility>
#include<cctype>
#include<vector>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxe=5e6+1e2,maxl=20;
const int inf=0x3f3f3f3f;

int ans[maxn],n;
namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    int dep[maxn],lazy[maxn][maxl],anc[maxn][maxl];
    inline void coredge(int from,int to) {
        static int cnt;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void pre(int pos) {
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != *anc[pos] ) dep[t[at]] = dep[*anc[t[at]]=pos] + 1 , pre(t[at]);
    }
    inline void init() {
        for(int j=1;j<maxl;j++) for(int i=1;i<=n;i++) anc[i][j] = anc[anc[i][j-1]][j-1];
    }
    inline int lca(int x,int y) {
        if( dep[x] < dep[y] ) swap(x,y);
        for(int i=maxl-1;~i;i--) if( dep[x] - ( 1 << i ) >= dep[y] ) x = anc[x][i];
        if( x == y ) return x;
        for(int i=maxl-1;~i;i--) if( anc[x][i] != anc[y][i] ) x = anc[x][i] , y = anc[y][i];
        return *anc[x];
    }
    inline int getlen(int s,int f) {
        return dep[s] - dep[f] + 1;
    }
    inline void markchain(int x,int dep,int v) { // mark dep points .
        for(int i=maxl-1;~i;i--) if( dep - ( 1 << i ) >= 0 ) {
            lazy[x][i] = max( lazy[x][i] , v ) , dep -= 1 << i , x = anc[x][i];
        }
    }
    inline void pushall() {
        for(int j=maxl-1;j;j--) for(int i=1;i<=n;i++) {
            lazy[i][j-1] = max( lazy[i][j-1] , lazy[i][j] ) ,
            lazy[anc[i][j-1]][j-1] = max( lazy[anc[i][j-1]][j-1] , lazy[i][j] );
        }
        for(int i=1;i<=n;i++) ans[i] = *lazy[i];
    }
}

typedef pair<int,int> pii;
inline pii mp(const int &x,const int &y) { return (pii){x,y}; }

int root;
struct Trie { // dep from 30 downto -1 becaus 2^30 > 1e9 so it can't have bit 2^31 .
    int ch[maxe][2],id[maxe],cnt; // identity of leaf node .
    inline void insert(int &pos,int dep,const int &val,const int &iid) {
        if( !pos ) pos = ++cnt;
        if( !~dep ) return void(id[pos] = iid);
        int bit = ( val >> dep ) & 1; insert(ch[pos][bit],dep-1,val,iid);
    }
    inline pii query(int pos,int dep,const int &val) {
        if( !~dep ) return mp(0,id[pos]);
        int bit = ( ( val >> dep ) & 1 ) ^ 1;
        if( ch[pos][bit] ) {
            pii qs = query(ch[pos][bit],dep-1,val);
            return mp(qs.first|(1<<dep),qs.second);
        } else return query(ch[pos][bit^1],dep-1,val); // pos must have at least one son .
    }
    inline void reset() {
        ++cnt , memset(ch,0,sizeof(ch[0])*cnt) , memset(id,0,sizeof(id[0])*cnt) , cnt = 0 , root = 0;
    }
}trie;

namespace TDAC {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
    int siz[maxn],mxs[maxn],ban[maxn],vs[maxn],is[maxn],cnt;
    inline void coredge(int from,int to,int len) {
        static int cnt;
        t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b,int l) {
        coredge(a,b,l) , coredge(b,a,l);
    }
    inline void getroot(int pos,int fa,const int &fs,int &rt) {
        siz[pos] = 1 , mxs[pos] = 0;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) getroot(t[at],pos,fs,rt) , siz[pos] += siz[t[at]] , mxs[pos] = max( mxs[pos] , siz[t[at]] );
        if( ( mxs[pos] = max( mxs[pos] , fs - siz[pos]) ) <= mxs[rt] ) rt = pos; // *mxs == inf .
    }
    inline void dfs(int pos,int fa,int su) {
        vs[++cnt] = su , is[cnt] = pos;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) dfs(t[at],pos,su^l[at]);
    }
    inline void solve(int pos,int fs) {
        if( fs == 1 ) return;
        int rt = 0; *mxs = inf , getroot(pos,-1,fs,rt) , ban[rt] = 1;

        static vector<int> sons,lens; sons.clear() , lens.clear();
        for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) sons.push_back(t[at]) , lens.push_back(l[at]);

        trie.reset() , trie.insert(root,30,0,rt);
        for(unsigned i=0;i<sons.size();i++) {
            cnt = 0 , dfs(sons[i],rt,lens[i]);
            for(int i=1;i<=cnt;i++) {
                pii qry = trie.query(root,30,vs[i]); int lca = Tree::lca(is[i],qry.second);
                Tree::markchain(is[i],Tree::getlen(is[i],lca),qry.first) , Tree::markchain(qry.second,Tree::getlen(qry.second,lca),qry.first);
            }
            for(int i=1;i<=cnt;i++) trie.insert(root,30,vs[i],is[i]);
        }

        reverse(sons.begin(),sons.end()) , reverse(lens.begin(),lens.end());
        
        trie.reset() , trie.insert(root,30,0,rt);
        for(unsigned i=0;i<sons.size();i++) {
            cnt = 0 , dfs(sons[i],rt,lens[i]);
            for(int i=1;i<=cnt;i++) {
                pii qry = trie.query(root,30,vs[i]); int lca = Tree::lca(is[i],qry.second);
                Tree::markchain(is[i],Tree::getlen(is[i],lca),qry.first) , Tree::markchain(qry.second,Tree::getlen(qry.second,lca),qry.first);
            }
            for(int i=1;i<=cnt;i++) trie.insert(root,30,vs[i],is[i]);
        }

        for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) solve(t[at],siz[t[at]]<siz[rt]?siz[t[at]]:fs-siz[rt]);
    }
}

namespace IO {
    inline char nextchar() {
        static const int BS = 1 << 21;
        static char buf[BS],*st,*ed;
        if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
        return st == ed ? -1 : *st++;
    }
    inline int getint() {
        int ret = 0; char ch;
        while( !isdigit(ch=nextchar()) ) ;
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
}
using IO::getint;

int main() {
    freopen("pathxor.in","r",stdin);
    freopen("pathxor.out","w",stdout);
    n = getint();
    for(int i=1,a,b,l;i<n;i++) a = getint() , b = getint() , l = getint() , Tree::addedge(a,b) , TDAC::addedge(a,b,l);
    Tree::pre(1) , Tree::init() , TDAC::solve(1,n) , Tree::pushall();
    for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
    fclose(stdout);
    return 0;
}
