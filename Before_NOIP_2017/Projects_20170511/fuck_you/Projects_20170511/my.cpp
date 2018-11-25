#include<bits/stdc++.h>
#define lli long long int
#define debug cout
#define mid ((l+r)>>1)
using namespace std;
const int maxn=5e4+1e2;
int cpi;
lli in[maxn],phi[100];
int n,m,p,c;
int lson[8*maxn],rson[8*maxn],lazy[8*maxn],tme[8*maxn],cnt,ll,rr;
lli dat[8*maxn];
inline int fastpow(int x,int tme,int mod,bool &abo)
{
    abo=0;
    lli ret=1,now=x;
    while(tme)
    {
        if(now>=mod) now%=mod,abo=1;
        if(tme&1)
        {
            ret=ret*now;
            if(ret>=mod) ret%=mod,abo=1;
        }
        now=now*now;
        tme>>=1;
    }
    return int(ret%mod);
}
inline int cal_phi(int x)
{
    if(!x) return 0;
    if(x==1) return 1;
    int ret=x;
    for(lli i=2;i*i<=x;i++)
    {
        if(!(x%i)) ret/=i,ret*=(i-1);
        while(!(x%i)) x/=i;
    }
    if(x>1) ret/=x,ret*=(x-1);
    return ret;
}

inline void getphi(int base)
{
    while((phi[cpi++]=base)!=1) base=cal_phi(base);
    phi[cpi]=1;
    phi[++cpi]=1;
}

int solve(int pos,int dpt,int modd,bool &labo)
{
    if(!dpt) return in[pos];
    bool myabo;
    lli tmp=solve(pos,dpt-1,modd+1,myabo);
    if(tmp>=phi[modd+1]||myabo) return fastpow(c,tmp%phi[modd+1]+phi[modd+1],phi[modd],labo);
    return fastpow(c,tmp,phi[modd],labo);
}


void build(int l,int r,int pos)
{
    if(l==r){ dat[pos]=in[l]; return;}
    build(l,mid,lson[pos]=++cnt);
    build(mid+1,r,rson[pos]=++cnt);
    dat[pos]=dat[lson[pos]]+dat[rson[pos]];
}
void update(int l,int r,int pos)
{
    if(lazy[pos]||rr<l||r<ll) return;
    if(l==r)
    {
        if(tme[pos]+1>cpi) {lazy[pos]=1;return;}
        bool tp;
        dat[pos]=solve(l,++tme[pos],0,tp);
        return;
    }
    update(l,mid,lson[pos]);
    update(mid+1,r,rson[pos]);
    dat[pos]=dat[lson[pos]]+dat[rson[pos]];
    lazy[pos]=lazy[lson[pos]]&&lazy[rson[pos]];
}
lli query(int l,int r,int pos)
{
    if(rr<l||r<ll) return 0;
    if(ll<=l&&r<=rr) return dat[pos];
    return query(l,mid,lson[pos])+query(mid+1,r,rson[pos]);
}

inline int getint()
{
    int ret=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while('0'<=ch&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
    return ret;
}

int main()
{
    freopen("data.in","r",stdin);
    freopen("my.out","w",stdout);
    n=getint(),m=getint(),p=getint(),c=getint();
    getphi(p);
    for(int i=1;i<=n;i++) in[i]=getint();
    build(1,n,++cnt);
    for(int i=1,q,a,b;i<=m;i++)
    {
       q=getint(),a=getint(),b=getint();
       if(!q) {ll=a,rr=b;update(1,n,1);}
       else ll=a,rr=b,printf("%lld\n",query(1,n,1)%p);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
