#include<bits/stdc++.h>
#define lli long long int
#define debug cout
#define lowbit(x) (x&(-x))
using namespace std;
const int maxn=5e4+1e2;
int tme[maxn],cnt,cpi;
lli dat[maxn],in[maxn],bas[maxn],pre[maxn][30],phi[100];
lli n,m,p,c;
bool end[maxn];
lli fastpow(lli x,lli tme,lli mod)
{
    lli ret=1,now=x%mod;
    while(tme)
    {
        if(tme&1) ret=(lli)ret*now%mod;
        now=(lli)now*now%mod;
        tme>>=1;
    }
    return ret%mod;
}
lli cal_phi(lli x)
{
    if(!x) return 0;
    if(x==1) return 1;
    lli ret=x;
    for(lli i=2;i*i<=x;i++) // Don;t write i<=x
    {
        if(!(x%i)) ret/=i,ret*=(i-1);
        while(!(x%i)) x/=i;
    }
    if(x>1) ret/=x,ret*=(x-1);
    return ret;
}

void getphi(lli base)
{
    while((phi[cpi++]=base)!=1) base=cal_phi(base);
    phi[cpi]=1;
    phi[++cpi]=1;
}
lli solve(int pos,int dpt,int modd)
{
    if(!dpt) return in[pos]%phi[modd];
    lli tmp=solve(pos,dpt-1,modd+1);
    if(tmp>=phi[modd+1]) return fastpow(c,tmp+phi[modd+1],phi[modd]);
    return fastpow(c,tmp,phi[modd]);
}

void core_update(int pos,lli x)
{
    while(pos<=n)
    {
        dat[pos]+=x;
        pos+=lowbit(pos);
    }
}
lli core_query(int pos)
{
    lli ret=0;
    while(pos)
    {
        ret+=dat[pos];
        ret%=p;
        pos-=lowbit(pos);
    }
    return ret;
}
void update(int l,int r)
{
    lli tmp;
    for(int i=l;i<=r;i++)
    {
        if(end[i]) continue;
        tmp=solve(i,++tme[i],0);
        if(tmp==bas[i]) {end[i]=1;continue;}
        core_update(i,-bas[i]);
        core_update(i,tmp);
        bas[i]=tmp;
    }
}
lli query(int l,int r)
{
    return core_query(r)-core_query(l-1);
}
void init()
{
    for(int i=1;i<=n;i++)
    {
        bas[i]=in[i];
        core_update(i,in[i]);
    }
}
int main()
{
    freopen("my.out","w",stdout);
    cin>>n>>m>>p>>c;
    getphi(p);
    for(int i=1;i<=n;i++) cin>>in[i];
    //for(int i=1;i<=n;i++) for(int j=0;j<=cpi;j++) pre[i][j]=solve(i,j,0);
    init();
    for(int i=1,q,a,b;i<=m;i++)
    {
        cin>>q>>a>>b;
        if(!q) update(a,b);
        else printf("%lld\n",query(a,b));
    }
    return 0;
}
