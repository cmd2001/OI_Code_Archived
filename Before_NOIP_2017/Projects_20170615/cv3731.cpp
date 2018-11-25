#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e4+1e2,maxm=2e5+1e2;

int s[maxn],revs[maxn],nxt[maxm],revnxt[maxm],t[maxm],revt[maxm],dep[maxn];
int m,n,start,endd;
bool vis[maxn],cav[maxn];

void addedge(int from,int to)
{
    static int cnt=0;
    t[++cnt]=to;
    nxt[cnt]=s[from];
    s[from]=cnt;
}
void addrevedge(int from,int to)
{
    static int cnt=1024;
    revt[++cnt]=to;
    revnxt[cnt]=revs[from];
    revs[from]=cnt;
}

queue<int> q;

inline void core_bfs1(int pos)
{
    int at=revs[pos];
    while(at)
    {
        if(!vis[revt[at]])
        {
            vis[revt[at]]=1;
            q.push(revt[at]);
        }
        at=revnxt[at];
    }
}
inline void core_bfs2(int pos)
{
    int at=s[pos];
    while(at)
    {
        if(cav[t[at]]&&dep[t[at]]==-1)
        {
            dep[t[at]]=dep[pos]+1;
            q.push(t[at]);
        }
        at=nxt[at];
    }
}
inline bool check(int pos)
{
    bool ret=1;
    int at=s[pos];
    while(at)
    {
        ret&=vis[t[at]];
        at=nxt[at];
    }
    return ret;
}
inline void getans()
{
    q.push(endd);
    vis[endd]=1;
    while(!q.empty())
    {
        core_bfs1(q.front());
        q.pop();
    }

    for(int i=1;i<=n;i++) cav[i]=check(i);

    memset(dep,-1,sizeof(dep));
    cav[start]=cav[endd]=1;
    dep[start]=0;
    q.push(start);
    while(!q.empty())
    {
        core_bfs2(q.front());
        q.pop();
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        addedge(a,b);
        addrevedge(b,a);
    }
    scanf("%d%d",&start,&endd);

    getans();

    printf("%d\n",dep[endd]);

    return 0;
}
