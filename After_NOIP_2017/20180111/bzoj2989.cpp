#include<iostream>
#include<cstdio>
#define debug cout
using namespace std;
const int maxn=2e7+1e1,maxm=160010;
const int slin=-60000,tlin=160000;
const int slout=0,tlout=160000;

int in[100010];
int lson[maxn],rson[maxn],siz[maxn],cnt;
int roots[maxm<<4];

inline void update_in(int& pos,int l,int r,int tar) {
    if( !pos )
        pos = ++cnt;
    ++siz[pos];
    if( l == r )
        return;
    const int mid = ( l + r ) >> 1;
    if( tar <= mid )
        update_in(lson[pos],l,mid,tar);
    else
        update_in(rson[pos],mid+1,r,tar);
}
inline int query_in(int pos,int l,int r,int ll,int rr) {
    if( ( !pos ) || (  rr < l || r < ll ) ) {
        return 0;
    }
    if( ll <= l && r <= rr )
        return siz[pos];
    const int mid = ( l + r ) >> 1;
    return query_in(lson[pos],l,mid,ll,rr) + query_in(rson[pos],mid+1,r,ll,rr);
}
inline void update_out(int pos,int l,int r,int x,int y) {
    update_in(roots[pos],slin,tlin,y);
    if( l == r )
        return;
    const int mid = ( l + r ) >> 1;
    if( x <= mid )
        update_out(pos<<1,l,mid,x,y);
    else
        update_out((pos<<1)|1,mid+1,r,x,y);
}
inline int query_out(int pos,int l,int r,int xl,int xr,int yl,int yr) {
    if( xr < l || r < xl )
        return 0;
    if( xl <= l && r <= xr )
        return query_in(roots[pos],slin,tlin,yl,yr);
    const int mid = ( l + r ) >> 1;
    return query_out(pos<<1,l,mid,xl,xr,yl,yr) + query_out((pos<<1)|1,mid+1,r,xl,xr,yl,yr);
}

int main() {
    static int n,m;
    static char c[20];
    
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) {
        scanf("%d",in+i);
        update_out(1,slout,tlout,in[i]+i,in[i]-i);
    }
    for(int i=1,x,k;i<=m;i++) {
        scanf("%s%d%d",c,&x,&k);
        if( *c == 'Q' ) {
            int sx = max( slout , x + in[x] - k ) , tx = min( tlout , x + in[x] + k );
            int sy = max( slin , in[x] - x - k ) , ty = min( tlin , in[x] - x + k );
            printf("%d\n",query_out(1,slout,tlout,sx,tx,sy,ty));
        }
        else if( *c == 'M') {
            in[x] = k;
            update_out(1,slout,tlout,in[x]+x,in[x]-x);
        }
    }
    
    return 0;
}