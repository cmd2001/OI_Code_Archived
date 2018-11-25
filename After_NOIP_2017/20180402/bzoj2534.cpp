#include<cstdio>
#include<cstring>
#include<map>
#include<queue>
using namespace std;
const int maxn=1e5+1e2,maxl=18;

char in[maxn>>1];
int li,lim;
int seq[maxn>>1],seqlen;
long long ans;

struct PersistentSegmentTree {
    int lson[maxn*maxl<<1],rson[maxn*maxl<<1],siz[maxn*maxl<<1],cnt;
    inline void insert(int &pos,int l,int r,int tar) {
        if( !pos ) pos = ++cnt; siz[pos] = 1;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],l,mid,tar);
        else insert(rson[pos],mid+1,r,tar);
    }
    inline int merge(int p1,int p2,int l,int r) {
        if( ! ( siz[p1] && siz[p2] ) ) return siz[p1] ? p1 : p2;
        int ret = ++cnt; siz[ret] = siz[p1] + siz[p2];
        if( l == r ) return ret;
        const int mid = ( l + r ) >> 1;
        lson[ret] = merge(lson[p1],lson[p2],l,mid) ,
        rson[ret] = merge(rson[p1],rson[p2],mid+1,r) ;
        return ret;
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr) {
        if( !pos ) return 0;
        if( ll <= l && r <= rr ) return siz[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson[pos],l,mid,ll,rr);
        else if( ll > mid ) return query(rson[pos],mid+1,r,ll,rr);
        return query(lson[pos],l,mid,ll,rr) + query(rson[pos],mid+1,r,ll,rr);
    }
    inline void dfs(int pos,int l,int r) {
        if( !pos ) return;
        if( l == r ) return void(seq[++seqlen]=l);
        const int mid = ( l + r ) >> 1;
        dfs(lson[pos],l,mid) , dfs(rson[pos],mid+1,r);
    }
    inline int getsiz(int pos) {
        return siz[pos];
    }
}segt;

namespace SAM {
    int fa[maxn],len[maxn],deg[maxn],last,root,cnt;
    int rit[maxn],roots[maxn];
    map<int,int> ch[maxn];
    inline int NewNode(int ll) {
        len[++cnt] = ll;
        return cnt;
    }
    inline int extend(int x,int rr) {
        int p = last;
        int np = NewNode(len[p]+1); rit[np] = rr;
        while( ch[p].find(x) == ch[p].end() ) ch[p][x] = np , p = fa[p];
        if( !p ) fa[np] = root;
        else {
            int q = ch[p][x];
            if( len[q] == len[p] + 1 ) fa[np] = q;
            else {
                int nq = NewNode(len[p]+1);
                ch[nq] = ch[q] , fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
            }
        }
        return last = np;
    }
    inline int query(int root,int i,int samelen) {
        if( samelen < 1 ) return 0;
        int ret = segt.query(root,1,li,i+lim+1,i+lim+samelen);
        if( i - lim - 1 > 0 ) ret += segt.query(root,1,li,i-lim-samelen,i-lim-1);
        return ret;
    }
    inline void topo() {
        for(int i=1;i<=cnt;i++) if( fa[i] ) ++deg[fa[i]];
        queue<int> q;
        for(int i=1;i<=cnt;i++) if( !deg[i] ) q.push(i);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            if( pos == root ) continue;
            if( rit[pos] ) {
                ans += query(roots[pos],rit[pos],len[pos]);
                int t = 0; segt.insert(t,1,li,rit[pos]);
                roots[pos] = segt.merge(roots[pos],t,1,li);
            }
            if( segt.getsiz(roots[fa[pos]]) < segt.getsiz(roots[pos]) ) // We won't use roots[pos] again .
                swap(roots[fa[pos]],roots[pos]);
            seqlen = 0 , segt.dfs(roots[pos],1,li);
            for(int i=1;i<=seqlen;i++) ans += query(roots[fa[pos]],seq[i],len[fa[pos]]);
            roots[fa[pos]] = segt.merge(roots[fa[pos]],roots[pos],1,li);
            if( !--deg[fa[pos]] ) q.push(fa[pos]);
        }
    }
}

int main() {
    scanf("%d%s",&lim,in+1) , li = strlen(in+1);
    SAM::last = SAM::root = SAM::NewNode(0);
    for(int i=1;i<=li;i++) SAM::extend(in[i],i);
    SAM::topo();
    printf("%lld\n",ans);
    return 0;
}
