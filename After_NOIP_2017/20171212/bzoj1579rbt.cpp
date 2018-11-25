#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cctype>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e4+1e2,maxm=5e4+1e2,maxk=22;

struct Node
{
    int pos;
    lli dis;
    friend bool operator < (const Node &a,const Node &b)
    {
        return a.dis != b.dis ? a.dis < b.dis : a.pos < b.pos;
    }
};
int s[maxn],t[maxm<<1],nxt[maxm<<1];
lli l[maxm<<1];
lli dis[maxn],tp[maxn];
lli ans;
unsigned char vis[maxn];
int n,m,k;

inline void addedge(int from,int to,int len)
{
    static int cnt = 0;
    t[++cnt] = to;
    l[cnt] = len;
    nxt[cnt] = s[from];
    s[from] = cnt;
}
inline void in_level_spfa(lli* dis)
{
    memset(vis,0,sizeof(vis));
    
    multiset<Node> ms;
    
    for(int i=1;i<=n;i++)
        ms.insert((Node){i,dis[i]});
    
    //debug<<"size = "<<ms.size()<<endl;
    for(int i=1;i<=n;i++)
    //while( ms.size() )
    {
        //debug<<"spfa i = "<<i<<endl;
        Node now = *ms.begin();
        //debug<<"begin found"<<endl;
        ms.erase(ms.begin());
        //debug<<"erased"<<endl;
        if( vis[now.pos] )
        {
            //debug<<"vised"<<endl;
            continue;
        }
        vis[now.pos] = 1;
        
        //debug<<"pos = "<<now.pos<<endl;
        
        
        const int &pos = now.pos;
        const lli &dd = now.dis;
        
        
        for(int at = s[pos];at;at=nxt[at])
            if( !vis[t[at]] && dis[t[at]] > dd + l[at] )
            {
                ms.erase((Node){t[at],dis[t[at]]});
                dis[t[at]] = dd + l[at];
                ms.insert((Node){t[at],dis[t[at]]});
            }
    }
        
    
}

inline void cross_level_dp(lli* sou,lli* tar)
{
    for(int pos=1;pos<=n;pos++)
        for(int at=s[pos];at;at=nxt[at])
            if( tar[t[at]] > sou[pos] )
                tar[t[at]] = sou[pos];
}

inline int getint()
{
    int ret = 0 , fix = 1;
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
    //freopen("fuck.txt","r",stdin);
    n = getint() , m = getint() , k = getint();
    for(int i=1,a,b,l;i<=m;i++)
    {
        a = getint() , b = getint() , l = getint();
        addedge(a,b,l);
        addedge(b,a,l);
    }
    
    memset(dis,0x3f,sizeof(dis));
    memset(tp,0x3f,sizeof(tp));
    
    ans = *dis;
    
    dis[1] = 0;
    
    for(int i=0;i<=k;i++)
    {
        //debug<<"i = "<<i<<endl;
        in_level_spfa(dis);
        if( i != k )
        {
            cross_level_dp(dis,tp);
            memcpy(dis,tp,sizeof(dis));
        }
        ans = min( ans , dis[n] );
    }
    
    printf("%lld\n",ans);
    
    return 0;
}

