#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1.5e6+1e2,maxe=5e5+1e2;

int ans[maxe];
int xs[maxn<<1],ys[maxn<<1],xcnt,ycnt,nslen;

struct BinaryIndexTree {
    int dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,int x) {
        while( pos <= ycnt ) dat[pos] += x , pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while( pos ) ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
}bit;

struct Node {
    int x,y,tpe,id,mul; // tpe = 0 means point , tpe = 1 means query .
    friend bool operator < (const Node &a,const Node &b) {
        return a.x != b.x ? a.x < b.x : a.tpe < b.tpe;
    }
}ns[maxn<<1];

inline void solve(int xl,int xr,int ql,int qr) {
    if( qr <= ql ) return;
    if( xl == xr ) {
        for(int i=ql;i<=qr;i++) {
            if( !ns[i].tpe ) bit.update(ns[i].y,1);
            else ans[ns[i].id] += bit.query(ns[i].y) * ns[i].mul;
        }
        for(int i=ql;i<=qr;i++) if( !ns[i].tpe ) bit.update(ns[i].y,-1);
        return;
    }
    const int xmid = ( xl + xr ) >> 1;
    int qmid;
    for(int i=ql;i<=qr;i++) {
        if( ns[i].x > xmid ) {
            qmid = i - 1;
            break;
        }
    }
    for(int i=ql;i<=qmid;i++) if( !ns[i].tpe ) bit.update(ns[i].y,1);
    for(int i=qmid+1;i<=qr;i++) if( ns[i].tpe ) ans[ns[i].id] += bit.query(ns[i].y) * ns[i].mul;
    for(int i=ql;i<=qmid;i++) if( !ns[i].tpe ) bit.update(ns[i].y,-1);
    solve(xl,xmid,ql,qmid) , solve(xmid+1,xr,qmid+1,qr);
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,x,y;i<=n;i++) {
        scanf("%d%d",&x,&y) , ++nslen , --x , --y;
        ns[nslen].x = x + 1 , ns[nslen].y = y + 1;
    }
    for(int i=1,x,y,xx,yy;i<=m;i++) {
        scanf("%d%d%d%d",&x,&y,&xx,&yy) , --x , --y , --xx , --yy;
        ns[++nslen] = (Node){x,y,1,i,1} , ns[++nslen] = (Node){xx+1,yy+1,1,i,1} ,
        ns[++nslen] = (Node){xx+1,y,1,i,-1} , ns[++nslen] = (Node){x,yy+1,1,i,-1};
    }
    for(int i=1;i<=nslen;i++) xs[i] = ns[i].x , ys[i] = ns[i].y;
    sort(xs+1,xs+1+nslen) , xcnt = unique(xs+1,xs+1+nslen) - xs - 1;
    sort(ys+1,ys+1+nslen) , ycnt = unique(ys+1,ys+1+nslen) - ys - 1;
    for(int i=1;i<=nslen;i++) {
        ns[i].x = lower_bound(xs+1,xs+1+xcnt,ns[i].x) - xs ,
        ns[i].y = lower_bound(ys+1,ys+1+ycnt,ns[i].y) - ys ;
    }
    sort(ns+1,ns+1+nslen);
    solve(1,xcnt,1,nslen);
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}