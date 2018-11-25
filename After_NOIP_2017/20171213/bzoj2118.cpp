#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=13,maxm=5e5+1e2; // Notice that maxm is zhe size of points and edges.
const int inf=0x3f3f3f3f;

int s[maxm],t[maxm<<4],nxt[maxm<<4],l[maxm<<4];
int in[maxn];
int n,miv;
lli dis[maxm];
lli ll,rr,ans;

inline void addedge(int from,int to,int len)
{
    static int cnt = 0;
    t[++cnt] = to;
    l[cnt] = len;
    nxt[cnt] = s[from];
    s[from] = cnt;
}

inline void spfa(int st)
{
    static unsigned char inq[maxm];
    dis[st] = 0;
    queue<int> q;
    
    q.push(st);
    inq[st] = 1;
    
    while( q.size() )
    {
        const int pos = q.front();
        q.pop();
        inq[pos] = 0;
        
        for(int at=s[pos];at;at=nxt[at])
            if( dis[t[at]] > dis[pos] + l[at] )
            {
                dis[t[at]] = dis[pos] + l[at];
                if( !inq[t[at]] )
                {
                    q.push(t[at]);
                    inq[t[at]] = 1;
                }
            }
    }
    
}

inline lli calc(lli x,lli lim)
{
    if( x <= lim )
        return ( lim - x ) / miv + 1;
    else
        return 0;
}

inline lli getint()
{
    lli ret = 0 , fix = 1;
    char ch = getchar();
    while( ! isdigit(ch) )
        fix = ch == '-' ? -1 : fix,
        ch = getchar();
    while( isdigit(ch) )
        ret = ret * 10 + ( ch - '0' ),
        ch = getchar();
    return ret * fix;
}

int main()
{
    n = getint() , ll = getint() - 1 , rr = getint();
    miv = inf;
    for(int i=1;i<=n;i++)
        miv = min( miv , in[i] = getint() );
    
    
    memset(dis,0x3f,sizeof(dis));
    
    //debug<<"miv = "<<miv<<endl;
    
    for(int i=0;i<miv;i++)
        for(int j=1;j<=n;j++)
            addedge(i,(i+in[j])%miv,in[j]);
    
    spfa(0);
    
    /*for(int i=0;i<miv;i++)
        debug<<dis[i]<<" ";debug<<endl;*/
    
    for(int i=0;i<miv;i++)
        ans -= calc(dis[i],ll),
        ans += calc(dis[i],rr);
    
    printf("%lld\n",ans);
    
    return 0;
}
