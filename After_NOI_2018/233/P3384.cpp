#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn = 1e5 + 1e2;

int in[maxn],n,mod;

class SegmentTree {
private:
    int sum[maxn<<3],lazy[maxn<<3];
    inline int add(const int &x,const int &y) {
        const int ret = x + y;
        return ret >= mod ? ret - mod : ret;
    }
    inline int mul(const int &x,const int &y) { // ret may never overflow.
        return (lli) x * y % mod;
    }
    inline void adde(int &dst,const int &x) {
        if((dst += x) >= mod) dst -= mod;
    }
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void apply(int pos,const int &l,const int &r,const int &x) {
        adde(sum[pos],mul(r-l+1,x)), adde(lazy[pos],x);
    }
    inline void maintain(int pos) {
        sum[pos] = add(sum[lson(pos)],sum[rson(pos)]);
    }
    inline void push(int pos,const int &l,const int &mid,const int &r) {
        if(lazy[pos]) apply(lson(pos),l,mid,lazy[pos]), apply(rson(pos),mid+1,r,lazy[pos]), lazy[pos] = 0;
    }
public:
    inline void update(int pos,int l,int r,const int &ll,const int &rr,const int &x) {
        if(ll <= l && r <= rr) return apply(pos,l,r,x);
        const int mid = (l + r) >> 1; push(pos,l,mid,r);
        if(ll <= mid) update(lson(pos),l,mid,ll,rr,x);
        if(mid < rr) update(rson(pos),mid+1,r,ll,rr,x);
        maintain(pos);
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr) {
        if(ll <= l && r <= rr) return sum[pos];
        const int mid = (l + r) >> 1; push(pos,l,mid,r);
        int ret = 0;
        if(ll <= mid) adde(ret,query(lson(pos),l,mid,ll,rr));
        if(mid < rr) adde(ret,query(rson(pos),mid+1,r,ll,rr));
        return ret;
    }
    #undef lson
    #undef rson
}sgt;

class Tree {
private:
    int s[maxn],t[maxn<<1],nxt[maxn<<1],siz[maxn],dep[maxn],fa[maxn],son[maxn],top[maxn],dfn[maxn],rit[maxn];
    inline void coredge(int from,int to) {
        static int cnt;
        t[++cnt] = to, nxt[cnt] = s[from], s[from] = cnt;
    }
    inline void adde(int &dst,const int &x) {
        if((dst += x) >= mod) dst -= mod;
    }
public:
    inline void addedge(int from,int to) {
        coredge(from,to), coredge(to,from);
    }
    inline void pre(int pos) {
        siz[pos] = 1;
        //debug<<"pos = "<<pos<<endl;
        for(int at=s[pos];at;at=nxt[at]) if(t[at] != fa[pos]) {
            fa[t[at]] = pos, dep[t[at]] = dep[pos] + 1, pre(t[at]), siz[pos] += siz[t[at]];
            if(siz[t[at]] > siz[son[pos]]) son[pos] = t[at];
        }
    }
    inline void dfs(int pos) {
        static int dd;
        top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos, dfn[pos] = ++dd;
        if(son[pos]) dfs(son[pos]);
        for(int at=s[pos];at;at=nxt[at]) if(t[at] != fa[pos] && t[at] != son[pos]) dfs(t[at]);
        rit[pos] = dd, sgt.update(1,1,n,dfn[pos],dfn[pos],in[pos]);
    }
    inline void chain_update(int x,int y,const int &v) {
        while(top[x] != top[y]) {
            if(dep[top[x]] < dep[top[y]]) swap(x,y);
            sgt.update(1,1,n,dfn[top[x]],dfn[x],v), x = fa[top[x]];
        }
        if(dfn[x] > dfn[y]) swap(x,y);
        sgt.update(1,1,n,dfn[x],dfn[y],v);
    }
    inline int chain_query(int x,int y) {
        int ret = 0;
        while(top[x] != top[y]) {
            if(dep[top[x]] < dep[top[y]]) swap(x,y);
            adde(ret,sgt.query(1,1,n,dfn[top[x]],dfn[x])), x = fa[top[x]];
        }
        if(dfn[x] > dfn[y]) swap(x,y);
        adde(ret,sgt.query(1,1,n,dfn[x],dfn[y]));
        return ret;
    }
    inline void subtree_update(int pos,const int &x) {
        sgt.update(1,1,n,dfn[pos],rit[pos],x);
    }
    inline int subtree_query(int pos) {
        return sgt.query(1,1,n,dfn[pos],rit[pos]);
    }
}tre;

int main() {
    static int root,m;
    scanf("%d%d%d%d",&n,&m,&root,&mod);
    for(int i=1;i<=n;i++) scanf("%d",in+i), in[i] %= mod;
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b), tre.addedge(a,b);
    tre.pre(root), tre.dfs(root);
    for(int i=1,o,x,y,z;i<=m;i++) {
        scanf("%d",&o);
        if(o == 1) scanf("%d%d%d",&x,&y,&z), tre.chain_update(x,y,z);
        else if(o == 2) scanf("%d%d",&x,&y), printf("%d\n",tre.chain_query(x,y));
        else if(o == 3) scanf("%d%d",&x,&z), tre.subtree_update(x,z);
        else if(o == 4) scanf("%d",&x), printf("%d\n",tre.subtree_query(x));
    }
    return 0;
}

