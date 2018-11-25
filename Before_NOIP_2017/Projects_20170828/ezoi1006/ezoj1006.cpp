#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=6e2+1e1;
const int mod=1000000007;

int s[maxn],t[maxn*maxn],nxt[maxn*maxn],in[maxn],n,m,k;
lli f[maxn][maxn],way[maxn],fix,g;
int st[maxn],ed[maxn];
bool mark[maxn];

inline void addedge(int from,int to)
{
    static int cnt=0;
	t[++cnt]=to;
	nxt[cnt]=s[from];
	s[from]=cnt;
}

inline void dfs(int pos)
{
    int at=s[pos];
    while(at)
    {
        if(!mark[t[at]])
        {
            mark[t[at]]=1;
            dfs(t[at]);
        }
        at=nxt[at];
    }
}
void getin(int pos)
{
    memset(mark,0,sizeof(mark));
    memset(in,0,sizeof(in));
    mark[pos]=1;
    dfs(pos);
    for(int i=1;i<=n;i++)
        if(mark[i])
        {
            int at=s[i];
            while(at)
            {
                in[t[at]]++;
                at=nxt[at];
            }
        }

}

inline void core_update(int pos,int id)
{
    getin(pos);
    memset(way,0,sizeof(way));
    way[pos]=1;
    queue<int> q;
    q.push(pos);
    while(!q.empty())
    {
        const int x=q.front();
        q.pop();
        int at=s[x];
        while(at)
        {
            way[t[at]]=(way[x]+way[t[at]])%mod;
            in[t[at]]--;
            if(!in[t[at]]) q.push(t[at]);
            at=nxt[at];
        }
    }
    for(int i=1;i<=k;i++)
        f[id][i]=way[ed[i]]%mod;
}
inline void genf()
{
    for(int i=1;i<=k;i++) core_update(st[i],i);
    for(int i=1;i<=k;i++)
        for(int j=1;j<=k;j++)
            f[i][j]%=mod;
}
inline lli fastpow(lli base,lli tme,lli mod)
{
    lli ret=1,now=base%mod;
    while(tme)
    {
        if(tme&1) ret=ret*now%mod;
        now=now*now%mod;
        tme>>=1;
    }
    return ret;
}
inline void swaper(int x,int y)
{
    g*=-1;
    for(int i=1;i<=n;i++) swap(f[x][i],f[y][i]);
}
inline void multi(int pos,lli x)
{
    for(int i=1;i<=k;i++) f[pos][i]=f[pos][i]*x%mod;
}
inline void minuser(int tar,int base,lli tme)
{
    for(int i=1;i<=k;i++)
	{
		f[tar][i]=((f[tar][i]-f[base][i]*tme)%mod+mod)%mod;
	}
}

inline void calc()
{
    g=1,fix=1;
    for(int i=1,pos;i<=k;i++)
    {
        pos=0;
        for(int j=i;j<=k;j++)
            if(f[j][i])
            {
                pos=j;
                break;
            }
        if(!pos)
        {
            fix=0;//,puts("No solution");
            continue;
        }
        if(pos!=i) swaper(pos,i);
        pos=i;
        if(f[i][i]!=1&&f[i][i])
        {
            fix=fix*f[i][i]%mod;
            multi(i,fastpow(f[i][i],mod-2,mod));
        }
        for(int j=1;j<=k;j++)
            if(j!=pos&&f[j][i])
                minuser(j,pos,f[j][i]);
     }
}

inline int getint()
{
    int ret=0,fix=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')fix=-1; ch=getchar();}
    while(ch>='0'&&ch<='9')
        ret=ret*10+(ch-'0'),
        ch=getchar();
    return ret*fix;
}

int main()
{
	//freopen("reverse10.in","r",stdin);
	//freopen("wa.out","w",stdout);
    n=getint(),m=getint(),k=getint();
    for(int i=1;i<=k;i++) st[i]=getint();
    for(int i=1;i<=k;i++) ed[i]=getint();
    for(int i=1,a,b;i<=m;i++)
    {
        a=getint(),b=getint();
        addedge(a,b);
    }

    genf();
	
    /*for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=k;j++) debug<<f[i][j]<<" ";
        debug<<endl;
    }*/

    calc();

    printf("%lld\n",(fix*g%mod+mod)%mod);

    //while(1);


    return 0;
}







