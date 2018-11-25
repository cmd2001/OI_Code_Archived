#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=5e4+1e2;

int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],mx[maxn<<3],cnt;
int in[maxn],srt[maxn];
int n;

inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) {
        mx[pos] = in[ll];
        return;
    }
    const int mid = ( ll + rr ) >> 1;
    build( lson[pos]=++cnt , ll , mid );
    build( rson[pos]=++cnt , mid+1 , rr );
    mx[pos] = max( mx[lson[pos]] , mx[rson[pos]] );
}

inline int query(int pos,int ll,int rr) {
    if( rr < l[pos] || r[pos] < ll ) return -1;
    if( ll <= l[pos] && r[pos] <= rr ) return mx[pos];
    return max( query(lson[pos],ll,rr) , query(rson[pos],ll,rr) );
}

inline bool judgecan(int x,int y) {
    if( y < x ) return 0;
    if( x == y ) return 1;
    int fx = lower_bound(srt+1,srt+1+n,x)-srt;
    int fy = lower_bound(srt+1,srt+1+n,y)-srt;
    if( srt[fx] != x || srt[fy] != y ) return 0;
    if( fy - fx + 1 != y - x + 1 ) return 0;
    if( fy == fx + 1 ) return in[fx] >= in[fy];
    return in[fx] >= in[fy] && query(1,fx+1,fy-1) < in[fy];
}
inline bool judgemaybe(int x,int y) {
    if( y < x ) return 0;
    if( y <= srt[1] || x >= srt[n] ) return 1;
    int fx = lower_bound(srt+1,srt+1+n,x)-srt;
    int fy = lower_bound(srt+1,srt+1+n,y)-srt;
    if( srt[fx] != x && srt[fy] != y ) return 1;
    if( srt[fx] == x && srt[fy] == y ) {
        if( fy == fx + 1 ) return in[fx] >= in[fy];
        return in[fx] >= in[fy] && query(1,fx+1,fy-1) < in[fy];
    }
    if( srt[fy] != y ) {
        if( fy == fx + 1 ) return 1;
        return query(1,fx+1,fy-1) < in[fx];
    }
    if( srt[fx] != fx ) {;
        return query(1,fx,fy-1) < in[fy];
    }
}

int main() {
    static int m;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",srt+i,in+i);
    
    build(cnt=1,1,n);
    scanf("%d",&m);
    for(int i=1,x,y;i<=m;i++) {
        scanf("%d%d",&x,&y);
        if( judgecan(x,y) ) puts("true");
        else if( judgemaybe(x,y) ) puts("maybe");
        else puts("false");
    }
    
    return 0;
}
