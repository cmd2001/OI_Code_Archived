#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e5+1e2;

int n;

struct Splay {
    int ch[maxn][2],fa[maxn],dat[maxn],siz[maxn],root,cnt;
    int sum[maxn],rev[maxn],swp[maxn],lmin[maxn],rmin[maxn],lmax[maxn],rmax[maxn];
    
    inline void applyswp(int pos) {
        if( !pos ) return;
        dat[pos] = -dat[pos] , sum[pos] = -sum[pos] , swp[pos] ^= 1;
        int lmi = lmin[pos] , lmx = lmax[pos];
        lmin[pos] = -lmx , lmax[pos] = -lmi;
        int rmi = rmin[pos] , rmx = rmax[pos];
        rmin[pos] = -rmx , rmax[pos] = -rmi;
    }
    inline void applyrev(int pos) {
        if( !pos ) return;
        swap(ch[pos][0],ch[pos][1]) , rev[pos] ^= 1;
        swap(lmin[pos],rmin[pos]) , swap(lmax[pos],rmax[pos]);
    }
    inline void push(int pos) {
        if( swp[pos] ) applyswp(ch[pos][0]) , applyswp(ch[pos][1]) , swp[pos] = 0;
        if( rev[pos] ) applyrev(ch[pos][0]) , applyrev(ch[pos][1]) , rev[pos] = 0;
    }
    inline void upgrade(int pos) {
        lmin[pos] = lmax[pos] = rmin[pos] = rmax[pos] = sum[pos] = dat[pos] , siz[pos] = 1;
        if( ch[pos][0] ) sum[pos] += sum[ch[pos][0]] , siz[pos] += siz[ch[pos][0]];
        if( ch[pos][1] ) sum[pos] += sum[ch[pos][1]] , siz[pos] += siz[ch[pos][1]];
        if( ch[pos][0] && !ch[pos][1] ) {
            lmin[pos] = min( lmin[ch[pos][0]] , sum[ch[pos][0]] + dat[pos] ) ,
            lmax[pos] = max( lmax[ch[pos][0]] , sum[ch[pos][0]] + dat[pos] ) ,
            rmin[pos] = min( rmin[ch[pos][0]] + dat[pos] , dat[pos] ) ,
            rmax[pos] = max( rmax[ch[pos][0]] + dat[pos] , dat[pos] ) ;
        } else if( !ch[pos][0] && ch[pos][1] ) {
            lmin[pos] = min( dat[pos] , dat[pos] + lmin[ch[pos][1]] ) ,
            lmax[pos] = max( dat[pos] , dat[pos] + lmax[ch[pos][1]] ) ,
            rmin[pos] = min( dat[pos] + sum[ch[pos][1]] , rmin[ch[pos][1]] ) ,
            rmax[pos] = max( dat[pos] + sum[ch[pos][1]] , rmax[ch[pos][1]] ) ;
        } else if( ch[pos][0] && ch[pos][1] ) { // first 4 lines is copied code .
            lmin[pos] = min( lmin[ch[pos][0]] , sum[ch[pos][0]] + dat[pos] ) ,
            lmax[pos] = max( lmax[ch[pos][0]] , sum[ch[pos][0]] + dat[pos] ) ,
            rmin[pos] = min( dat[pos] + sum[ch[pos][1]] , rmin[ch[pos][1]] ) ,
            rmax[pos] = max( dat[pos] + sum[ch[pos][1]] , rmax[ch[pos][1]] ) ;
            lmin[pos] = min( lmin[pos] , sum[ch[pos][0]] + dat[pos] + lmin[ch[pos][1]] ) ,
            lmax[pos] = max( lmax[pos] , sum[ch[pos][0]] + dat[pos] + lmax[ch[pos][1]] ) ,
            rmin[pos] = min( rmin[pos] , rmin[ch[pos][0]] + dat[pos] + sum[ch[pos][1]] ) ,
            rmax[pos] = max( rmax[pos] , rmax[ch[pos][0]] + dat[pos] + sum[ch[pos][1]] ) ;
        }
    }
    inline int gid(int pos) {
        return pos == ch[fa[pos]][1];
    }
    inline void rotate(int x) {
        if( fa[fa[x]] ) push(fa[fa[x]]);
        push(fa[x]) , push(x);
        const int f = fa[x] , id = gid(x);
        fa[x] = fa[f];
        if(fa[f]) ch[fa[f]][gid(f)] = x;
        else root = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        ch[x][id^1] = f , fa[f] = x;
        upgrade(f) , upgrade(x);
    }
    inline void splay(int x,int tar) {
        while( fa[x] != tar ) {
            if( fa[fa[x]] != tar ) rotate(fa[x]);
            rotate(x);
        }
    }
    inline int kth(int k) {
        int now = root;
        while(1) {
            push(now);
            if( k == siz[ch[now][0]] + 1 ) return now;
            else if( k <= siz[ch[now][0]] ) now = ch[now][0];
            else k -= siz[ch[now][0]] + 1 , now = ch[now][1];
        }
    }
    inline int getseg(int l,int r) {
        int ret;
        if( l == 1 && r == n ) return root; // full tree .
        else if( l == 1 ) {
            r = kth(r+1) , splay(r,0);
            ret = ch[root][0];
        } else if( r == n ) {
            l = kth(l-1) , splay(l,0);
            ret = ch[root][1];
        } else {
            l = kth(l-1) , r = kth(r+1);
            splay(l,0) , splay(r,l);
            ret = ch[ch[root][1]][0];
        }
        pushchain(ret);
        return ret;
    }
    inline void upchain(int pos) {
        while(pos) push(pos) , upgrade(pos) , pos = fa[pos];
    }
    inline void pushchain(int pos) {
        if( fa[pos] ) pushchain(fa[pos]);
        push(pos);
    }
    inline void modifyswp(int l,int r) { // this swap isn't swap in the problem .
        int s = getseg(l,r);
       applyswp(s) , upchain(s);
    }
    inline void modifyrev(int l,int r) {
        int s = getseg(l,r);
        applyrev(s) , upchain(s);
    }
    inline int query(int l,int r) {
        int s = getseg(l,r);
        int lmx = max( lmax[s] , 0 );
        int rmi = min( rmin[s] , 0 );
        return ( lmx + 1 ) / 2 + ( -rmi + 1 ) / 2;
    }
    inline void init(int pos,int col) {
        siz[pos] = 1 , dat[pos] = col;
    }
    inline void insert(int col) {
        if( !root ) {
            root = ++cnt;
        } else {
            int now = root;
            while( ch[now][1] ) now = ch[now][1];
            ch[now][1] = ++cnt , fa[cnt] = now;
        }
        init(cnt,col) , upchain(cnt);
        if( fa[cnt] ) splay(fa[cnt],0);
    }
}tree;

char in[maxn];

int main() {
    static int m;
    static char o[10];
    scanf("%d%d%s",&n,&m,in+1);
    for(int i=1;i<=n;i++) tree.insert(in[i]==')'?1:-1);
    for(int i=1,o,l,r;i<=m;i++) {
        scanf("%d%d%d",&o,&l,&r);
        if( o == 2 ) tree.modifyrev(l,r);
        else if( o == 1 ) tree.modifyswp(l,r);
        else if( o == 0 ) printf("%d\n",tree.query(l,r));
    }
    return 0;
}

