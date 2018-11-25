#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e4+1e2,maxm=5e4+1e2,maxk=22;

int s[maxn],t[maxm<<1],nxt[maxm<<1];
lli l[maxm<<1];
lli dis[maxn],tp[maxn];
lli ans;
unsigned char inq[maxn];
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
    queue<int> q;
    
    for(int i=1;i<=n;i++)
    {
        q.push(i);
        inq[i] = 1;
    }
    
    while( q.size() )
    {
        const int pos = q.front();
        q.pop();
        inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
        {
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
        in_level_spfa(dis);
        if( i != k )
        {
            //memset(tp,0x3f,sizeof(tp));
            cross_level_dp(dis,tp);
            memcpy(dis,tp,sizeof(dis));
        }
        ans = min( ans , dis[n] );
    }
    
    printf("%lld\n",ans);
    
    return 0;
}

