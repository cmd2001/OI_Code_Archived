#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define debug cout
using namespace std;
const int maxn=2e5+1e1;
const double alpha = 0.75;

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
        assert(*this==x);
        val += x.val;
        return *this;
    }
    inline void reset() {
        d[0] = d[1] = val = 0;
    }
}ps[maxn],nv[maxn];

int lson[maxn],rson[maxn],mi[maxn][2],mx[maxn][2],sum[maxn],siz[maxn];
int reb,root;

namespace RamPool {
    int pool[maxn],top;
    inline void DelNode(int x) {
        lson[x] = rson[x] = mi[x][0] = mi[x][1] = mx[x][0] = mx[x][1] = sum[x] = siz[x] = 0;
        nv[x].reset();
        pool[++top] = x;
    }
    inline int NewNode() {
        return pool[top--];
    }
}

using RamPool::DelNode;using RamPool::NewNode;

inline void update(int pos) {
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
    nv[pos] = p;
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
    ++siz[pos];
    if( !nv[pos].val ) {
        fill(pos,p);
        return pos;
    }
    if( p == nv[pos] ) {
        nv[pos] += p;
        return pos;
    }
    if( p < nv[pos] ) {
        if( !lson[pos] ) lson[pos] = NewNode();
        lson[pos] = insert(lson[pos],dir^1,p);
        /*if( !reb && siz[lson[pos]] > (double) siz[pos] * alpha )
            return rebuild(pos,dir);*/
    } else {
        if( !rson[pos] ) rson[pos] = NewNode();
        rson[pos] = insert(rson[pos],dir^1,p);
        /*if( !reb && siz[rson[pos]] > (double) siz[pos] * alpha )
            return rebuild(pos,dir);*/
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
    //debug<<"pos = "<<pos<<endl;
    if( outside(mi[pos][0],mi[pos][1],mx[pos][0],mx[pos][1],sx,sy,tx,ty) ) {
        //debug<<"outside"<<endl;
        return 0;
    }
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

int main() {
    static int ope,lastans,sx,sy,tx,ty,xx,yy,num;
    init();
    
    scanf("%*d");
    while( scanf("%d",&ope) == 1 && ope != 3 ) {
        if( ope == 1 ) {
            scanf("%d%d%d",&xx,&yy,&num);
            xx ^= lastans , yy ^= lastans , num ^= lastans , reb = 0;
            root = insert(root,0,(Point){xx,yy,num});
        } else {
            scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
            sx ^= lastans , sy ^= lastans , tx ^= lastans , ty ^= lastans;
            printf("%d\n", lastans = query(root,sx,sy,tx,ty) );
        }
    }
    
    return 0;
}