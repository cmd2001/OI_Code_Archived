#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
const int inf=0x3f3f3f3f;

char in[maxn];
int li;

struct SegmentTree {
    int dat[maxn<<2],lazy[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) ((pos<<1)|1)
    inline void fill(int pos,int x) {
        lazy[pos] = min( lazy[pos] , x );
        dat[pos] = min( dat[pos] , x );
    }
    inline void push(int pos) {
        if( lazy[pos] == inf ) return;
        fill(lson(pos),lazy[pos]) , fill(rson(pos),lazy[pos]) ,
        lazy[pos] = inf;
    }
    inline void update(int pos,int l,int r,const int &ll,const int &rr,const int &x) {
        if( ll <= l && r <= rr ) return fill(pos,x);
        push(pos);
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) update(lson(pos),l,mid,ll,rr,x);
        else if( ll > mid ) update(rson(pos),mid+1,r,ll,rr,x);
        else {
            update(lson(pos),l,mid,ll,rr,x) ,
            update(rson(pos),mid+1,r,ll,rr,x);
        }
    }
    inline int query(int pos,int l,int r,const int &tar) {
        if( l == r ) return dat[pos];
        push(pos);
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) return query(lson(pos),l,mid,tar);
        else return query(rson(pos),mid+1,r,tar);
    }
    SegmentTree() {
        memset(dat,0x3f,sizeof(dat)) , memset(lazy,0x3f,sizeof(lazy));
    }
}st1,st2;

struct SAM {
    int ch[maxn<<1][26],fa[maxn<<1],len[maxn<<1],siz[maxn<<1],rit[maxn<<1],deg[maxn<<1],root,last,cnt;
    inline int NewNode(int ll) {
        len[++cnt] = ll;
        return cnt;
    }
    inline void extend(int x,int r) {
        int p = last , np = NewNode(len[p]+1);
        rit[np] = r , siz[np] = 1;
        while( p && !ch[p][x] ) ch[p][x] = np , p = fa[p];
        if( !p ) fa[np] = root;
        else {
            int q = ch[p][x];
            if( len[q] == len[p] + 1 ) fa[np] = q;
            else {
                int nq = NewNode(len[p]+1);
                memcpy(ch[nq],ch[q],sizeof(ch[q])) , fa[nq] = fa[q];
                fa[q] = fa[np] = nq;
                while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
            }
        }
        last = np;
    }
    inline void topo() {
        for(int i=1;i<=cnt;i++) if( fa[i] ) ++deg[fa[i]];
        queue<int> q;
        for(int i=1;i<=cnt;i++) if( !deg[i] ) q.push(i);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            if( siz[pos] == 1 ) {
                st1.update(1,1,li,rit[pos]-len[pos]+1,rit[pos]-len[fa[pos]],rit[pos]+1);
                st2.update(1,1,li,rit[pos]-len[fa[pos]],rit[pos],len[fa[pos]]+1);
            }
            siz[fa[pos]] += siz[pos];
            if( !--deg[fa[pos]] ) q.push(fa[pos]);
        }
    }
    SAM() {
        last = root = NewNode(0);
    }
}sam;

int main() {
    scanf("%s",in+1) , li = strlen(in+1);
    for(int i=1;i<=li;i++) sam.extend(in[i]-'a',i);
    sam.topo();
    for(int i=1,ans;i<=li;i++) {
        ans = min( st1.query(1,1,li,i) - i , st2.query(1,1,li,i) );
        printf("%d\n",ans);
    }
    return 0;
}

