#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cctype>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

struct Node
{
    int pos;
    lli val;
    friend bool operator < (const Node &a,const Node &b)
    {
        return a.val != b.val ? a.val < b.val : a.pos < b.pos;
    }
};
multiset<Node> ms;

lli in[maxn],ans;
int prv[maxn],nxt[maxn];
unsigned char vis[maxn];
int n,m,tot,used;

inline void init()
{
    for(int i=1;i<=n;i++)
        prv[i] = i - 1,
        nxt[i] = i + 1;
}

inline void del(int x)
{
    vis[x] = 1;
    if( prv[x] != 0 )
        nxt[prv[x]] = nxt[x];
    if( nxt[x] != n + 1 )
        prv[nxt[x]] = prv[x];
}

inline void merge(int x)
{
    lli nv = in[x];
    if( prv[x] != 0 )
    {
        nv += in[prv[x]];
        del(prv[x]);
    }
    if( nxt[x] != n + 1 )
    {
        nv += in[nxt[x]];
        del(nxt[x]);
    }
    in[x] = nv;
    ms.insert((Node{x,abs(nv)}));
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
        ch = getchar();/* condition */
    return ret * fix;
}

int main()
{
    //freopen("deb.txt","w",stdout);
    tot = getint() , m = getint();
    while( tot-- )
    {
        lli xx = getint();
        if( !xx )
            continue;
        if( !n || in[n] * xx < 0 )
            in[++n] = xx;
        else
            in[n] += xx;
    }
    
    init();
    
    for(int i=1;i<=n;i++)
    {
        ms.insert((Node){i,abs(in[i])});
        if( in[i] > 0 )
            ans += in[i],
            ++used;
    }
    
    /*for(int i=1;i<=n;i++) debug<<in[i]<<" ";debug<<endl;
    
    debug<<"ans = "<<ans<<"used = "<<used<<endl;*/
    
    while( used > m )
    {
        --used;
        while( vis[(*ms.begin()).pos] )
            ms.erase(ms.begin());
        const int pos = (*ms.begin()).pos;
            ms.erase(ms.begin());
        if( ( prv[pos] == 0 || nxt[pos] == n + 1 ) && in[pos] < 0 )
        {
            ++used;
            continue;
        }
        ans -= abs(in[pos]);
        merge(pos);
    }
    
    printf("%lld\n",ans);
    
    return 0;
}