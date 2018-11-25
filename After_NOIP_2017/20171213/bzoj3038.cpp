#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define mid ( ( ll + rr ) >> 1 )
#define lli long long int
using namespace std;
const int maxn=1e5+1e2;

int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3];
lli dat[maxn<<3];
unsigned char lazy[maxn<<3];
int n,m,cnt;

inline void build(int pos,int ll,int rr)
{
    l[pos] = ll , r[pos] = rr;
    if( ll == rr )
    {
        scanf("%lld",dat+pos);
        lazy[pos] = dat[pos] == 1;
        return;
    }
    build(lson[pos]=++cnt,ll,mid);
    build(rson[pos]=++cnt,mid+1,rr);
    dat[pos] = dat[lson[pos]] + dat[rson[pos]];
    lazy[pos] = lazy[lson[pos]] && lazy[rson[pos]];
}

inline void update(int pos,int ll,int rr)
{
    if( rr < l[pos] || r[pos] < ll )
        return;
    if( lazy[pos] )
        return;
    if( l[pos] == r[pos] )
    {
        dat[pos] = sqrt(dat[pos]);
        lazy[pos] = dat[pos] == 1;
        return;
    }
    update(lson[pos],ll,rr);
    update(rson[pos],ll,rr);
    dat[pos] = dat[lson[pos]] + dat[rson[pos]];
    lazy[pos] = lazy[lson[pos]] && lazy[rson[pos]];
}

inline lli query(int pos,int ll,int rr)
{
    if( rr < l[pos] || r[pos] < ll )
        return 0;
    if( ll <= l[pos] && r[pos] <= rr )
        return dat[pos];
    return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
}

int main()
{
    scanf("%d",&n);
    
    build(cnt=1,1,n);
    
    scanf("%d",&m);
    
    for(int i=1,q,a,b;i<=m;i++)
    {
        scanf("%d%d%d",&q,&a,&b);
        if( a > b )
            swap(a,b);
        if( !q )
            update(1,a,b);
        else
            printf("%lld\n",query(1,a,b));
    }
    
    return 0;
}