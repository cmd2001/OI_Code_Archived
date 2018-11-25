#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=5e5+1e2;
 
int n;
 
struct Splay {
    int ch[maxn][2],fa[maxn],col[maxn][2],dat[maxn],sum[maxn],siz[maxn],root,cnt; // sum includes color on sides .
    int rev[maxn],recol[maxn]; // rev >= recol , so you must push recol first before pusing rev .
     
    Splay() {
        memset(recol,-1,sizeof(recol));
    }
    inline void fill(int pos,int cc) {
        if( !pos ) return;
        col[pos][0] = col[pos][1] = dat[pos] = recol[pos] = cc , sum[pos] = 1;
    }
    inline void initfill(int pos,int cc) {
        col[pos][0] = col[pos][1] = dat[pos] = cc , sum[pos] = 1;
    }
    inline void applyrev(int pos) {
        if( !pos ) return;
        swap( ch[pos][0] , ch[pos][1] ) , swap( col[pos][0] , col[pos][1] );
    }
    inline void push(int pos) {
        if( ~recol[pos] ) {
            fill(ch[pos][0],recol[pos]) , fill(ch[pos][1],recol[pos]);
            recol[pos] = -1;
        }
        if( rev[pos] ) {
            rev[ch[pos][0]] ^= 1 , rev[ch[pos][1]] ^= 1;
            applyrev(ch[pos][0]) , applyrev(ch[pos][1]);
            rev[pos] = 0;
        }
    }
    inline void upgrade(int pos) {
        col[pos][0] = col[pos][1] = dat[pos] , sum[pos] = 1 ,
        siz[pos] = 1;
        if( ch[pos][0] ) {
            sum[pos] = sum[pos] + sum[ch[pos][0]] - ( col[ch[pos][0]][1] == col[pos][0] ) , 
            col[pos][0] = col[ch[pos][0]][0] ,
            siz[pos] += siz[ch[pos][0]] ;
        }
        if( ch[pos][1] ) {
            sum[pos] = sum[pos] + sum[ch[pos][1]] - ( col[pos][1] == col[ch[pos][1]][0] ) ,
            col[pos][1] = col[ch[pos][1]][1]  ,
            siz[pos] += siz[ch[pos][1]] ;
        }
    }
    inline int gid(int x) {
        return x == ch[fa[x]][1];
    }
    inline void rotate(int x) {
        push(fa[x]) , push(x);
        const int f = fa[x] , id = gid(x);
        fa[x] = fa[f];
        if( fa[f] ) ch[fa[f]][gid(f)] = x;
        else root = x;
        ch[f][id] = ch[x][id^1];
        if( ch[x][id^1] ) fa[ch[x][id^1]] = f;
        ch[x][id^1] = f , fa[f] = x;
        upgrade(f) , upgrade(x);
    }
    inline void splay(int pos) {
        while( root != pos ) {
            if( fa[fa[pos]] ) rotate(fa[pos]);
            rotate(pos);
        }
    }
    inline void upchain(int x) {
        while( x ) {
            upgrade(x) , 
            x = fa[x];
        }
    }
    inline void pushchain(int x) {
        if( fa[x] ) pushchain(fa[x]);
        push(x);
    }
    inline void insert(int cc) {
        if( !root ) {
            root = ++cnt , siz[cnt] = 1;
            initfill(root,cc);
            return;
        }
        int now = root;
        while( push(now) , ch[now][1] ) now = ch[now][1];
        ch[now][1] = ++cnt , siz[cnt] = 1 , fa[cnt] = now;
        initfill(cnt,cc) , upchain(cnt);
        splay(cnt);
    }
    inline int kth(int k) {
        int now = root;
        while( 1 ) {
            push(now);
            if( k < 0 ) exit(0);
            if( k == siz[ch[now][0]] + 1 ) return now;
            if( k <= siz[ch[now][0]] ) now = ch[now][0];
            else k -= siz[ch[now][0]] + 1 , now = ch[now][1];
        }
        throw "It Shouldn't Be Here ." ; 
    }
    inline void insertleft(int pos) {
        int now = root;
        while( push(now) , ch[now][0] ) now = ch[now][0];
        ch[now][0] = pos , fa[pos] = now;
        upchain(now);
    }
    inline void move(int k) {
        int mip = kth(n-k);
        splay(mip) , pushchain(mip);
        int pos = ch[mip][1]; ch[mip][1] = fa[pos] = 0;
        upchain(mip);
        insertleft(pos);
        splay(pos);
    }
    inline void filp() {
        int tar = kth(1);
        splay(tar);
        rev[ch[tar][1]] ^= 1 , applyrev(ch[tar][1]);
        splay(ch[tar][1]);
    }
    inline int getp(int k) {
        int pos = kth(k);
        return dat[pos];
    }
    inline void mkrson(int pos) {
        while( pos != ch[root][1] ) {
            if( fa[pos] != ch[root][1] ) rotate(fa[pos]);
            rotate(pos);
        }
    }
    inline void print(int st,int ed,int cc) {
        if( st == 1 && ed == n ) {
            fill(root,cc);
        } else if( st == 1 ) {
            int nxt = kth(ed+1);
            splay(nxt);
            fill(ch[root][0],cc);
            splay(ch[root][0]);
        } else if( ed == n ) {
            int prv = kth(st-1);
            splay(prv);
            fill(ch[root][1],cc);
            splay(ch[root][1]);
        } else {
            int nxt = kth(ed+1) , prv = kth(st-1);
            splay(prv) , mkrson(nxt);
            fill(ch[ch[root][1]][0],cc);
            splay(ch[ch[root][1]][0]);
        }
    }
    inline int count(int st,int ed) {
        if( st == 1 && ed == n ) {
            return max ( sum[root] - ( col[root][0] == col[root][1] ) , 1 );
        } else if( st == 1 ) {
            int nxt = kth(ed+1);
            splay(nxt);
            return sum[ch[root][0]];
        } else if( ed == n ) {
            int prv = kth(st-1);
            splay(prv);
            return sum[ch[root][1]];
        } else {
            int nxt = kth(ed+1) , prv = kth(st-1);
            splay(prv) , mkrson(nxt);
            return sum[ch[ch[root][1]][0]];
        }
    }
    inline int count(int st,int ed,int& rc) {
        if( st == 1 ) {
            int nxt = kth(ed+1);
            splay(nxt) , rc = col[ch[root][0]][0];
            return sum[ch[root][0]];
        } else if( ed == n ) {
            int prv = kth(st-1);
            splay(prv) , rc = col[ch[root][1]][1];
            return sum[ch[root][1]];
        }
        throw "It Shouldn't Be Here ." ; 
    }
}T;
 
int main() {
    static int m;
    static char o[10];
    scanf("%d%*d",&n);
    for(int i=1,x;i<=n;i++) {
        scanf("%d",&x);
        T.insert(x);
    }
     
    scanf("%d",&m);
    for(int i=1,x,y,k;i<=m;i++) {
        scanf("%s",o);
        if( *o == 'F' ) T.filp();
        else if( *o == 'C' ) {
            if( o[1] != 'S' ) printf("%d\n",T.count(1,n));
            else {
                scanf("%d%d",&x,&y);
                if( x <= y ) printf("%d\n",T.count(x,y));
                else {
                    int cx,cy,ans;
                    ans = T.count(x,n,cx) + T.count(1,y,cy);
                    ans -= ( cx == cy );
                    printf("%d\n",ans);
                }
            }
        } else {
            if( *o == 'R' ) {
                scanf("%d",&k);
                T.move(k);
            } else {
                scanf("%d%d",&x,&y);
                if( *o == 'S' ) {
                    int cx = T.getp(x) , cy = T.getp(y);
                    T.print(x,x,cy) , T.print(y,y,cx);
                } else {
                    scanf("%d",&k);
                    if( x <= y ) T.print(x,y,k);
                    else T.print(x,n,k) , T.print(1,y,k);
                }
            }
        }
    }
    return 0;
}
