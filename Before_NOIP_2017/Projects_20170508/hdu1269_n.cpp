#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=5e4+1e2,maxm=1e5+1e2;
int to[maxm],nxt[maxm],s[maxn];
int dfn[maxn],low[maxn],n,m,cnt,ctr,cne;
bool vis[maxn],in[maxn];
int siz;
stack <int> st;
inline void addedge(int f,int t)
{
    nxt[++cne]=s[f];
    to[cne]=t;
    s[f]=cne;
}
void dfs(int pos)
{
    //debug<<"pos="<<pos<<endl;
    static int cnt;
    low[pos]=dfn[pos]=ctr++;
    st.push(pos);
    in[pos]=1;
    int at=s[pos];
    while(at)
    {
        const int &t=to[at];
        //debug<<"t="<<t<<endl;
        if(!vis[t])
        {
            vis[t]=1;
            dfs(t);
        }
        if(in[t]) low[pos]=min(low[pos],low[t]);
        at=nxt[at];
    }
    if(low[pos]==dfn[pos])
    {
        //debug<<"low==dfn"<<endl;
        cnt=0;
        while(st.top()!=pos)
        {
            ++cnt;
            in[st.top()]=0;
            st.pop();
        }
        ++cnt;
        in[st.top()]=0;
        st.pop();
        siz=max(siz,cnt);
    }
}
inline void init()
{
    memset(to,0,sizeof(to));
    memset(nxt,0,sizeof(nxt));
    memset(s,0,sizeof(s));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(vis,0,sizeof(vis));
    memset(in,0,sizeof(in));
    siz=cnt=cne=0;
    ctr=1;
    while(!st.empty()) st.pop();
}
int main()
{
    while(scanf("%d%d",&n,&m)==2&&(n||m)) // You will get WA if you write &&n&&m;
    {
        //puts("Fuck you!!!");
        //puts("You motherfucker!")
        init();
        for(int i=1,a,b;i<=m;i++) {scanf("%d%d",&a,&b);addedge(a,b);}
        for(int i=1;i<=n;i++)
        {
            if(!vis[i])
            {
                vis[i]=1;
                dfs(i);
            }
        }
        if(siz==n) puts("Yes");
        else puts("No");
    }
    return 0;
}
