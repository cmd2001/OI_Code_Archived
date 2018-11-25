#include<cstdio>
#include<algorithm>
#include<cstdlib>
const int maxn=1e5+1e2;

typedef std::pair<int,int> pii;
__inline pii mp(const int &x,const int &y) { return std::make_pair(x,y); }

int seq[maxn],sql;
int stk[maxn],top;

struct Treap {
    int lson[maxn],rson[maxn],lazy[maxn],val[maxn],siz[maxn],fix[maxn],cnt;
    
    inline void init(int n) {
        for(int i=1;i<=n;i++) fix[i] = i;
        std::random_shuffle(fix+1,fix+1+n);
    }
    inline void apply(int pos,int x) {
        if(pos) lazy[pos] += x , val[pos] -= x;
    }
    inline void push(int pos) {
        if( lazy[pos] ) apply(lson[pos],lazy[pos]) , apply(rson[pos],lazy[pos]) , lazy[pos] = 0;
    }
    inline void maintain(int pos) {
        siz[pos] = siz[lson[pos]] + siz[rson[pos]] + 1;
    }

    inline pii split(int pos,int dv) { // left is <= , right is > .
        if( !pos ) return mp(0,0);
        push(pos);
        if(  dv < val[pos] ) {
            pii spl = split(lson[pos],dv);
            lson[pos] = spl.second , maintain(pos);
            return mp(spl.first,pos);
        } else {
            pii spr = split(rson[pos],dv);
            rson[pos] = spr.first , maintain(pos);
            return mp(pos,spr.second);
        }
    }
    inline int merge(int x,int y) {
        if( !x || !y ) return x | y;
        push(x) , push(y);
        if( val[x] > val[y] ) std::swap(x,y);
        if( fix[x] > fix[y] ) { // siz[x] is bigger .
            lson[y] = merge(lson[y],x) , maintain(y);
            return y;
        } else {
            rson[x] = merge(rson[x],y) , maintain(x);
            return x;
        }
    }
    inline void dfs(int pos) {
        if( !pos ) return;
        seq[++sql] = val[pos] , push(pos);
        dfs(lson[pos]) , dfs(rson[pos]);
        lson[pos] = rson[pos] = siz[pos] = 0 , stk[++top] = pos;
    }
    inline int kth(int pos,int k) { // return the kth value .
        if( k == siz[lson[pos]] + 1 ) return val[pos];
        return push(pos) , k <= siz[lson[pos]] ? kth(lson[pos],k) : kth(rson[pos],k-siz[lson[pos]]-1);
    }
    inline void insert(int &root,int x) {
        val[++cnt] = x , siz[cnt] = 1;
        pii sp = split(root,x);
        root = merge(sp.first,cnt) , root = merge(root,sp.second);
    }
    inline void reinsert(int &root,int x) {
        int cur = stk[top--];
        val[cur] = x , siz[cur] = 1;
        pii sp = split(root,x);
        root = merge(sp.first,cur) , root = merge(root,sp.second);
    }
    
}tp;

int main() {
    static int n,m,root,rtl,rtm,rtr;
    scanf("%d%d",&n,&m) , tp.init(n);
    for(int i=1,t;i<=n;i++) scanf("%d",&t) , tp.insert(root,t);
    for(int i=1,o,x;i<=m;i++) {
        scanf("%d%d",&o,&x);
        if( o == 1 ) printf("%d\n",tp.kth(root,x));
        else if( o == 2 ) {
            pii sp = tp.split(root,x);
            rtl = sp.first , sp = tp.split(sp.second,x<<1);
            rtm = sp.first , rtr = sp.second;
            sql = 0 , tp.dfs(rtm) , tp.apply(rtr,x);
            for(int i=1;i<=sql;i++) tp.reinsert(rtl,seq[i]-x);
            root = tp.merge(rtl,rtr);
        }
    }
    return 0;
}
