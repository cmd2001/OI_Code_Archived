#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxp=1e5+1e2;

struct Node
{
    int id,pos;
    friend bool operator < (const Node &a,const Node &b)
    {
        return a.pos != b.pos ? a.pos > b.pos : a.id < b.id;
    }
};
multiset<Node> ms;

int in[maxp],nxt[maxp],lst[maxn];
int srt[maxn],len;
unsigned char vis[maxn];
int msp[maxn];
int n,q,m,ans;

inline int getint()
{
    int ret = 0;
    char ch = getchar();
    while( ! isdigit(ch) )
        ch = getchar();
    while( isdigit(ch) )
        ret = ret * 10 + ( ch - '0' ),
        ch = getchar();
    return ret;
}

int main()
{
    q = n = getint() , m = getint() ;
    for(int i=1;i<=q;i++)
        srt[++len] = in[i] = getint();
    sort(srt+1,srt+1+n);
    n = len = unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=q;i++)
        in[i] = lower_bound(srt+1,srt+1+len,in[i]) - srt;
    n = len;
    for(int i=1;i<=n;i++)
        lst[i] = q + 1;
    for(int i=q;i;i--)
        nxt[i] = lst[in[i]],
        lst[in[i]] = i;
    for(int i=1;i<=q;i++)
    {
        if( !vis[in[i]] )
        {
            //debug<<"!vis"<<endl;
            ++ans;
            if( ms.size() < m )
            {
                ms.insert((Node){in[i],nxt[i]});
                vis[in[i]] = 1 , msp[in[i]] = nxt[i];
            }
            else
            {
                const int rm = (*ms.begin()).id;
                ms.erase(ms.begin());
                //debug<<"reased"<<rm<<endl;
                vis[rm] = 0 , msp[rm] = 0;
                ms.insert((Node){in[i],nxt[i]});
                vis[in[i]] = 1 , msp[in[i]] = nxt[i];
            }
        }
        else
        {
            ms.erase((Node){in[i],msp[in[i]]});
            msp[in[i]] = nxt[i];
            ms.insert((Node){in[i],nxt[i]});
        }
    }
    
    printf("%d\n",ans);
    
    return 0;
}