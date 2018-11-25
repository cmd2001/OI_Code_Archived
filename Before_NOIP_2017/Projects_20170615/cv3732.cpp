#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e2+1e1,maxm=1e6+1e2,maxl=1e4+1e2;

int n,m,l,p=5;
int prime[6]={0,11261,19997,22877,21893,14843};
int in[6][maxn],ans[maxn],cnt;
bitset<maxm> vis;
char s[maxl];

inline int getint(int mod)
{
    int len=strlen(s),ret=0,fix=1;
    if(s[0]=='-') fix=-1;
    else ret=s[0]-'0';
    for(int i=1;i<len;i++)
    {
        ret=ret*10+s[i]-'0';
        if(ret>mod) ret%=mod;
    }
    return ret*fix;
}
inline void getin()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++)
    {
        scanf("%s",s);
        for(int k=1;k<=p;k++) in[k][i]=getint(prime[k]);
    }
}

void mark(int x,int p)
{
    while(x<0) x+=p;
    while(x<=m)
    {
        vis[x]=1;
        x+=p;
    }
}
inline bool core_test(int x,int mod,int *dat)
{
    lli now=0;
    for(int i=n;i>=0;i--)
    {
        now=now*x+dat[i];
        if(abs(now)>mod) now%=mod;
    }
    now%=mod;
    if(now) mark(x,mod);
    return !now;
}
inline bool test(int x)
{
     bool ret=1;
     for(int i=1;i<=p;i++)
     {
        ret&=core_test(x,prime[i],in[i]);
        if(!ret) return 0;
    }
    return 1;
}


int main()
{
    freopen("equation10.in","r",stdin);
    getin();
    for(int i=1;i<=m;i++)
    {
        if(vis[i]) continue;
        if(test(i)) ans[++cnt]=i;
    }
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++) printf("%d\n",ans[i]);
    return 0;
}
