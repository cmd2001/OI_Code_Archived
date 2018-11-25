#include<cstdio>
#pragma GCC optimize (3)
#define mid ((ll+rr)>>1)
#define debug cout
#define inf 0x3f3f3f3f
#define lson (pos<<1)
#define rson ((pos<<1)|1)
using namespace std;
const int maxn=1e6+1e2;
int l[4*maxn],r[4*maxn],mi[4*maxn],add[4*maxn];
int m,n,x,s,e;
inline int min(int a,int b){return a<b?a:b;}
inline int getint()
{
    int fix=1,ret=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
    while(ch>='0'&&ch<='9')
    {
        ret=ret*10+ch-'0';
        ch=getchar();
    }
    return fix*ret;
}
void build(int pos,int ll,int rr)
{
    l[pos]=ll,r[pos]=rr;
    if(ll==rr)
    {
        mi[pos]=getint();
        return;
    }
    build(lson,ll,mid);
    build(rson,mid+1,rr);
    mi[pos]=min(mi[lson],mi[rson]);
}
inline void push(int pos)
{
    if(add[pos])
    {
        add[lson]+=add[pos],mi[lson]+=add[pos];
        add[rson]+=add[pos],mi[rson]+=add[pos];
        add[pos]=0;
    }
}
void update(int pos,int ll,int rr,int x)
{
    if(l[pos]>rr||r[pos]<ll) return;
    if(ll<=l[pos]&&r[pos]<=rr)
    {
        add[pos]+=x;
        mi[pos]+=x;
        return;
    }
    push(pos);
    update(lson,ll,rr,x);
    update(rson,ll,rr,x);
    mi[pos]=min(mi[lson],mi[rson]);
}
int query(int pos,int ll,int rr)
{
    if(l[pos]>rr||r[pos]<ll) return inf;
    push(pos);
    if(ll<=l[pos]&&r[pos]<=rr) return mi[pos];
    return min(query(lson,ll,rr),query(rson,ll,rr));
}
int main()
{
    n=getint(),m=getint();
    build(1,1,n);
    register int i;
    for(i=1;i<=m;i++)
    {
        x=getint(),s=getint(),e=getint();
        update(1,s,e,-x);
        if(query(1,s,e)<0) break;
    }
    if(i>m) puts("0");
    else puts("-1"),printf("%d\n",i);
    return 0;
}
