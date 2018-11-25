#include<bits/stdc++.h>
#define lson (p<<1)
#define rson ((p<<1)|1)
#define mid (l[p]+r[p])/2
#define debug cout
using namespace std;
const long long maxn=1e5+1e2;
long long n,m,mod;
long long l[maxn<<2],r[maxn<<2],mul[maxn<<2],sum[maxn<<2],add[maxn<<2];
long long in[maxn+10];
void build(long long p,long long ll,long long rr)
{
    l[p]=ll;r[p]=rr;
    mul[p]=1;
    if(ll==rr)
    {
        sum[p]=in[ll];
    }
    else
    {
        build(lson,ll,mid);
        build(rson,mid+1,rr);
        sum[p]=((long long)sum[lson]+sum[rson])%mod;
    }
}
void down(long long p)
{
    if(mul[p]!=1)
    {
        mul[lson]=(long long)mul[lson]*mul[p]%mod;
        mul[rson]=(long long)mul[rson]*mul[p]%mod;
        sum[lson]=(long long)sum[lson]*mul[p]%mod;
        sum[rson]=(long long)sum[rson]*mul[p]%mod;
        add[lson]=(long long)add[lson]*mul[p]%mod;
        add[rson]=(long long)add[rson]*mul[p]%mod;
        mul[p]=1;
    }
    if(add[p])
    {
        add[lson]=((long long)add[lson]+add[p])%mod;
        add[rson]=((long long)add[rson]+add[p])%mod;
        sum[lson]=((long long)sum[lson]+add[p]*(r[lson]-l[lson]+1))%mod;
        sum[rson]=((long long)sum[rson]+add[p]*(r[rson]-l[rson]+1))%mod;
        add[p]=0;
    }
}
void tplus(long long p,long long ll,long long rr,long long x)
{
    if(ll<=l[p]&&rr>=r[p])
    {
        add[p]=((long long)add[p]+x)%mod;
        sum[p]=((long long)x*(r[p]-l[p]+1)+sum[p])%mod;
        return;
    }
    down(p);
    if(ll<=mid) tplus(lson,ll,rr,x);
    if(rr>mid) tplus(rson,ll,rr,x);
    sum[p]=((long long)sum[lson]+sum[rson])%mod;
}
void multi(long long p,long long ll,long long rr,long long x)
{
    if(ll<=l[p]&&rr>=r[p])
    {
        mul[p]=((long long)mul[p]*x)%mod;
        sum[p]=(long long)sum[p]*x%mod;
        add[p]=(long long)add[p]*x%mod;
        return;
    }
    down(p);
    if(ll<=mid) multi(lson,ll,rr,x);
    if(rr>mid) multi(rson,ll,rr,x);
    sum[p]=((long long)sum[lson]+sum[rson])%mod;
}
long long read(long long p,long long ll,long long rr)
{
    if(rr<l[p]||ll>r[p]) return 0;
    else if(ll<=l[p]&&rr>=r[p]) return sum[p];
    down(p);
    return ((long long)read(lson,ll,rr)+read(rson,ll,rr))%mod;
}
int main()
{
    scanf("%lld%lld",&n,&mod);
    for(long long i=1;i<=n;i++) scanf("%lld",in+i);
    build(1,1,n);
    scanf("%lld",&m);
    for(long long i=1,c,a,b,x;i<=m;i++)
    {
    	scanf("%lld",&c);
        if(c==3)
        {
            scanf("%lld%lld",&a,&b);
            printf("%lld\n",read(1,a,b));
        }
        else if(c==2)
        {
            scanf("%lld%lld%lld",&a,&b,&x);
            tplus(1,a,b,x);
        }
        else if(c==1)
        {
            scanf("%lld%lld%lld",&a,&b,&x);
            multi(1,a,b,x);
        }
    }
    return 0;
}
