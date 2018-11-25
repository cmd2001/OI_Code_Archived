#include<bits/stdc++.h>
#define mid ((ll+rr)>>1)
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int n,m;
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],dat[maxn<<3],rev[maxn<<3],cnt;

inline void push(int pos)
{
    if(rev[pos])
    {
        if(lson[pos]) rev[lson[pos]]^=1,dat[lson[pos]]=r[lson[pos]]-l[lson[pos]]+1-dat[lson[pos]];
        if(rson[pos]) rev[rson[pos]]^=1,dat[rson[pos]]=r[rson[pos]]-l[rson[pos]]+1-dat[rson[pos]];
        rev[pos]=0;
    }
}
inline void build(int pos,int ll,int rr)
{
    l[pos]=ll,r[pos]=rr;
    if(ll==rr) return;
    build(lson[pos]=++cnt,ll,mid);
    build(rson[pos]=++cnt,mid+1,rr);
}
inline void update(int pos,int ll,int rr)
{
    if(rr<l[pos]||r[pos]<ll) return;
    if(ll<=l[pos]&&r[pos]<=rr)
    {
        rev[pos]^=1;
        dat[pos]=r[pos]-l[pos]+1-dat[pos];
        return;
    }
    push(pos);
    update(lson[pos],ll,rr);
    update(rson[pos],ll,rr);
    dat[pos]=dat[lson[pos]]+dat[rson[pos]];
}
inline int query(int pos,int ll,int rr)
{
    if(rr<l[pos]||r[pos]<ll) return 0;
    if(ll<=l[pos]&&r[pos]<=rr) return dat[pos];
    push(pos);
    return query(lson[pos],ll,rr)+query(rson[pos],ll,rr);
}


int main()
{
    scanf("%d%d",&n,&m);
    build(++cnt,1,n);
    for(int i=1,a,b,x;i<=m;i++)
    {
        scanf("%d%d%d",&x,&a,&b);
        if(!x) update(1,a,b);
        else printf("%d\n",query(1,a,b));
    }
    return 0;
}
