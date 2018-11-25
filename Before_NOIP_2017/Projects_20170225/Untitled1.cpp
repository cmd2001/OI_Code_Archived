#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
#define lson (p<<1)
#define rson ((p<<1)|1)
#define mid ((l[p]+r[p])>>1)
using namespace std;
const int maxn=1e5+10;
int q[maxn],m,n,now;
int l[maxn<<2],r[maxn<<2],sum[maxn<<2],num[maxn<<2];//memset num -1;
int op[maxn],opl[maxn],opr[maxn],pos;
void build(int p,int ll,int rr)
{
    l[p]=ll,r[p]=rr;
    if(ll==rr)
    {
        sum[p]=(q[ll]>now);
        //debug<<sum[p]<<endl;
        return;
    }
    build(lson,ll,mid);
    build(rson,mid+1,rr);
    sum[p]=sum[lson]+sum[rson];
}
void down(int p)
{
    if(num[p]!=-1)
    {
        num[lson]=num[p];
        num[rson]=num[p];
        sum[lson]=num[p]*(r[lson]-l[lson]+1);
        sum[rson]=num[p]*(r[rson]-l[rson]+1);
        sum[p]=sum[lson]+sum[rson];
        num[p]=-1;
    }
}
void update(int p,int ll,int rr,int n)
{
    if(ll>r[p]||rr<l[p]) return;
    if(ll<=l[p]&&rr>=r[p])
    {
        num[p]=n;
        sum[p]=(r[p]-l[p]+1)*n;
        return;
    }
    down(p);
    update(lson,ll,rr,n);
    update(rson,ll,rr,n);
    sum[p]=sum[lson]+sum[rson];
}
int query(int p,int ll,int rr)
{
    if(ll>r[p]||rr<l[p]) return 0;
    if(ll<=l[p]&&rr>=r[p])
    {
        return sum[p];
    }
    down(p);
    return query(lson,ll,rr)+query(rson,ll,rr);
}
bool check(int x)
{
    //debug<<"num="<<x<<endl;
    int tmp;
    memset(l,0,sizeof(l));
    memset(r,0,sizeof(r));
    memset(sum,0,sizeof(sum));
    memset(num,-1,sizeof(num));
    now=x;
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        tmp=query(1,opl[i],opr[i]);
        //debug<<"l="<<opl[i]<<"r="<<opr[i]<<endl;
        //debug<<"tmp="<<tmp<<endl;
        if(op[i])//jiangxu
        {
            update(1,opl[i],opl[i]+tmp-1,1);
            update(1,opl[i]+tmp,opr[i],0);
        }
        else//shengxu
        {
            update(1,opr[i]-tmp+1,opr[i],1);
            update(1,opl[i],opr[i]-tmp,0);
        }
    }
    return query(1,pos,pos);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",q+i);
    for(int i=1;i<=m;i++) scanf("%d%d%d",op+i,opl+i,opr+i);
    scanf("%d",&pos);
    int ll=1,rr=n,md=(1+n)/2;
    while(ll!=md)
    {
        //debug<<"l="<<ll<<"  r="<<rr<<"  mid="<<md<<endl;
        //debug<<"check======================="<<check(md)<<endl;
        if(check(md)) {ll=md;}
        else rr=md;
        md=(ll+rr)/2;
    }
    printf("%d\n",rr);
    return 0;
}
