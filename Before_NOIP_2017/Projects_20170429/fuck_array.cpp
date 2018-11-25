#include<cstdio>
//#define mid ((ll+rr)>>1)
#define mid ((l+r)>>1)
#define debug cout
#define inf 0x3f3f3f3f
#define lson (pos<<1)
#define rson ((pos<<1)|1)
using namespace std;
const int maxn=1e6+1e2;
//int l[4*maxn],r[4*maxn],mi[4*maxn],add[4*maxn];
int mi[4*maxn],add[4*maxn];
int m,n,x,s,e,ll,rr;
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
void build(int pos,int l,int r)
{
    //l[pos]=ll,r[pos]=rr;
    if(l==r)
    {
        mi[pos]=getint();
        return;
    }
    build(lson,l,mid);
    build(rson,mid+1,r);
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
void update(int pos,int x,int l,int r)
{
    if(l>rr||r<ll) return;
    if(ll<=l&&r<=rr)
    {
        add[pos]+=x;
        mi[pos]+=x;
        return;
    }
    push(pos);
    update(lson,x,l,mid);
    update(rson,x,mid+1,r);
    mi[pos]=min(mi[lson],mi[rson]);
}
int query(int pos,int l,int r)
{
    if(l>rr||r<ll) return inf;
    push(pos);
    if(l<=l&&r<=r) return mi[pos];
    return min(query(lson,l,mid),query(rson,mid+1,r));
}
int main()
{
    n=getint(),m=getint();
    build(1,1,n);
    int i;
    for(i=1;i<=m;i++)
    {
        x=getint(),s=getint(),e=getint();
        ll=s,rr=e;
        update(1,-x,1,n);
        if(query(1,1,n)<0) break;
    }
    if(i>m) puts("0");
    else puts("-1"),printf("%d\n",i);
    return 0;
}

