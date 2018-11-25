#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=8e5+1e2,maxm=2e6+1e2;

int n;

struct BinaryIndexTree {
    int dat[maxm];
    #define lowbit(x) (x&-x)
    inline void update(int pos,int x) {
        while( pos <=n ) {
            dat[pos] += x ,
            pos += lowbit(pos);
        }
    }
    inline int query(int pos) {
        int ret = 0;
        while( pos )
            ret += dat[pos] ,
            pos -= lowbit(pos);
        return ret;
    }
}bit;

struct QNode {
    int tpe,x,y,aid,tme,lam;
    friend bool operator < (const QNode &a,const QNode &b) {
        if( a.x != b.x )
            return a.x < b.x;
        if( a.y != b.y )
            return a.y < b.y;
        return a.tpe < b.tpe;
    }
}ns[maxn],tp[maxn];

int cnt,acn;
int ans[maxn];

inline void cdq(int l,int r) {
    if( l == r )
        return;
    const int mid = ( l + r ) >> 1;
    for(int i=l;i<=r;i++) {
        if( ns[i].tme <= mid && ns[i].tpe == 1 )
            bit.update(ns[i].y,ns[i].lam);
        if( ns[i].tme > mid && ns[i].tpe == 2 )
            ans[ns[i].aid] += ns[i].lam * bit.query(ns[i].y);
    }
    for(int i=l;i<=r;i++)
        if( ns[i].tme <= mid && ns[i].tpe == 1 )
            bit.update(ns[i].y,-ns[i].lam);
    int l1 = l , l2 = mid + 1;
    for(int i=l;i<=r;i++)
        if( ns[i].tme <= mid )
            tp[l1++] = ns[i];
        else
            tp[l2++] = ns[i];
    for(int i=l;i<=r;i++)
        ns[i] = tp[i];
    cdq(l,mid);
    cdq(mid+1,r);
}

int main() {
    static int t,x,y,xx,yy,lam;
    scanf("%*d%d",&n);
    while( scanf("%d",&t) == 1 && t != 3 ) {
        if( t == 1 ) {
            scanf("%d%d%d",&x,&y,&lam);
            ns[++cnt].tpe = t , ns[cnt].x = x , ns[cnt].y = y ,
            ns[cnt].lam = lam , ns[cnt].tme = cnt;
        }
        else {
            scanf("%d%d%d%d",&x,&y,&xx,&yy);
            --x , --y , ++acn;
            ns[++cnt].tpe = t , ns[cnt].x = x , ns[cnt].y = y ,
            ns[cnt].aid = acn , ns[cnt].tme = cnt , ns[cnt].lam = 1;
            ns[++cnt].tpe = t , ns[cnt].x = xx , ns[cnt].y = yy ,
            ns[cnt].aid = acn , ns[cnt].tme = cnt , ns[cnt].lam = 1;
            ns[++cnt].tpe = t , ns[cnt].x = x , ns[cnt].y = yy ,
            ns[cnt].aid = acn , ns[cnt].tme = cnt , ns[cnt].lam = -1;
            ns[++cnt].tpe = t , ns[cnt].x = xx , ns[cnt].y = y ,
            ns[cnt].aid = acn , ns[cnt].tme = cnt , ns[cnt].lam = -1;
        }
    }
    sort(ns+1,ns+1+cnt);
    cdq(1,cnt);
    
    for(int i=1;i<=acn;i++)
        printf("%d\n",ans[i]);
    
    return 0;
}