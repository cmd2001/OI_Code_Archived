#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=3e5+1e2,maxl=19;

int siz[maxn],dep[maxn],id[maxn],anc[maxn][maxl],n;

namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    inline void addedge(int from,int to) {
        static int cnt = 1;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void dfs(int pos,int fa) {
        static int dd;
        siz[pos] = 1 , *anc[pos] = fa , id[pos] = ++dd;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) dep[t[at]] = dep[pos] + 1 , dfs(t[at],pos) , siz[pos] += siz[t[at]];
    }
    inline void pre() {
        for(int j=1;j<maxl;j++) for(int i=1;i<=n;i++) anc[i][j] = anc[anc[i][j-1]][j-1];
    }
}

namespace VitrualTree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    int in[maxn],srt[maxn],stk[maxn],bel[maxn],rem[maxn],ans[maxn],seq[maxn],top,cnt,m,dfn;
    inline void addedge(int from,int to) {
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline int lca(int x,int y) {
        if( dep[x] < dep[y] ) std::swap(x,y);
        for(int i=maxl-1;~i;i--) if( dep[x] - ( 1 << i ) >= dep[y] ) x = anc[x][i];
        if( x == y ) return x;
        for(int i=maxl-1;~i;i--) if( anc[x][i] != anc[y][i] ) x = anc[x][i] , y = anc[y][i];
        return *anc[x];
    }
    inline int findnst(int x,int tfa) {
        for(int i=maxl-1;~i;i--) if( dep[x] - ( 1 << i ) > dep[tfa] ) x = anc[x][i];
        return x;
    }
    inline int dis(int x,int y) {
        return dep[x] + dep[y] - ( dep[lca(x,y)] << 1 );
    }
    inline bool cmp(const int &x,const int &y) {
        return id[x] < id[y];
    }
    inline void dfs1(int pos) {
        seq[++dfn] = pos , rem[pos] = siz[pos];
        for(int at=s[pos],dl,dt;at;at=nxt[at]) {
            dfs1(t[at]) , dl = dis(bel[pos],pos) , dt = dis(bel[t[at]],pos);
            if( !bel[pos] || dl > dt || ( dl == dt && bel[pos] > bel[t[at]] ) ) bel[pos] = bel[t[at]];
        }
    }
    inline void dfs2(int pos) {
        for(int at=s[pos],dl,dt;at;at=nxt[at]) {
            dl = dis(bel[pos],t[at]) , dt = dis(bel[t[at]],t[at]);
            if( !bel[t[at]] || dt > dl || ( dt == dl && bel[t[at]] > bel[pos] ) ) bel[t[at]] = bel[pos];
            dfs2(t[at]);
        }
    }
    inline void solve(int fa,int son) {
        int nst = findnst(son,fa) , mid = son;
        rem[fa] -= siz[nst];
        if( bel[fa] == bel[son] ) return void( ans[bel[fa]] += siz[nst] - siz[son] );
        for(int i=maxl-1;~i;i--) {
            int nxt = anc[mid][i];
            if( dep[nxt] < dep[fa] ) continue;
            int t1 = dis(nxt,bel[fa]) , t2 = dis(nxt,bel[son]);
            if( t1 > t2 || ( t1 == t2 && bel[fa] > bel[son] ) ) mid = nxt;
        }
        ans[bel[fa]] += siz[nst] - siz[mid] , ans[bel[son]] += siz[mid] - siz[son];
    }
    inline void solvecase() {
        scanf("%d",&m);
        for(int i=1;i<=m;i++) scanf("%d",in+i) , srt[i] = in[i] , bel[in[i]] = in[i];
        std::sort(srt+1,srt+1+m,cmp);
        if( bel[1] != 1 ) stk[++top] = 1; // insert point 1 by force .
        for(int i=1,l;i<=m;i++) {
            const int p = srt[i];
            while( top ) {
                l = lca(stk[top],p);
                if( top > 1 && dep[stk[top-1]] > dep[l] ) addedge(stk[top-1],stk[top]) , --top;
                else if( dep[stk[top]] > dep[l] ) {
                    addedge(l,stk[top--]);
                    break;
                } else break;
            }
            if( stk[top] != l ) stk[++top] = l;
            stk[++top] = p;
        }
        while( top > 1 ) addedge(stk[top-1],stk[top]) , --top;
        dfs1(1) , dfs2(1);
        for(int i=1;i<=dfn;i++) for(int at=s[seq[i]];at;at=nxt[at]) solve(seq[i],t[at]);
        for(int i=1;i<=dfn;i++) ans[bel[seq[i]]] += rem[seq[i]];
        for(int i=1;i<=m;i++) printf("%d%c",ans[in[i]],i!=m?' ':'\n');
        for(int i=1;i<=dfn;i++) s[seq[i]] = bel[seq[i]] = rem[seq[i]] = ans[seq[i]] = 0;
        top = cnt = m = dfn = 0;
    }
}

int main() {
    static int m;
    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , Tree::addedge(a,b) , Tree::addedge(b,a);
    dep[1] = 1 , Tree::dfs(1,-1) , Tree::pre();
    scanf("%d",&m);
    while(m--) VitrualTree::solvecase();
    return 0;
}
