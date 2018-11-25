#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e3+1e2,maxm=1e4+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm],nxt[maxm],v[maxm];
int dep[maxn];
bool vis[maxm];
int que[maxn],st,ed,n,m,ans;

inline void addedge(int from,int to,int val)
{
    static int cnt=1;
    t[++cnt]=to,v[cnt]=val,nxt[cnt]=s[from],s[from]=cnt;
    t[++cnt]=from,v[cnt]=val,nxt[cnt]=s[to],s[to]=cnt;
}
inline void core_bfs(int pos)
{
    int at=s[pos];
    while(at)
    {
        if(dep[t[at]]==-1)
        {
            dep[t[at]]=dep[pos]+1;
            que[++ed]=t[at];
        }
        at=nxt[at];
    }
}
inline void getdep()
{
    memset(dep,-1,sizeof(dep));
    dep[1]=1;
    que[st=ed=1]=1;
    while(st<=ed) core_bfs(que[st++]);
}
inline void core_mark(int pos)
{
    int at=s[pos];
    while(at)
    {
        if(dep[t[at]]==dep[pos]+1)
        {
            vis[at]=1;
            vis[at^1]=1;
            que[++ed]=t[at];
        }
        at=nxt[at];
    }
}
inline void markedge()
{
    que[st=ed=1]=1;
    while(st<=ed) core_mark(que[st++]);
}

inline int dfs(int pos,int flow)
{
    if(pos==n) return flow;
    int ret=0,now=0;
    int at=s[pos];
    while(at)
    {
        if(vis[at]&&v[at]&&dep[t[at]]>dep[pos])
        {
            now=dfs(t[at],min(flow,v[at]));
            ret+=now;
            flow-=now;
            v[at]-=now;
            v[at^1]+=now;
            if(!flow) break;
        }
        at=nxt[at];
    }
    return ret;
}
inline int once_dinic()
{
    int ret=0,now=0;
    while(now=dfs(1,inf)) ret+=now;
    return ret;
}

int main()
{
	freopen("barricade.in","r",stdin);
	freopen("barricade.out","w",stdout);
	
    scanf("%d%d",&n,&m);

    for(int i=1,a,b,v;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&v);
        addedge(a,b,v);
    }
    getdep();
    markedge();
    ans=once_dinic();

    printf("%d\n",ans);
    
    fclose(stdin);
    fclose(stdout);

    return 0;
}




