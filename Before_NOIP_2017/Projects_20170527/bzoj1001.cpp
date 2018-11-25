#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e6+1e4,inf=0x7fffffff;
int s[maxn],dep[maxn],t[6*maxn],nxt[6*maxn];
int f[6*maxn],st,ed,n,m;

inline void addedge(int from,int to,int flow)
{
    static int cnt=1;
    t[++cnt]=to;
    nxt[cnt]=s[from];
    s[from]=cnt;
    f[cnt]=flow;
}

queue<int> q;

inline void core_bfs(int pos)
{
    int at=s[pos];
    while(at)
    {
        if(f[at]&&!dep[t[at]])
        {
            dep[t[at]]=dep[pos]+1;
            q.push(t[at]);
        }
        at=nxt[at];
    }
}

inline int dfs(int pos,int flow)
{
    if(pos==ed) return flow;
    int ret=0,tmp,at=s[pos];
    while(at)
    {
        if(f[at]&&dep[t[at]]>dep[pos])
        {
            tmp=dfs(t[at],min(flow,f[at]));
            ret+=tmp;
            f[at]-=tmp;
            f[at^1]+=tmp;
            flow-=tmp;
            if(!flow) return ret;
        }
        at=nxt[at];
    }
    if(!ret) dep[pos]=0;
    return ret;
}

inline int getflow()
{
    int ret=0,tmp;
    while(1)
    {
        memset(dep,0,sizeof(dep));
        q.push(st);
        dep[st]=1;
        while(!q.empty())
        {
            core_bfs(q.front());
            q.pop();
        }
        if(!dep[ed]) return ret;
        tmp=dfs(st,inf);
        ret+=tmp;
    }
}

int main()
{
	freopen("dat.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1,a,b,tmp;i<=n;i++) for(int j=1;j<m;j++)
    {
        scanf("%d",&tmp);
        a=i*m+j-m,b=i*m+j+1-m;
        addedge(a,b,tmp);
        addedge(b,a,tmp);
    }
    for(int i=1,a,b,tmp;i<n;i++) for(int j=1;j<=m;j++)
    {
        scanf("%d",&tmp);
        a=i*m+j-m,b=(i+1)*m+j-m;
        addedge(a,b,tmp);
        addedge(b,a,tmp);
    }
    for(int i=1,a,b,tmp;i<n;i++) for(int j=1;j<m;j++)
    {
        scanf("%d",&tmp);
        a=i*m+j-m,b=(i+1)*m+j+1-m;
        addedge(a,b,tmp);
        addedge(b,a,tmp);
    }
    st=1*m+1-m,ed=n*m+m-m;
    printf("%d\n",getflow());
    return 0;
}




