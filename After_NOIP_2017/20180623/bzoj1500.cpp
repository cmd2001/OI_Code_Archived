#include<cstdio>
#include<algorithm>
#include<cctype>
using std::max;
const int maxn=5e5+1e2;
const int inf=0x3f3f3f3f;

struct pii {int l,r;};
inline pii mp(const int &x,const int &y) { return (pii){x,y}; }

int root;

struct RotatelessTreap {
    int lson[maxn],rson[maxn],siz[maxn],dat[maxn],mxl[maxn],mxr[maxn],mx[maxn],su[maxn],fix[maxn];
    int lazy[maxn],rev[maxn];

    // ram pool .
    int stk[maxn],top;
    inline void pushNode(int t) { stk[++top] = t; }
    inline int newNode() { return stk[top--]; }

    RotatelessTreap() {
        for(int i=1;i<maxn;i++) pushNode(i) , fix[i] = i;
        std::random_shuffle(fix+1,fix+maxn);
    }
    inline void maintain(int pos) {
        siz[pos] = siz[lson[pos]] + 1 + siz[rson[pos]] , su[pos] = mx[pos] = mxl[pos] = mxr[pos] = dat[pos];
        if( lson[pos] ) {
            mx[pos] = max( mx[pos] , max( mx[lson[pos]] , mxr[lson[pos]] + mxl[pos] ) );
            mxl[pos] = max( mxl[lson[pos]] , su[lson[pos]] + mxl[pos] );
            mxr[pos] = max( mxr[pos] , mxr[lson[pos]] + su[pos] ) , su[pos] += su[lson[pos]];
        }
        if( rson[pos] ) {
            mx[pos] = max( mx[pos] , max( mx[rson[pos]] , mxr[pos] + mxl[rson[pos]] ) );
            mxr[pos] = max( mxr[rson[pos]] , mxr[pos] + su[rson[pos]] );
            mxl[pos] = max( mxl[pos] , su[pos] + mxl[rson[pos]] ) , su[pos] += su[rson[pos]];
        }
    }
    inline void apply_rev(int pos) {
        if( !pos ) return;
        rev[pos] ^= 1 , std::swap(lson[pos],rson[pos]) , std::swap(mxl[pos],mxr[pos]);
    }
    inline void apply_fil(int pos,int x) {
        if( !pos ) return;
        dat[pos] = lazy[pos] = x , su[pos] = x * siz[pos];
        if( x >= 0 ) mxl[pos] = mxr[pos] = mx[pos] = x * siz[pos];
        else mxl[pos] = mxr[pos] = mx[pos] = x;
    }
    inline void push(int pos) {
        if( rev[pos] ) apply_rev(lson[pos]) , apply_rev(rson[pos]) , rev[pos] = 0;
        if( lazy[pos] != inf ) apply_fil(lson[pos],lazy[pos]) , apply_fil(rson[pos],lazy[pos]) , lazy[pos] = inf;
    }
    inline pii split(int pos,int ts) { // left siz is ts .
        if( !pos ) return mp(0,0);
        push(pos);
        if( ts <= siz[lson[pos]] ) { // split left .
            pii spl = split(lson[pos],ts);
            lson[pos] = spl.r , maintain(pos);
            return mp(spl.l,pos);
        } else {
            pii spr = split(rson[pos],ts-siz[lson[pos]]-1);
            rson[pos] = spr.l , maintain(pos);
            return mp(pos,spr.r);
        }
    }
    inline int merge(int x,int y) { // assert x is left and y is right .
        if( !x || !y ) return x | y;
        if( fix[x] > fix[y] ) { // great root heap .
            push(x) , rson[x] = merge(rson[x],y) , maintain(x);
            return x;
        } else {
            push(y) , lson[y] = merge(x,lson[y]) , maintain(y);
            return y;
        }
    }
    inline void recycle(int pos) {
        if(lson[pos]) recycle(lson[pos]);
        if(rson[pos]) recycle(rson[pos]);
        pushNode(pos);
    }
    inline int initNode(int x) {
        int ret = newNode();
        lson[ret] = rson[ret] = rev[ret] = 0 , lazy[ret] = inf;
        su[ret] = mxl[ret] = mxr[ret] = mx[ret] = dat[ret] = x , siz[ret] = 1;
        return ret;
    }
}treap;

int in[maxn],len,tar;

inline int build() {
    static int stk[maxn],top;
    for(int i=1;i<=len;i++) {
        int x = treap.initNode(in[i]) , last = 0;
        while( top && treap.fix[stk[top]] < treap.fix[x] ) treap.maintain(stk[top]) , last = stk[top--];
        if( top ) treap.rson[stk[top]] = x;
        treap.lson[x] = last , stk[++top] = x;
    }
    while( top ) treap.maintain(stk[top--]);
    return stk[1];
}
inline void insert_segment(int* in,int len,int tar) {
    int nrt = build();
    pii sp = treap.split(root,tar);
    root = treap.merge(sp.l,treap.merge(nrt,sp.r));
}
inline void remove_segment(int l,int len) {
    pii spl = treap.split(root,l-1) , spr = treap.split(spl.r,len);
    root = treap.merge(spl.l,spr.r) , treap.recycle(spr.l);
}
inline void update_fil(int l,int len,int x) {
    pii spl = treap.split(root,l-1) , spr = treap.split(spl.r,len);
    treap.apply_fil(spr.l,x) , root = treap.merge(spl.l,treap.merge(spr.l,spr.r));
}
inline void update_rev(int l,int len) {
    pii spl = treap.split(root,l-1) , spr = treap.split(spl.r,len);
    treap.apply_rev(spr.l) , root = treap.merge(spl.l,treap.merge(spr.l,spr.r));
}
inline int query_sum(int l,int len) {
    if( !len ) return 0;
    pii spl = treap.split(root,l-1) , spr = treap.split(spl.r,len);
    const int ret = treap.su[spr.l]; root = treap.merge(spl.l,treap.merge(spr.l,spr.r));
    return ret;
}
inline int query_mx() {
    return treap.mx[root];
}


inline char nextchar() {
    static const int BS = 1 << 22;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? ' ' : *st++;
}
inline int getint() {
    int ret = 0 , fix = 1 , ch;
    while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret * fix;
}
inline void getstr(char* s) {
    char ch;
    while( isspace(ch=nextchar()) ) ;
    do *s++ = ch; while( !isspace(ch=nextchar()) );
}

int main() {
    static int m;
    static char o[25];
    len = getint() , m = getint();
    for(int i=1;i<=len;i++) in[i] = getint();
    insert_segment(in,len,0);
    for(int i=1;i<=m;i++) {
        getstr(o);
        if( *o == 'M' && o[2] == 'X' ) printf("%d\n",query_mx());
        else {
            tar = getint() , len = getint();
            if( *o == 'I' ) {
                for(int i=1;i<=len;i++) in[i] = getint();
                insert_segment(in,len,tar);
            } else if( *o == 'D' ) remove_segment(tar,len);
            else if( *o == 'M' ) update_fil(tar,len,getint());
            else if( *o == 'R' ) update_rev(tar,len);
            else if( *o == 'G' ) printf("%d\n",query_sum(tar,len));
        }
    }
    return 0;
}
