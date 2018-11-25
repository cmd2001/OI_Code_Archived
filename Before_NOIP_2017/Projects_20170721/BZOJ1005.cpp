#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#define debug cout
using namespace std;
const int maxn=1e3+1e2;
const int base=1e6;

int in[maxn],n,tot,m;
int prime[maxn],cnt[maxn],pl;
bitset<maxn> vis;
int ans[maxn],len;

inline void getprime(int lim)
{
    static int cnt=0;
    for(int i=2,j;i<=lim;i++)
    {
        if(!vis[i]) prime[++cnt]=i;
        for(j=1;j<=cnt&&i*prime[j]<=lim&&i%prime[j];j++) vis[i*prime[j]]=1;
        if(i*prime[j]<=lim) vis[i*prime[j]]=1;
    }
    pl=cnt;
}

inline void divide(int x,int ope)
{
	if(!x) return;//puts("Fuck you!"),exit(0);
    for(int i=1;i<=pl;i++)
    {
        while(!(x%prime[i]))
        {
            cnt[i]+=ope;
            x/=prime[i];
        }
    }
}

inline void mul(int x)
{
    for(int i=1;i<=len;i++)
    {
        ans[i]*=x;
        if(ans[i]>base)
        {
            ans[i+1]+=ans[i]/base;
            ans[i]%=base;
        }
    }
    while(ans[len+1])
    {
        len++;
        ans[len+1]+=ans[len]/base;
        ans[len]%=base;
    }
}

inline void update(int x,int ope) // update x! with ope
{
    for(int i=1;i<=x;i++) divide(i,ope);
}

inline void getans()
{
    for(int i=1;i<=pl;i++)
    {
        while(cnt[i]--) mul(prime[i]);
    }
}

inline void putans()
{
    for(int i=len;i;i--)
    {
        if(i==len) printf("%d",ans[i]);
        else printf("%06d",ans[i]);
    }
}
inline int getint()
{
    int ret=0,fix=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') fix=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')
        ret=ret*10+(ch-'0'),
        ch=getchar();
    return ret*fix;
}

int main()
{
    ans[1]=len=1;
    n=getint();
    getprime(1000);
    if(n==1)
    {
        int x=getint();
        if(!x) puts("1");
        else puts("0");
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        in[i]=getint();
        if(!in[i])
        {
            puts("0");
            return 0;
        }
        if(in[i]==-1) m++;
        else
        {
            in[i]--;
            tot+=in[i];
        }
    }
    if(tot>n-2)
    {
        puts("0");
        return 0;
    }
    update(n-2,1);
    update(n-2-tot,-1);
    for(int i=1;i<=n;i++) if(in[i]) update(in[i],-1);
	getans();
	for(int i=1;i<=n-2-tot;i++) mul(m);
    putans();
    return 0;
}


