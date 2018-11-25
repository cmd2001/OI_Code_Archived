#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxm=2e5+1e2;

vector<int> es[maxn];
int prv[maxn],nxt[maxn];
unsigned char vis[maxn],mrk[maxn];
int siz[maxn],cnt;
int n,m;

inline void addedge(int a,int b)
{
    es[a].push_back(b);
    es[b].push_back(a);
}

inline void init()
{
    for(int i=1;i<=n;i++)
        nxt[i] = i + 1,
        prv[i] = i - 1;
    nxt[0] = 1;
}

inline void del(int xx)
{
    nxt[prv[xx]] = nxt[xx];
    prv[nxt[xx]] = prv[xx];
}

inline void bfs(int st)
{
    queue<int> q;
    q.push(st);
    while( q.size() )
    {
        ++siz[cnt];
        const int pos = q.front();
        //debug<<"pos = "<<pos<<endl;
        q.pop();
        for(unsigned at=0;at<es[pos].size();at++)
            if( !vis[es[pos][at]] )
                mrk[es[pos][at]] = 1;
        for(int at=nxt[0];at!=n+1;at=nxt[at])
            if( vis[at] )
                continue;
            else if( !mrk[at] )
            {
                vis[at] = 1;
                del(at);
                q.push(at);
            }
            else
                mrk[at] = 0;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        addedge(a,b);
        addedge(b,a);
    }
    init();
    for(int i=1;i<=n;i++)
        if( !vis[i] )
        {
            cnt++;
            del(i);
            bfs(i);
            //debug<<"-------------"<<endl;
        }
    
    sort(siz+1,siz+1+cnt);
    
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++)
        printf("%d ",siz[i]);
    putchar('\n');
    
    return 0;
}
