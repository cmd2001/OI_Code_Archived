#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=5e3+1e2,maxm=1e5+1e2;
int to[maxm],nxt[maxm],s[maxn];
int dfn[maxn],low[maxn],n,m,cnt,ctr,cne;
bool vis[maxn],in[maxn];
int out[maxn],siz;
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
    static int tmp[maxn],cnt;
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
        memset(tmp,0,sizeof(tmp));
        cnt=0;
        while(st.top()!=pos)
        {
            tmp[++cnt]=st.top();
            in[st.top()]=0;
            st.pop();
        }
        tmp[++cnt]=st.top();
        in[st.top()]=0;
        st.pop();
        if(cnt<siz) return;
        sort(tmp+1,tmp+1+cnt);
        if(cnt>siz)
        {
            memcpy(out,tmp,sizeof(tmp));
            siz=cnt;
        }
        else if(cnt==siz) if(tmp[1]<out[1]) memcpy(out,tmp,sizeof(tmp));
    }
}
int main()
{
    //freopen("deb.txt","w",stdout);
    scanf("%d%d",&n,&m);
    ctr=1;
    for(int i=1,a,b,c;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        addedge(a,b);
        if(c==2) addedge(b,a);
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            //debug<<"i="<<i<<endl;
            vis[i]=1;
            dfs(i);
        }
    }
    printf("%d\n",siz);
    for(int i=1;i<=siz;i++) printf("%d ",out[i]);
    putchar('\n');
    return 0;
}
