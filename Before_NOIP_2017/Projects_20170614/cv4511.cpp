#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=2e6+1e2;

int in[maxn],cnt[maxn],que[maxn],n,st,ed;
bool vis[maxn];

inline void cutchain()
{
    st=1;
    while(ed>=st)
    {
        const int &x=que[st];
        vis[x]=1;
        cnt[in[x]]--;
        if(!cnt[in[x]]) que[++ed]=in[x];
        st++;
    }
}
inline int getring(int x)
{
    int ret=0;
    while(!vis[x])
    {
        ++ret;
        vis[x]=1;
        x=in[x];
    }
    return ret;
}
inline void init()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",in+i);
        cnt[in[i]]++;
    }
}
int main()
{
    static int ans=0x7fffffff;
    init();
    for(int i=1;i<=n;i++) if(!cnt[i]) que[++ed]=i;
    cutchain();
    for(int i=1;i<=n;i++) if((!vis[i])&&cnt[i]) ans=min(ans,getring(i));
    printf("%d\n",ans);
    return 0;
}
