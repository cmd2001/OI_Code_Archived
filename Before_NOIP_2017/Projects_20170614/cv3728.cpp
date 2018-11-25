#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e5+1e2,MOD=10007;

lli in[maxn],sum[maxn],sig[maxn],mxson[maxn],secson[maxn],msans[maxn],mx;
int s[maxn],t[maxn<<1],nxt[maxn<<1],n;
bool vis[maxn];

inline void addedge(int from,int to)
{
    static int cnt=0;
    t[++cnt]=to;
    nxt[cnt]=s[from];
    s[from]=cnt;
}
inline void doubledge(int a,int b)
{
    addedge(a,b);
    addedge(b,a);
}


inline void update(lli &mx,lli &sec,lli x)
{
    if(x>=mx) sec=mx,mx=x;
    else if(x>=sec) sec=x;
}
inline void dfs(int pos)
{
    int at=s[pos];
    while(at)
    {
        if(!vis[t[at]])
        {
            vis[t[at]]=1;
            dfs(t[at]);
            sum[pos]+=in[t[at]];
            update(mxson[pos],secson[pos],in[t[at]]);
        }
        at=nxt[at];
    }
}
inline lli getm(int pos,int fa) // this function returns the max value and updates the sum
{
    lli ret=0;
    int at=s[pos];
    while(at)
    {
        if(!vis[t[at]])
        {
            vis[t[at]]=1;
            sig[pos]+=(in[t[at]]*(sum[pos]-in[t[at]]))%MOD;
            sig[pos]%=MOD;
            ret=max(ret,getm(t[at],pos));
            sig[pos]%=MOD;
            ret=max(ret,in[t[at]]*in[fa]);
            sig[pos]+=sig[t[at]];
            sig[pos]%=MOD;
        }
        at=nxt[at];
    }
    sig[fa]+=2*sum[pos]*in[fa];
    sig[fa]%=MOD;
    ret=max(ret,mxson[pos]*secson[pos]);
    return ret;
}

int main()
{
    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        doubledge(a,b);
    }
    for(int i=1;i<=n;i++) scanf("%lld",in+i);

    vis[1]=1;
    dfs(1);
    memset(vis,0,sizeof(vis));
    vis[1]=1;
    mx=getm(1,0);
    printf("%lld %lld\n",mx,sig[1]);
    return 0;
}


