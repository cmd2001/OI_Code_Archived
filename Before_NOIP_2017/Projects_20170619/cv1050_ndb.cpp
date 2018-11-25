#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e2+1e1,maxl=1<<11;

int in[maxn][7],lst[7],now[7],n,ans,last,start,cur=1;
int dp[2][maxl];
bool row[7],vis[7],used[7];

inline void unzip(int x)
{
    memset(lst,0,sizeof(lst));
    for(int i=1;i<6;i++) lst[i]=(x>>((i-1)<<1))&3;
}
inline int zip()
{
    int ret=0;
    for(int i=1;i<6;i++)
    {
        ret|=(now[i]<<((i-1)<<1));
    }
    return ret;
}

inline void extra_col(int pos)
{
    for(int k=pos+1;row[k];k++) now[k]=now[pos];
    for(int k=pos-1;row[k];k--) now[k]=now[pos];
}
inline void extra_vis(int pos)
{
    for(int k=pos+1;lst[k];k++) vis[k]=1;
    for(int k=pos-1;lst[k];k--) vis[k]=1;
    for(int k=1;k<6;k++) if(lst[k]==lst[pos]) vis[k]=1;
}
inline bool judge_vis()
{
    bool ret=1;
    for(int i=1;i<6;i++) if(lst[i]) ret&=vis[i];
    return ret;
}
inline void re_color(int from,int to)
{
    for(int i=1;i<6;i++) if(now[i]==from) now[i]=to;
}
inline void color()
{
    memset(vis,0,sizeof(vis));
    memset(now,0,sizeof(now));
    memset(used,0,sizeof(used));

    for(int i=1;i<6;i++)
    {
        if(row[i]&&!now[i]) if(lst[i])
        {
            now[i]=lst[i];
            vis[i]=1;
            used[lst[i]]=1;
            extra_col(i);
            extra_vis(i);
        }
        if(row[i]&&now[i]&&lst[i])
        {
            vis[i]=1;
            extra_vis(i);
            re_color(lst[i],now[i]);
        }
    }
    for(int i=1;i<6;i++)
    {
    	if(row[i]&&now[i]&&lst[i]&&now[i]!=lst[i]) re_color(lst[i],now[i]);
    }
    if(used[2]&&!used[1])
    {
        re_color(2,1);
        used[1]=1,used[2]=0;
    }

    for(int i=1;i<6;i++) if(row[i]&&!now[i])
    {
        now[i]= ( (!used[1]) ? (used[1]=1,1) : ( (!used[2]) ? (used[2]=1,2) : (used[3]=1,3) ) );
        extra_col(i);
    }
    if(used[3]&&!used[1])
    {
        re_color(3,1);
        used[1]=1,used[3]=0;
    }
    if(used[3]&&!used[2])
    {
        re_color(3,2);
        used[2]=1,used[3]=0;
    }
    if(used[2]&&!used[1])
    {
        re_color(2,1);
        used[1]=1,used[2]=0;
    }
}

void dfs(int dep,int to,int x)
{
    if(dep==6)
    {
        if(judge_vis())
        {
            int sta=zip();
            dp[to][sta]=min(dp[to][sta],x);
        }
        return;
    }
    if(row[dep]) dfs(dep+1,to,x);
    else if(!row[dep])
    {
        row[dep]=1;
        color();
        dfs(dep+1,to,x+1);
        row[dep]=0;
        color();
        dfs(dep+1,to,x);
    }
}

inline bool judge_ans(int k)
{
    unzip(k);
    static int num;
    for(int i=1;i<6;i++) if(num=lst[i]) break;
    for(int i=1;i<6;i++) if(lst[i]&&lst[i]!=num) return 0;
    return 1;
}
inline int getans()
{
    int ret=0x3f3f3f3f;
    for(int i=1;i<maxl;i++)
    {
        if(judge_ans(i)) ret=min(ret,dp[cur][i]);
    }
    return ret;
}

inline void get_input()
{
    static char s[10];
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=5;j++)
		{
			if(in[i][j]=s[j]-'0')
			{
				last=i;
				if(!start) start=i;
			}
		}
    }
}

int main()
{
    get_input();

    memset(dp,0x3f,sizeof(dp));

    for(int i=1;i<6;i++) row[i]=in[start][i];
    color();
    dfs(1,cur,0);

    for(int i=start;i<last;i++)// i:using row
    {
        for(int k=1;k<6;k++) row[k]=in[i+1][k];
        memset(dp[cur^1],0x3f,sizeof(dp[0]));
        for(int k=1;k<maxl;k++)
        {
        	if(dp[cur][k]>=0x3f3f3f3f) continue;
            unzip(k);
            color();
            dfs(1,cur^1,dp[cur][k]);
        }
		cur^=1;
    }

    ans=getans();

    printf("%d\n",ans);

    return 0;
}

