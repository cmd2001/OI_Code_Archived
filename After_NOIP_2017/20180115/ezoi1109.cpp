#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int in[maxn];
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],sum[maxn<<3],lazy[maxn<<3];
int n,m,cnt;

inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) {
        sum[pos] = in[ll];
        return;
    }
    const int mid = ( ll + rr ) >> 1;
    build(lson[pos]=++cnt,ll,mid);
    build(rson[pos]=++cnt,mid+1,rr);
    sum[pos] = sum[lson[pos]] + sum[rson[pos]];
}
inline void fill(int pos,int x) {
    sum[pos] = ( lazy[pos] = x ) * (r[pos] - l[pos] + 1 );
}
inline void push(int pos) {
    if( ~lazy[pos] ) {
        if( lson[pos] ) fill(lson[pos],lazy[pos]);
        if( rson[pos] ) fill(rson[pos],lazy[pos]);
        lazy[pos] = -1;
    }
}
inline void update(int pos,int ll,int rr,int x) {
    if( rr < l[pos] || r[pos] < ll ) return;
    if( ll <= l[pos] && r[pos] <= rr ) {
        fill(pos,x);
        return;
    }
    push(pos);
    update(lson[pos],ll,rr,x);
    update(rson[pos],ll,rr,x);
    sum[pos] = sum[lson[pos]] + sum[rson[pos]];
}
inline int query(int pos,int ll,int rr) {
    if( rr < l[pos] || r[pos] < ll ) return 0;
    if( ll <= l[pos] && r[pos] <= rr ) return sum[pos];
    push(pos);
    return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
}


int main() {
    static char com[10];
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i) , in[i]--;
    
    memset(lazy,-1,sizeof(lazy));
    build(cnt=1,1,n);
    
    for(int i=1,p,q,x;i<=m;i++) {
        scanf("%s",com);
        if( *com == 'C' ) {
            if( scanf("%d%d%d",&p,&q,&x) == 1 ) {
                x = query(1,p,p);
                update(1,p,p,x^1);
            } else {
                update(1,p,q,x-1);
            }
        } else if( *com == 'A' ) {
            if( scanf("%d%d",&p,&q) == 1 ) {
                printf("%d\n",query(1,p,p)+1);
            } else {
                x = query(1,p,q);
                printf("%d %d\n",q-p+1-x,x);
            }
        }
    }
    return 0;
}