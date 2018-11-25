#pragma GCC optimize(3)
#include<cstdio>
#include<algorithm>
#include<cctype>
using namespace std;
const int maxn=2e5+1e1;
const double alpha = 0.8;
   
int cmp;
struct Point {
    int d[2],val;
    friend bool operator < (const Point &a,const Point &b) {
        return a.d[cmp] < b.d[cmp];
    }
    friend bool operator == (const Point &a,const Point &b) {
        return a.d[0] == b.d[0] && a.d[1] == b.d[1];
    }
    Point operator += (const Point &x) {
        val += x.val;
        return *this;
    }
    inline void reset() {
        d[0] = d[1] = val = 0;
    }
}ps[maxn],nv[maxn];
   
int lson[maxn],rson[maxn],mi[maxn][2],mx[maxn][2],sum[maxn],siz[maxn];
int reb,delta,root;
   
namespace RamPool {
    int pool[maxn],top;
    inline void DelNode(int x) {
        lson[x] = rson[x] = 0;
        pool[++top] = x;
    }
    inline int NewNode() {
        return pool[top--];
    }
}
   
using RamPool::DelNode;using RamPool::NewNode;
   
inline void update(int pos) {
    sum[pos] = nv[pos].val;
    if( lson[pos] ) {
        for(int i=0;i<2;i++)
            mi[pos][i] = min( mi[pos][i] , mi[lson[pos]][i] ),
            mx[pos][i] = max( mx[pos][i] , mx[lson[pos]][i] );
        sum[pos] += sum[lson[pos]];
    }
    if( rson[pos] ) {
        for(int i=0;i<2;i++)
            mi[pos][i] = min( mi[pos][i] , mi[rson[pos]][i] ),
            mx[pos][i] = max( mx[pos][i] , mx[rson[pos]][i] );
        sum[pos] += sum[rson[pos]];
    }
}
inline void fill(int pos,const Point &p) {
    nv[pos] = p , siz[pos] = 1;
    for(int i=0;i<2;i++)
        mi[pos][i] = mx[pos][i] = p.d[i];
    sum[pos] = p.val;
}
inline void build(int pos,int ll,int rr,int dir) {
    cmp = dir;
    const int mid = ( ll + rr ) >> 1;
    nth_element(ps+ll,ps+mid,ps+rr+1);
    fill(pos,ps[mid]); siz[pos] = rr - ll + 1;
    if( ll < mid ) build(lson[pos]=NewNode(),ll,mid-1,dir^1);
    if( rr > mid ) build(rson[pos]=NewNode(),mid+1,rr,dir^1);
    update(pos);
}
inline void recycle(int pos,int& pcnt) {
    if( lson[pos] ) recycle(lson[pos],pcnt);
    if( rson[pos] ) recycle(rson[pos],pcnt);
    ps[++pcnt] = nv[pos];
    DelNode(pos);
}
inline int rebuild(int pos,int dir) {
    reb = 1;
    int pcnt = 0;
    recycle(pos,pcnt);
    int ret = NewNode();
    build(ret,1,pcnt,dir);
    return ret;
}
   
inline int insert(int pos,int dir,const Point &p) {
    cmp = dir;
    if( !nv[pos].val ) {
        fill(pos,p);
        return pos;
    }
    if( p == nv[pos] ) {
        nv[pos] += p;
        sum[pos] += p.val;
        return pos;
    }
    ++siz[pos];
    if( p < nv[pos] ) {
        if( !lson[pos] ) lson[pos] = NewNode();
        lson[pos] = insert(lson[pos],dir^1,p);
        if( !reb && delta > 1000 && siz[lson[pos]] > (double) siz[pos] * alpha )
            return rebuild(pos,dir);
    } else {
        if( !rson[pos] ) rson[pos] = NewNode();
        rson[pos] = insert(rson[pos],dir^1,p);
        if( !reb && delta > 1000 && siz[rson[pos]] > (double) siz[pos] * alpha )
            return rebuild(pos,dir);
    }
    update(pos);
    return pos;
}
   
inline bool inside(const int &Insx,const int &Insy,const int &Intx,const int &Inty,const int &Osx,const int &Osy,const int &Otx,const int &Oty) {
    return Osx <= Insx &&Intx <= Otx && Osy <= Insy &&Inty <= Oty;
}
inline bool outside(const int &Insx,const int &Insy,const int &Intx,const int &Inty,const int &Osx,const int &Osy,const int &Otx,const int &Oty) {
    return Insx > Otx || Intx < Osx || Insy > Oty || Inty < Osy;
}
inline bool inside(const Point &p,const int &Osx,const int &Osy,const int &Otx,const int &Oty) {
    return inside(p.d[0],p.d[1],p.d[0],p.d[1],Osx,Osy,Otx,Oty);
}
inline int query(int pos,const int &sx,const int &sy,const int &tx,int const &ty) {
    if( outside(mi[pos][0],mi[pos][1],mx[pos][0],mx[pos][1],sx,sy,tx,ty) ) return 0;
    if( inside(mi[pos][0],mi[pos][1],mx[pos][0],mx[pos][1],sx,sy,tx,ty) ) return sum[pos];
    int ret = 0;
    if( inside(nv[pos],sx,sy,tx,ty) ) ret += nv[pos].val;
    if( lson[pos] ) ret += query(lson[pos],sx,sy,tx,ty);
    if( rson[pos] ) ret += query(rson[pos],sx,sy,tx,ty);
    return ret;
}
   
inline void init() {
    for(int i=1;i<maxn;i++)
        DelNode(i);
    root = NewNode();
}

inline char nextchar() {
    static char buf[1<<22],*st=buf+(1<<22),*ed=buf+(1<<22);
    if( st == ed ) ed = buf + fread(st=buf,1,1<<22,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0,ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}
   
int main() {
    static int ope,lastans,sx,sy,tx,ty,xx,yy,num;
    init();
       
    getint();
    while( ( ope = getint() ) != 3 ) {
        if( ope == 1 ) {
            xx = getint() , yy = getint() , num = getint();
            reb = 0 , ++delta;
            xx ^= lastans , yy ^= lastans , num ^= lastans;
            root = insert(root,0,(Point){xx,yy,num});
        } else {
            sx = getint() , sy = getint() , tx = getint() , ty = getint();
            sx ^= lastans , sy ^= lastans , tx ^= lastans , ty ^= lastans;
            printf("%d\n", lastans = query(root,sx,sy,tx,ty) );
        }
    }
       
    return 0;
}
