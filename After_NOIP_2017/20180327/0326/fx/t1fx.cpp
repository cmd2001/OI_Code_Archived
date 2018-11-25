#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cerr
using namespace std;
const int maxn=4e5+1e2;

char in[maxn>>1];
int li,ans=1;

struct PersistentSegmentTree {
    static const int maxe = maxn * 25;
    int siz[maxe],lson[maxe],rson[maxe],cnt;
    
    inline void insert(int &pos,int l,int r,const int &tar) {
        if( !pos ) pos = ++cnt;
        siz[pos] = 1;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) return insert(lson[pos],l,mid,tar);
        else return insert(rson[pos],mid+1,r,tar);
    }
    inline int merge(int p1,int p2,int l,int r) {
        if( ! ( siz[p1] && siz[p2] ) ) return siz[p1] ? p1 : p2;
        int ret = ++cnt; siz[ret] = siz[p1] + siz[p2];
        if( l == r ) return ret;
        const int mid = ( l + r ) >> 1;
        lson[ret] = merge(lson[p1],lson[p2],l,mid);
        rson[ret] = merge(rson[p1],rson[p2],mid+1,r);
        return ret;
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr) {
        if( !pos ) return 0;
        if( ll <= l && r <= rr ) return siz[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson[pos],l,mid,ll,rr);
        if( ll > mid ) return query(rson[pos],mid+1,r,ll,rr);
        return query(lson[pos],l,mid,ll,rr) + query(rson[pos],mid+1,r,ll,rr);
    }
}tree;

namespace SAM {
    int ch[maxn][26],fa[maxn],len[maxn],deg[maxn],last,root,cnt;
    int rit[maxn],pos[maxn],roots[maxn],bst[maxn],f[maxn];
    int seq[maxn],qlen;
    
    inline int NewNode(int li) {
        len[++cnt] = li;
        return cnt;
    }
    inline void extend(int x,int at) {
        int p = last;
        int np = NewNode(len[p]+1); rit[np] = pos[np] = at;
        while( p && !ch[p][x] ) ch[p][x] = np , p = fa[p];
        if( !p ) fa[np] = root;
        else {
            int q = ch[p][x];
            if( len[q] == len[p] + 1 ) fa[np] = q;
            else {
                int nq = NewNode(len[p]+1);
                memcpy(ch[nq],ch[q],sizeof(ch[q])) , fa[nq] = fa[q] , pos[nq] = pos[q];
                fa[np] = fa[q] = nq;
                while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
            }
        }
        last = np;
    }
    inline void build() {
        last = root = NewNode(0);
        for(int i=1;i<=li;i++) extend(in[i]-'a',i);
    }
    inline void topo() {
        for(int i=1;i<=cnt;i++) if( fa[i] ) ++deg[fa[i]];
        queue<int> q;
        for(int i=1;i<=cnt;i++) if( !deg[i] ) q.push(i);
        while( q.size() ) {
            const int pos = q.front(); q.pop() , seq[++qlen] = pos;
            if( pos == root ) continue;
            if( rit[pos] ) {
                int t = 0;
                tree.insert(t,1,li,rit[pos]);
                roots[pos] = tree.merge(roots[pos],t,1,li);
            }
            roots[fa[pos]] = tree.merge(roots[fa[pos]],roots[pos],1,li);
            if( !--deg[fa[pos]] ) q.push(fa[pos]);
        }
        reverse(seq+1,seq+1+qlen);
    }
    inline void getans() {
        f[root] = 1 , bst[root] = root;
        for(int i=2;i<=qlen;i++) {
            const int now = seq[i] , milen = len[fa[now]] + 1;
            if( fa[now] == root ) {
                f[now] = 1 , bst[now] = now;
            } else {
                bst[now] = bst[fa[now]] , f[now] = f[bst[now]];
                const int ql = pos[now] - len[now] + len[bst[now]];
                const int qr = pos[now] - milen + len[bst[now]];
                if( tree.query(roots[bst[now]],1,li,ql,qr) ) f[now]++ , bst[now] = now;
            }
            ans = max( ans , f[now] );
        }
    }
}

int main() {
    scanf("%s",in+1) , li = strlen(in+1);
    SAM::build() , SAM::topo();
    SAM::getans();
    printf("%d\n",ans);
    return 0;
}