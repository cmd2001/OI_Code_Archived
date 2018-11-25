#include<bits/stdc++.h>
#define debug cout
#define int long long
using namespace std;
const int maxn=1e5+1e2;

int n;

int iw[maxn],ib[maxn];

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int fa[maxn],siz[maxn],dep[maxn],son[maxn],top[maxn],dfn[maxn],rit[maxn];

inline void coredge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}
inline void pre(int pos) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] ) {
        dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos , pre(t[at]) , siz[pos] += siz[t[at]];
        if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
    }
}
inline void dfs(int pos) {
    static int dd;
    dfn[pos] = ++dd , top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    if( son[pos] ) dfs(son[pos]);
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa[pos] && t[at] != son[pos] ) dfs(t[at]);
    rit[pos] = dd;
}

inline int query_seg(int l,int r,int ll,int rr) {
    int ret = 0;
    for(int i=l;i<=r;i++) if( ll <= iw[i] && iw[i] <= rr ) ret = max( ret , ib[i] );
    return ret;
}
inline int query_chain(int x,int y,int ll,int rr) {
    int ret = 0;
    while( top[x] != top[y] ) {
        if( dep[top[x]] < dep[top[y]] ) swap(x,y);
        ret = max( ret , query_seg(dfn[top[x]],dfn[x],ll,rr) ) , x = fa[top[x]];
    }
    ret = max( ret , query_seg(min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),ll,rr) );
    return ret;
}

inline void apply_subtree_w(int pos,int w) {
    for(int i=dfn[pos];i<=rit[pos];i++) iw[i] = w;
}
inline void apply_subtree_b(int pos,int b) {
    for(int i=dfn[pos];i<=rit[pos];i++) ib[i] = b;
}

int srt[maxn<<2],len;
int o[maxn],ox[maxn],oy[maxn],oll[maxn],orr[maxn];

inline int gid(int x) {
    return lower_bound(srt+1,srt+1+len,x) - srt;
}

signed main() {
    static int m;
    static char ooo[50];
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b);
    for(int i=1;i<=m;i++) {
        scanf("%s%d%d",ooo+1,ox+i,oy+i);
        if( ooo[1] == 'C' ) {
            if( ooo[7] == 'W' ) o[i] = 1 , srt[++len] = oy[i];
            else o[i] = 2;
        } else o[i] = 3 , scanf("%d%d",oll+i,orr+i) , srt[++len] = oll[i] , srt[++len] = orr[i]; 
    }
    //debug<<"all readed"<<endl;
    sort(srt+1,srt+1+len) , len = unique(srt+1,srt+1+len) - srt - 1;
    for(int i=1;i<=m;i++) {
        if( o[i] == 1 ) oy[i] = gid(oy[i]);
        else if( o[i] == 3 ) oll[i] = gid(oll[i]) , orr[i] = gid(orr[i]);
    }
    //debug<<"sorted"<<endl;
    pre(1) , dfs(1);
    //debug<<"inited"<<endl;
    for(int i=1;i<=m;i++) {
        if( o[i] == 1 ) apply_subtree_w(ox[i],oy[i]);
        else if( o[i] == 2 ) apply_subtree_b(ox[i],oy[i]);
        else printf("%d\n",query_chain(ox[i],oy[i],oll[i],orr[i]));
    }
    return 0;
}
